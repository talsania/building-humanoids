#include <iostream>
#include <rclcpp/rclcpp.hpp>
#include <moveit/robot_model_loader/robot_model_loader.h>
#include <moveit/kdl_kinematics_plugin/kdl_kinematics_plugin.h>
#include <fstream>

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("kdl_chain_print_test");
    
    std::cout << "=== KDL Chain Print Test ===" << std::endl;
    
    // Load robot description
    std::string urdf_path = "/home/kptal/humanoid_ws/src/myrobot_description/urdf/v2.urdf";
    std::ifstream urdf_file(urdf_path);
    if (!urdf_file.is_open()) {
        std::cerr << "Could not open URDF file: " << urdf_path << std::endl;
        return 1;
    }
    
    std::stringstream buffer;
    buffer << urdf_file.rdbuf();
    std::string urdf_content = buffer.str();
    
    // Load SRDF
    std::string srdf_path = "/home/kptal/humanoid_ws/src/kris_moveit_config/config/v2.srdf";
    std::ifstream srdf_file(srdf_path);
    if (!srdf_file.is_open()) {
        std::cerr << "Could not open SRDF file: " << srdf_path << std::endl;
        return 1;
    }
    
    std::stringstream srdf_buffer;
    srdf_buffer << srdf_file.rdbuf();
    std::string srdf_content = srdf_buffer.str();
    
    node->declare_parameter("robot_description", urdf_content);
    node->declare_parameter("robot_description_semantic", srdf_content);
    
    auto robot_model_loader = std::make_shared<robot_model_loader::RobotModelLoader>(node);
    auto robot_model = robot_model_loader->getModel();
    
    if (!robot_model) {
        std::cerr << "Robot model not available" << std::endl;
        return 1;
    }
    
    // Print available groups
    std::cout << "Available joint model groups:" << std::endl;
    auto group_names = robot_model->getJointModelGroupNames();
    for (const auto& name : group_names) {
        auto group = robot_model->getJointModelGroup(name);
        std::cout << "  - " << name;
        if (group->isChain()) {
            std::cout << " (chain)";
        } else {
            std::cout << " (not a chain)";
        }
        std::cout << std::endl;
    }
    
    // Test with right arm single chain (same as Kris plugin test)
    std::string group_name = "right_arm_single";
    if (!robot_model->hasJointModelGroup(group_name)) {
        std::cerr << "Robot model or " << group_name << " group not available. Available groups:" << std::endl;
        for (const auto& name : group_names) {
            std::cerr << "  - " << name << std::endl;
        }
        return 1;
    }
    
    // Initialize KDL plugin
    auto kdl_plugin = std::make_unique<kdl_kinematics_plugin::KDLKinematicsPlugin>();
    
    std::string base_frame = robot_model->getModelFrame();
    std::string tip_frame = "right_finger_1";  // Right arm chain tip
    std::vector<std::string> tip_frames = {tip_frame};
    
    std::cout << "\nInitializing KDL plugin with:" << std::endl;
    std::cout << "  Group: " << group_name << std::endl;
    std::cout << "  Base frame: " << base_frame << std::endl;
    std::cout << "  Tip frame: " << tip_frame << std::endl;
    
    bool kdl_success = kdl_plugin->initialize(node, *robot_model, group_name, 
                                             base_frame, tip_frames, 0.01);
    
    std::cout << "KDL Plugin initialization: " << (kdl_success ? "✓" : "✗") << std::endl;
    
    if (!kdl_success) {
        std::cerr << "KDL plugin initialization failed" << std::endl;
        return 1;
    }
    
    // Get KDL chain information
    auto kdl_joint_names = kdl_plugin->getJointNames();
    auto kdl_link_names = kdl_plugin->getLinkNames();
    
    std::cout << "\n=== KDL Plugin Information ===" << std::endl;
    std::cout << "Joint names (" << kdl_joint_names.size() << "):" << std::endl;
    for (size_t i = 0; i < kdl_joint_names.size(); ++i) {
        std::cout << "  [" << i << "] " << kdl_joint_names[i] << std::endl;
    }
    
    std::cout << "Link names (" << kdl_link_names.size() << "):" << std::endl;
    for (size_t i = 0; i < kdl_link_names.size(); ++i) {
        std::cout << "  [" << i << "] " << kdl_link_names[i] << std::endl;
    }
    
    // Print MoveIt group information
    std::cout << "\n=== MoveIt Group Information ===" << std::endl;
    auto kdl_group = robot_model->getJointModelGroup(group_name);
    if (kdl_group) {
        std::cout << "Group: " << group_name << std::endl;
        std::cout << "Is chain: " << (kdl_group->isChain() ? "Yes" : "No") << std::endl;
        std::cout << "Active joints: " << kdl_group->getActiveJointModels().size() << std::endl;
        std::cout << "All joints: " << kdl_group->getJointModels().size() << std::endl;
        std::cout << "Links: " << kdl_group->getLinkModels().size() << std::endl;
        
        std::cout << "\nActive joint details:" << std::endl;
        for (const auto* joint : kdl_group->getActiveJointModels()) {
            std::cout << "  - " << joint->getName() 
                      << " (type: " << joint->getTypeName() 
                      << ", DOF: " << joint->getVariableCount() << ")" << std::endl;
            
            // Print joint limits
            const auto& bounds = joint->getVariableBounds();
            for (size_t i = 0; i < bounds.size(); ++i) {
                std::cout << "    Variable " << i << ": [" 
                          << bounds[i].min_position_ << ", " 
                          << bounds[i].max_position_ << "]" << std::endl;
            }
        }
        
        std::cout << "\nLink details:" << std::endl;
        for (const auto* link : kdl_group->getLinkModels()) {
            std::cout << "  - " << link->getName();
            if (link->getParentJointModel()) {
                std::cout << " (parent joint: " << link->getParentJointModel()->getName() << ")";
            }
            auto shape_msgs = link->getShapes();
            if (!shape_msgs.empty()) {
                std::cout << " [" << shape_msgs.size() << " shapes]";
            }
            std::cout << std::endl;
        }
    }
    
    // Test forward kinematics
    std::cout << "\n=== Forward Kinematics Test ===" << std::endl;
    std::vector<double> zero_config(kdl_joint_names.size(), 0.0);
    std::vector<double> test_config = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.1};  // 8-DOF test angles for right arm
    
    std::vector<geometry_msgs::msg::Pose> poses;
    std::vector<std::string> tip_links = {tip_frame};
    
    // Test with zero configuration
    bool fk_zero = kdl_plugin->getPositionFK(tip_links, zero_config, poses);
    std::cout << "FK (zero config): " << (fk_zero ? "✓" : "✗") << std::endl;
    if (fk_zero && !poses.empty()) {
        const auto& pose = poses[0];
        std::cout << "  Position: [" << pose.position.x << ", " << pose.position.y << ", " << pose.position.z << "]" << std::endl;
        std::cout << "  Orientation: [" << pose.orientation.x << ", " << pose.orientation.y 
                  << ", " << pose.orientation.z << ", " << pose.orientation.w << "]" << std::endl;
    }
    
    // Test with non-zero configuration
    if (test_config.size() == kdl_joint_names.size()) {
        bool fk_test = kdl_plugin->getPositionFK(tip_links, test_config, poses);
        std::cout << "FK (8-DOF test config): " << (fk_test ? "✓" : "✗") << std::endl;
        if (fk_test && !poses.empty()) {
            const auto& pose = poses[0];
            std::cout << "  Position: [" << pose.position.x << ", " << pose.position.y << ", " << pose.position.z << "]" << std::endl;
            std::cout << "  Orientation: [" << pose.orientation.x << ", " << pose.orientation.y 
                      << ", " << pose.orientation.z << ", " << pose.orientation.w << "]" << std::endl;
        }
    }
    
    std::cout << "\n=== Test Complete ===" << std::endl;
    
    rclcpp::shutdown();
    return 0;
}