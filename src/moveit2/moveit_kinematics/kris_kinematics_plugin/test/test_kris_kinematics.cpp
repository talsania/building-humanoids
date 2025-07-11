#include <gtest/gtest.h>
#include <rclcpp/rclcpp.hpp>
#include <moveit/robot_model_loader/robot_model_loader.h>
#include <moveit/kris_kinematics_plugin/kris_kinematics_plugin.h>

class KrisKinematicsTest : public ::testing::Test
{
protected:
  void SetUp() override
  {
    // Initialize ROS
    rclcpp::init(0, nullptr);
    node_ = rclcpp::Node::make_shared("kris_kinematics_test");
    
    // Load robot model
    robot_model_loader_ = std::make_shared<robot_model_loader::RobotModelLoader>(node_);
    robot_model_ = robot_model_loader_->getModel();
    
    if (!robot_model_)
    {
      GTEST_SKIP() << "No robot model loaded - skipping Kris kinematics tests";
    }
    
    // Initialize kinematics plugin
    plugin_ = std::make_unique<kris_kinematics_plugin::KrisKinematicsPlugin>();
    
    // Get the first planning group (adjust this for your robot)
    auto group_names = robot_model_->getJointModelGroupNames();
    if (group_names.empty())
    {
      GTEST_SKIP() << "No planning groups found - skipping Kris kinematics tests";
    }
    
    group_name_ = group_names[0];  // Use first group, or specify your group name
    
    // Get group info
    const auto* jmg = robot_model_->getJointModelGroup(group_name_);
    if (!jmg)
    {
      GTEST_SKIP() << "Could not find joint model group: " << group_name_;
    }
    
    // Get base frame and tip frame
    base_frame_ = robot_model_->getModelFrame();
    
    // Get tip frame (last link in the chain)
    const auto& link_names = jmg->getLinkModelNames();
    if (link_names.empty())
    {
      GTEST_SKIP() << "No links found in group: " << group_name_;
    }
    tip_frame_ = link_names.back();
    
    // Initialize plugin
    std::vector<std::string> tip_frames = {tip_frame_};
    bool success = plugin_->initialize(node_, *robot_model_, group_name_, 
                                       base_frame_, tip_frames, 0.01);
    
    if (!success)
    {
      GTEST_SKIP() << "Failed to initialize kinematics plugin";
    }
    
    // Get joint names and create test configuration
    joint_names_ = plugin_->getJointNames();
    
    // Create a test joint configuration (all zeros for now)
    test_joint_angles_.resize(joint_names_.size(), 0.0);
  }
  
  void TearDown() override
  {
    rclcpp::shutdown();
  }
  
  rclcpp::Node::SharedPtr node_;
  std::shared_ptr<robot_model_loader::RobotModelLoader> robot_model_loader_;
  moveit::core::RobotModelPtr robot_model_;
  std::unique_ptr<kris_kinematics_plugin::KrisKinematicsPlugin> plugin_;
  
  std::string group_name_;
  std::string base_frame_;
  std::string tip_frame_;
  std::vector<std::string> joint_names_;
  std::vector<double> test_joint_angles_;
};

TEST_F(KrisKinematicsTest, BasicFunctionality)
{
  // Test that we can get basic information
  EXPECT_FALSE(plugin_->getJointNames().empty()) << "Joint names should not be empty";
  EXPECT_FALSE(plugin_->getLinkNames().empty()) << "Link names should not be empty";
  
  std::cout << "Plugin initialized with " << joint_names_.size() << " joints" << std::endl;
  std::cout << "Group: " << group_name_ << std::endl;
  std::cout << "Base frame: " << base_frame_ << std::endl;
  std::cout << "Tip frame: " << tip_frame_ << std::endl;
}

TEST_F(KrisKinematicsTest, ComputeJacobian)
{
  Eigen::MatrixXd jacobian;
  
  // Test basic Jacobian computation
  bool success = plugin_->getJacobian(test_joint_angles_, jacobian);
  
  EXPECT_TRUE(success) << "Failed to compute Jacobian";
  
  if (success)
  {
    // Check Jacobian dimensions
    EXPECT_EQ(jacobian.rows(), 6) << "Jacobian should have 6 rows (3 position + 3 orientation)";
    EXPECT_EQ(jacobian.cols(), static_cast<int>(test_joint_angles_.size())) 
        << "Jacobian should have " << test_joint_angles_.size() << " columns";
    
    // Check that Jacobian is not all zeros
    double jacobian_norm = jacobian.norm();
    EXPECT_GT(jacobian_norm, 1e-6) << "Jacobian should not be all zeros";
    
    // Print some debug info
    std::cout << "Jacobian dimensions: " << jacobian.rows() << "x" << jacobian.cols() << std::endl;
    std::cout << "Jacobian norm: " << jacobian_norm << std::endl;
    std::cout << "Test joint angles: ";
    for (size_t i = 0; i < test_joint_angles_.size(); ++i)
    {
      std::cout << test_joint_angles_[i] << " ";
    }
    std::cout << std::endl;
  }
}

TEST_F(KrisKinematicsTest, ForwardKinematics)
{
  // Test that forward kinematics works with our test configuration
  std::vector<std::string> link_names = {tip_frame_};
  std::vector<geometry_msgs::msg::Pose> poses;
  
  bool success = plugin_->getPositionFK(link_names, test_joint_angles_, poses);
  
  EXPECT_TRUE(success) << "Forward kinematics failed";
  
  if (success && !poses.empty())
  {
    const auto& pose = poses[0];
    
    // Check that pose is reasonable (not NaN, not at origin unless expected)
    EXPECT_FALSE(std::isnan(pose.position.x)) << "Pose position x is NaN";
    EXPECT_FALSE(std::isnan(pose.position.y)) << "Pose position y is NaN";
    EXPECT_FALSE(std::isnan(pose.position.z)) << "Pose position z is NaN";
    
    EXPECT_FALSE(std::isnan(pose.orientation.x)) << "Pose orientation x is NaN";
    EXPECT_FALSE(std::isnan(pose.orientation.y)) << "Pose orientation y is NaN";
    EXPECT_FALSE(std::isnan(pose.orientation.z)) << "Pose orientation z is NaN";
    EXPECT_FALSE(std::isnan(pose.orientation.w)) << "Pose orientation w is NaN";
    
    // Check quaternion normalization
    double quat_norm = sqrt(pose.orientation.x * pose.orientation.x +
                           pose.orientation.y * pose.orientation.y +
                           pose.orientation.z * pose.orientation.z +
                           pose.orientation.w * pose.orientation.w);
    
    EXPECT_NEAR(quat_norm, 1.0, 1e-6) << "Quaternion is not normalized";
    
    std::cout << "End-effector pose: [" 
              << pose.position.x << ", " << pose.position.y << ", " << pose.position.z << "] "
              << "[" << pose.orientation.x << ", " << pose.orientation.y << ", " 
              << pose.orientation.z << ", " << pose.orientation.w << "]" << std::endl;
  }
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}