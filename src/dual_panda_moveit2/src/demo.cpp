#include <chrono>
#include <geometry_msgs/msg/pose.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <iostream>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit/robot_model/robot_model.h>
#include <moveit/robot_model_loader/robot_model_loader.h>
#include <moveit/robot_state/robot_state.h>
#include <rclcpp/rclcpp.hpp>
#include <thread>
#include <vector>

// Include your custom message
#include "dual_panda_moveit2_interface/msg/robot_pose.hpp"  // Adjust based on your package name

using namespace std::chrono_literals;

class ReachyController
{
public:
  ReachyController(const rclcpp::Node::SharedPtr &node)
      : node_(node),
        move_group_(node, "dual_arm"),
        left_gripper_(node, "left_gripper"),
        right_gripper_(node, "right_gripper"),
        head_group_(node, "head"),
        planning_scene_interface_()
  {
    move_group_.setMaxVelocityScalingFactor(0.5);
    left_gripper_.setMaxVelocityScalingFactor(0.5);
    right_gripper_.setMaxVelocityScalingFactor(0.5);
    head_group_.setMaxVelocityScalingFactor(0.5);

    planning_scene_publisher_ = node_->create_publisher<moveit_msgs::msg::PlanningScene>(
        "/planning_scene", rclcpp::QoS(10));

    robot_pose_pub_ = node_->create_publisher<dual_panda_moveit2_interface::msg::RobotPose>(
        "/robot_pose", rclcpp::QoS(10));
  }

  void execute()
  {
    waitForValidState(move_group_);
    waitForValidState(left_gripper_);
    waitForValidState(right_gripper_);
    waitForValidState(head_group_);

    timer_ = node_->create_wall_timer(
        100ms, std::bind(&ReachyController::publishCurrentPose, this));
  }

private:
  rclcpp::Node::SharedPtr node_;
  moveit::planning_interface::MoveGroupInterface move_group_;
  moveit::planning_interface::MoveGroupInterface left_gripper_;
  moveit::planning_interface::MoveGroupInterface right_gripper_;
  moveit::planning_interface::MoveGroupInterface head_group_;
  moveit::planning_interface::PlanningSceneInterface planning_scene_interface_;
  rclcpp::Publisher<moveit_msgs::msg::PlanningScene>::SharedPtr planning_scene_publisher_;
  rclcpp::Publisher<dual_panda_moveit2_interface::msg::RobotPose>::SharedPtr robot_pose_pub_;
  rclcpp::TimerBase::SharedPtr timer_;

  void waitForValidState(moveit::planning_interface::MoveGroupInterface &group)
  {
    RCLCPP_INFO(node_->get_logger(), "Waiting for valid initial state of %s...",
                group.getName().c_str());
    group.startStateMonitor();
    auto current_state = group.getCurrentState(10.0);
    if (!current_state)
    {
      RCLCPP_ERROR(node_->get_logger(),
                   "Failed to get valid initial state for %s!",
                   group.getName().c_str());
      throw std::runtime_error("Invalid initial state");
    }
  }

  void publishCurrentPose()
  {
    auto left_pose = move_group_.getCurrentPose("l_arm_tip");
    auto right_pose = move_group_.getCurrentPose("r_arm_tip");
    auto head_pose = head_group_.getCurrentPose();

    dual_panda_moveit2_interface::msg::RobotPose pose_msg;
    pose_msg.left_pose = left_pose;
    pose_msg.right_pose = right_pose;
    pose_msg.head = head_pose;

    robot_pose_pub_->publish(pose_msg);

    // Optional logging
    RCLCPP_DEBUG(node_->get_logger(), "Published robot poses.");
  }
};

int main(int argc, char **argv)
{
  try
  {
    rclcpp::init(argc, argv);
    rclcpp::NodeOptions options =
        rclcpp::NodeOptions().allow_undeclared_parameters(true).use_intra_process_comms(true).parameter_overrides({
          {"use_sim_time", rclcpp::ParameterValue(true)}
      });;
    auto node = std::make_shared<rclcpp::Node>("bimanual_control", options);

    auto parameters_client =
        std::make_shared<rclcpp::SyncParametersClient>(node, "/move_group");
    while (!parameters_client->wait_for_service(1s))
    {
      if (!rclcpp::ok())
      {
        RCLCPP_ERROR(node->get_logger(),
                     "Interrupted while waiting for parameter service.");
        rclcpp::shutdown();
        return 1;
      }
      RCLCPP_INFO(node->get_logger(), "Waiting for parameter service...");
    }

    auto param_list = parameters_client->list_parameters(
        {"robot_description_kinematics"}, 10);
    auto params = parameters_client->get_parameters(param_list.names);
    node->set_parameters(params);

    auto executor =
        std::make_shared<rclcpp::executors::SingleThreadedExecutor>();
    executor->add_node(node);
    std::thread executor_thread([executor]()
                                { executor->spin(); });

    ReachyController controller(node);
    controller.execute();

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
