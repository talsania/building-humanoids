#include <iostream>
#include <vector>
#include <pinocchio/multibody/model.hpp>
#include <pinocchio/multibody/data.hpp>
#include <pinocchio/algorithm/kinematics.hpp>
#include <pinocchio/algorithm/jacobian.hpp>
#include <pinocchio/parsers/urdf.hpp>
#include <pinocchio/algorithm/frames.hpp>

class JacobianTester
{
public:
    JacobianTester() = default;
    
    bool loadURDF(const std::string& urdf_path)
    {
        try
        {
            std::cout << "Loading URDF from: " << urdf_path << std::endl;
            pinocchio::urdf::buildModel(urdf_path, model_);
            data_ = pinocchio::Data(model_);
            
            std::cout << "Model loaded successfully!" << std::endl;
            std::cout << "Number of joints: " << model_.njoints << std::endl;
            std::cout << "Number of DOF: " << model_.nv << std::endl;
            std::cout << "Number of frames: " << model_.frames.size() << std::endl;
            
            // Print joint names
            std::cout << "\nJoint names:" << std::endl;
            for (size_t i = 0; i < model_.names.size(); ++i)
            {
                std::cout << "  " << i << ": " << model_.names[i] << std::endl;
            }
            
            // Print frame names
            std::cout << "\nFrame names:" << std::endl;
            for (size_t i = 0; i < model_.frames.size(); ++i)
            {
                std::cout << "  " << i << ": " << model_.frames[i].name << std::endl;
            }
            
            return true;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error loading URDF: " << e.what() << std::endl;
            return false;
        }
    }
    
    bool computeJacobian(const std::vector<double>& joint_angles, 
                        const std::string& frame_name,
                        Eigen::MatrixXd& jacobian)
    {
        try
        {
            // Convert joint angles to Eigen vector
            Eigen::VectorXd q = Eigen::VectorXd::Zero(model_.nq);
            
            // Copy joint angles (assuming they match the model's DOF)
            int copy_size = std::min(static_cast<int>(joint_angles.size()), model_.nv);
            for (int i = 0; i < copy_size; ++i)
            {
                q[i] = joint_angles[i];
            }
            
            std::cout << "Joint configuration: " << q.transpose() << std::endl;
            
            // Compute forward kinematics
            pinocchio::forwardKinematics(model_, data_, q);
            
            // Find frame
            pinocchio::FrameIndex frame_id;
            if (model_.existFrame(frame_name))
            {
                frame_id = model_.getFrameId(frame_name);
                std::cout << "Found frame '" << frame_name << "' with ID: " << frame_id << std::endl;
            }
            else
            {
                std::cerr << "Frame '" << frame_name << "' not found!" << std::endl;
                return false;
            }
            
            // Compute Jacobian
            jacobian = Eigen::MatrixXd::Zero(6, model_.nv);
            pinocchio::computeFrameJacobian(model_, data_, q, frame_id, 
                                            pinocchio::LOCAL_WORLD_ALIGNED, jacobian);
            
            std::cout << "Jacobian computed successfully!" << std::endl;
            std::cout << "Jacobian dimensions: " << jacobian.rows() << "x" << jacobian.cols() << std::endl;
            std::cout << "Jacobian norm: " << jacobian.norm() << std::endl;
            
            return true;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error computing Jacobian: " << e.what() << std::endl;
            return false;
        }
    }
    
    void printJacobian(const Eigen::MatrixXd& jacobian)
    {
        std::cout << "\nJacobian matrix:" << std::endl;
        std::cout << jacobian << std::endl;
    }
    
    bool testNumericalVsAnalytical(const std::vector<double>& joint_angles,
                                  const std::string& frame_name,
                                  double epsilon = 1e-6)
    {
        std::cout << "\n=== Testing Numerical vs Analytical Jacobian ===" << std::endl;
        
        // Compute analytical Jacobian
        Eigen::MatrixXd analytical_jacobian;
        if (!computeJacobian(joint_angles, frame_name, analytical_jacobian))
        {
            return false;
        }
        
        // Compute numerical Jacobian
        Eigen::MatrixXd numerical_jacobian;
        if (!computeNumericalJacobian(joint_angles, frame_name, numerical_jacobian, epsilon))
        {
            return false;
        }
        
        // Compare
        Eigen::MatrixXd diff = analytical_jacobian - numerical_jacobian;
        double max_diff = diff.cwiseAbs().maxCoeff();
        double relative_error = max_diff / analytical_jacobian.cwiseAbs().maxCoeff();
        
        std::cout << "Analytical Jacobian norm: " << analytical_jacobian.norm() << std::endl;
        std::cout << "Numerical Jacobian norm: " << numerical_jacobian.norm() << std::endl;
        std::cout << "Max absolute difference: " << max_diff << std::endl;
        std::cout << "Relative error: " << relative_error << std::endl;
        
        bool test_passed = relative_error < 1e-3;
        std::cout << "Test result: " << (test_passed ? "PASSED" : "FAILED") << std::endl;
        
        return test_passed;
    }
    
private:
    pinocchio::Model model_;
    pinocchio::Data data_;
    
    bool computeNumericalJacobian(const std::vector<double>& joint_angles,
                                 const std::string& frame_name,
                                 Eigen::MatrixXd& jacobian,
                                 double epsilon)
    {
        try
        {
            // Get frame ID
            if (!model_.existFrame(frame_name))
            {
                std::cerr << "Frame not found for numerical Jacobian" << std::endl;
                return false;
            }
            pinocchio::FrameIndex frame_id = model_.getFrameId(frame_name);
            
            // Get center position
            pinocchio::SE3 pose_center = computeFramePose(joint_angles, frame_id);
            
            // Initialize Jacobian
            jacobian = Eigen::MatrixXd::Zero(6, joint_angles.size());
            
            // Compute numerical derivatives
            for (size_t i = 0; i < joint_angles.size(); ++i)
            {
                // Perturb joint i
                std::vector<double> joint_plus = joint_angles;
                std::vector<double> joint_minus = joint_angles;
                joint_plus[i] += epsilon;
                joint_minus[i] -= epsilon;
                
                // Get poses
                pinocchio::SE3 pose_plus = computeFramePose(joint_plus, frame_id);
                pinocchio::SE3 pose_minus = computeFramePose(joint_minus, frame_id);
                
                // Compute numerical derivatives for position
                jacobian(0, i) = (pose_plus.translation().x() - pose_minus.translation().x()) / (2 * epsilon);
                jacobian(1, i) = (pose_plus.translation().y() - pose_minus.translation().y()) / (2 * epsilon);
                jacobian(2, i) = (pose_plus.translation().z() - pose_minus.translation().z()) / (2 * epsilon);
                
                // For orientation, use angular velocity approximation
                pinocchio::SE3 diff = pose_plus.inverse() * pose_minus;
                Eigen::Vector3d angular_diff = pinocchio::log3(diff.rotation()) / (2 * epsilon);
                jacobian(3, i) = angular_diff.x();
                jacobian(4, i) = angular_diff.y();
                jacobian(5, i) = angular_diff.z();
            }
            
            return true;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error computing numerical Jacobian: " << e.what() << std::endl;
            return false;
        }
    }
    
    pinocchio::SE3 computeFramePose(const std::vector<double>& joint_angles, 
                                   pinocchio::FrameIndex frame_id)
    {
        Eigen::VectorXd q = Eigen::VectorXd::Zero(model_.nq);
        int copy_size = std::min(static_cast<int>(joint_angles.size()), model_.nv);
        for (int i = 0; i < copy_size; ++i)
        {
            q[i] = joint_angles[i];
        }
        
        pinocchio::forwardKinematics(model_, data_, q);
        pinocchio::updateFramePlacements(model_, data_);
        
        return data_.oMf[frame_id];
    }
};

int main(int argc, char** argv)
{
    std::cout << "=== Pinocchio Jacobian Tester ===" << std::endl;
    
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <urdf_file> [frame_name]" << std::endl;
        std::cerr << "Example: " << argv[0] << " /path/to/robot.urdf end_effector" << std::endl;
        return 1;
    }
    
    std::string urdf_path = argv[1];
    std::string frame_name = "end_effector";
    
    if (argc >= 3)
    {
        frame_name = argv[2];
    }
    
    JacobianTester tester;
    
    // Load URDF
    if (!tester.loadURDF(urdf_path))
    {
        std::cerr << "Failed to load URDF" << std::endl;
        return 1;
    }
    
    // Test with zero configuration
    std::cout << "\n=== Testing with zero configuration ===" << std::endl;
    std::vector<double> joint_angles_zero = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}; // Adjust size as needed
    
    Eigen::MatrixXd jacobian;
    if (tester.computeJacobian(joint_angles_zero, frame_name, jacobian))
    {
        tester.printJacobian(jacobian);
    }
    
    // Test with non-zero configuration
    std::cout << "\n=== Testing with non-zero configuration ===" << std::endl;
    std::vector<double> joint_angles_nonzero = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6}; // Adjust size as needed
    
    if (tester.computeJacobian(joint_angles_nonzero, frame_name, jacobian))
    {
        tester.printJacobian(jacobian);
    }
    
    // Test analytical vs numerical
    tester.testNumericalVsAnalytical(joint_angles_nonzero, frame_name);
    
    std::cout << "\n=== Test completed ===" << std::endl;
    
    return 0;
}