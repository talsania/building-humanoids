#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <geometry_msgs/msg/pose.hpp>
#include <moveit/robot_model_loader/robot_model_loader.h>
#include <moveit/robot_model/robot_model.h>
#include <moveit/robot_state/robot_state.h>
#include <thread>
#include <chrono>
#include <vector>
#include <iostream>

using namespace std::chrono_literals;

class DualPandaController
{
public:
  DualPandaController(const rclcpp::Node::SharedPtr &node)
    : node_(node),
      move_group_(node, "dual_arms"),
      planning_scene_interface_()
  {
    // Adjust planning parameters as needed.
    move_group_.setMaxVelocityScalingFactor(0.25);
    // Other planning parameters (planning time, tolerances, etc.) can be set here.
  }

  void execute()
  {
    try
    {
      waitForValidState();

      // Set an initial joint state for the robot (optional)
      std::vector<double> joint_values = {
          -1.6487, // left_panda_joint1
          -0.785,  // left_panda_joint2
          0.0,     // left_panda_joint3
          -2.356,  // left_panda_joint4
          0.0,     // left_panda_joint5
          1.571,   // left_panda_joint6
          0.785,   // left_panda_joint7
          -1.6487, // right_panda_joint1
          -0.785,  // right_panda_joint2
          0.0,     // right_panda_joint3
          -0.356,  // right_panda_joint4
          0.0,     // right_panda_joint5
          1.571,   // right_panda_joint6
          0.785    // right_panda_joint7
      };
      setJointStates(joint_values);

      // sleep for a few seconds to allow the robot to settle

      std::this_thread::sleep_for(2s);

      joint_values = {
          1.6487, // left_panda_joint1
          0.785,  // left_panda_joint2
          0.5,     // left_panda_joint3
          2.356,  // left_panda_joint4
          0.5,     // left_panda_joint5
          -1.571,   // left_panda_joint6
          -0.785,   // left_panda_joint7
          1.6487, // right_panda_joint1
          0.785,  // right_panda_joint2
          0.5,     // right_panda_joint3
          2.356,  // right_panda_joint4
          0.5,     // right_panda_joint5
          -1.571,   // right_panda_joint6
          -0.785    // right_panda_joint7
      };

      setJointStates(joint_values);
      // // Get and print the current end-effector poses
      // auto [left_pose, right_pose] = getCurrentPoses();
      // printRobotState(left_pose, right_pose);

      // // Example Cartesian target poses for the left and right arms.
      // geometry_msgs::msg::Pose left_target_pose = left_pose;
      // left_target_pose.position.x = 0.023918;
      // left_target_pose.position.y = -0.406114;
      // left_target_pose.position.z = 0.59029;
      // // Adjust orientation as needed.

      // geometry_msgs::msg::Pose right_target_pose;
      // right_target_pose.position.x = 0.476093;
      // right_target_pose.position.y = -0.30611;
      // right_target_pose.position.z = 0.59029;
      // right_target_pose.orientation.w = -4.22935e-05;  // Adjust orientation as needed.

      // // Convert Cartesian targets into joint states using the KDL-based IK.
      // setTargetPose(left_target_pose, right_target_pose);

      // RCLCPP_INFO(node_->get_logger(), "Robot motion complete!");

      // // Get and print the updated end-effector poses.
      // left_pose = getCurrentPoses().first;
      // printRobotState(left_pose, right_pose);
    }
    catch (const std::exception &e)
    {
      RCLCPP_FATAL(node_->get_logger(), "Critical error in execution: %s", e.what());
    }
    catch (...)
    {
      RCLCPP_FATAL(node_->get_logger(), "Unknown critical error in execution.");
    }
  }

private:
  rclcpp::Node::SharedPtr node_;
  moveit::planning_interface::MoveGroupInterface move_group_;
  moveit::planning_interface::PlanningSceneInterface planning_scene_interface_;

  void waitForValidState()
  {
    RCLCPP_INFO(node_->get_logger(), "Waiting for valid initial state...");
    move_group_.startStateMonitor();
    auto current_state = move_group_.getCurrentState(10.0);
    if (!current_state)
    {
      RCLCPP_ERROR(node_->get_logger(), "Failed to get valid initial state within timeout!");
      throw std::runtime_error("Invalid initial state");
    }
  }

  moveit::core::RobotStatePtr getCurrentState()
  {
    auto current_state = move_group_.getCurrentState(10.0);
    if (!current_state)
    {
      RCLCPP_ERROR(node_->get_logger(), "Failed to retrieve current state!");
      throw std::runtime_error("Invalid current state");
    }
    return current_state;
  }

  std::pair<geometry_msgs::msg::Pose, geometry_msgs::msg::Pose> getCurrentPoses()
  {
    geometry_msgs::msg::Pose left_pose = move_group_.getCurrentPose("left_panda_link8").pose;
    geometry_msgs::msg::Pose right_pose = move_group_.getCurrentPose("right_panda_link8").pose;
    return {left_pose, right_pose};
  }

  void printRobotState(const geometry_msgs::msg::Pose &left_pose,
                       const geometry_msgs::msg::Pose &right_pose)
  {
    std::cout << "\nCurrent Pose State:" << std::endl;
    std::cout << "Left End-Effector Pose:" << std::endl;
    std::cout << "  Position - x: " << left_pose.position.x
              << ", y: " << left_pose.position.y
              << ", z: " << left_pose.position.z << std::endl;
    std::cout << "  Orientation - x: " << left_pose.orientation.x
              << ", y: " << left_pose.orientation.y
              << ", z: " << left_pose.orientation.z
              << ", w: " << left_pose.orientation.w << std::endl;

    std::cout << "Right End-Effector Pose:" << std::endl;
    std::cout << "  Position - x: " << right_pose.position.x
              << ", y: " << right_pose.position.y
              << ", z: " << right_pose.position.z << std::endl;
    std::cout << "  Orientation - x: " << right_pose.orientation.x
              << ", y: " << right_pose.orientation.y
              << ", z: " << right_pose.orientation.z
              << ", w: " << right_pose.orientation.w << std::endl;
  }

  void setJointStates(const std::vector<double> &joint_values)
  {
    auto current_state = move_group_.getCurrentState();
    if (!current_state)
    {
      RCLCPP_ERROR(node_->get_logger(), "Failed to get current state for setting joint values!");
      throw std::runtime_error("Invalid current state in setJointStates");
    }

    const std::vector<std::string> &joint_names = move_group_.getJointNames();
    if (joint_values.size() != joint_names.size())
    {
      RCLCPP_ERROR(node_->get_logger(), "Mismatch between joint values size and joint names size!");
      throw std::runtime_error("Joint values size mismatch");
    }

    moveit::core::RobotState &robot_state = *current_state;
    robot_state.setVariablePositions(joint_names, joint_values);
    move_group_.setJointValueTarget(robot_state);

    moveit::planning_interface::MoveGroupInterface::Plan plan;
    bool success = static_cast<bool>(move_group_.plan(plan));
    if (success)
    {
      RCLCPP_INFO(node_->get_logger(), "Plan computed successfully for joint state setting, executing...");
      auto execute_result = move_group_.execute(plan);
      if (execute_result != moveit::core::MoveItErrorCode::SUCCESS)
      {
        RCLCPP_ERROR(node_->get_logger(), "Execution failed with error code: %d", execute_result.val);
        throw std::runtime_error("Execution failure in setJointStates");
      }
      RCLCPP_INFO(node_->get_logger(), "Plan executed successfully for joint state setting.");
    }
    else
    {
      RCLCPP_ERROR(node_->get_logger(), "Planning failed in setJointStates!");
      throw std::runtime_error("Planning failure in setJointStates");
    }
  }

  void setTargetPose(const geometry_msgs::msg::Pose &left_target_pose,
                     const geometry_msgs::msg::Pose &right_target_pose)
  {
    robot_model_loader::RobotModelLoader robot_model_loader(node_);
    const moveit::core::RobotModelPtr &kinematic_model = robot_model_loader.getModel();
    if (!kinematic_model)
    {
      RCLCPP_ERROR(node_->get_logger(), "Failed to load robot model!");
      throw std::runtime_error("Robot model loading failed");
    }
    RCLCPP_INFO(node_->get_logger(), "Model frame: %s", kinematic_model->getModelFrame().c_str());
    moveit::core::RobotStatePtr robot_state(new moveit::core::RobotState(kinematic_model));
    robot_state->setToDefaultValues();
    const moveit::core::JointModelGroup *left_group = kinematic_model->getJointModelGroup("left_arm");
    const moveit::core::JointModelGroup *right_group = kinematic_model->getJointModelGroup("right_arm");

    if (!left_group || !right_group)
    {
      RCLCPP_ERROR(node_->get_logger(), "Failed to retrieve joint model groups!");
      throw std::runtime_error("Missing joint model groups");
    }

    RCLCPP_INFO(node_->get_logger(), "Left group: %s", left_group->getName().c_str());

    bool found_ik_left = robot_state->setFromIK(left_group, left_target_pose, 0.1);
    bool found_ik_right = robot_state->setFromIK(right_group, right_target_pose, 0.1);
    if (!(found_ik_left && found_ik_right))
    {
      RCLCPP_ERROR(node_->get_logger(), "IK solution not found for one or both arms!");
      throw std::runtime_error("IK solution failure in setTargetPose");
    }

    RCLCPP_INFO(node_->get_logger(), "IK solution found for both arms, setting joint target...");
    move_group_.setJointValueTarget(*robot_state);

    moveit::planning_interface::MoveGroupInterface::Plan plan;
    bool success = static_cast<bool>(move_group_.plan(plan));
    if (success)
    {
      RCLCPP_INFO(node_->get_logger(), "Plan computed successfully for target pose, executing...");
      auto execute_result = move_group_.execute(plan);
      if (execute_result != moveit::core::MoveItErrorCode::SUCCESS)
      {
        RCLCPP_ERROR(node_->get_logger(), "Execution failed with error code: %d", execute_result.val);
        throw std::runtime_error("Execution failure in setTargetPose");
      }
      RCLCPP_INFO(node_->get_logger(), "Plan executed successfully for target pose.");
    }
    else
    {
      RCLCPP_ERROR(node_->get_logger(), "Planning failed in setTargetPose!");
      throw std::runtime_error("Planning failure in setTargetPose");
    }
  }
};

int main(int argc, char **argv)
{
  try
  {
    rclcpp::init(argc, argv);

    rclcpp::NodeOptions options = rclcpp::NodeOptions().allow_undeclared_parameters(true);
    auto node = std::make_shared<rclcpp::Node>("bimanual_control", options);

    // Get all kinematics parameters from the move_group node.
    auto parameters_client = std::make_shared<rclcpp::SyncParametersClient>(node, "/move_group");
    while (!parameters_client->wait_for_service(1s))
    {
      if (!rclcpp::ok())
      {
        RCLCPP_ERROR(node->get_logger(), "Interrupted while waiting for the parameters service. Exiting.");
        rclcpp::shutdown();
        return 1;
      }
      RCLCPP_INFO(node->get_logger(), "Parameters service not available, waiting...");
    }
    rcl_interfaces::msg::ListParametersResult parameter_list = parameters_client->list_parameters({"robot_description_kinematics"}, 10);
    auto parameters = parameters_client->get_parameters(parameter_list.names);

    // Set the retrieved parameters to our node.
    node->set_parameters(parameters);

    auto executor = std::make_shared<rclcpp::executors::SingleThreadedExecutor>();
    executor->add_node(node);
    std::thread executor_thread([executor]() { executor->spin(); });

    DualPandaController controller(node);
    controller.execute();

    executor->cancel();
    executor_thread.join();
    rclcpp::shutdown();
    return 0;
  }
  catch (const std::exception &e)
  {
    std::cerr << "Fatal error in main: " << e.what() << std::endl;
    rclcpp::shutdown();
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown fatal error in main." << std::endl;
    rclcpp::shutdown();
    return 1;
  }
}
