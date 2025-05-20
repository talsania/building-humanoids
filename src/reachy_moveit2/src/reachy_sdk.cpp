#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <sensor_msgs/msg/joint_state.hpp>
#include <std_msgs/msg/header.hpp>
#include <reachy_moveit2/msg/robot_control_command.hpp>
#include <reachy_moveit2/msg/add_obstacle.hpp>
#include <reachy_moveit2/msg/execute_request.hpp>
#include <shape_msgs/msg/solid_primitive.hpp>
#include <moveit/planning_scene_monitor/planning_scene_monitor.h>
#include <thread>
#include <chrono>
#include <memory>
#include <mutex>

using namespace std::chrono_literals;

class ReachyController : public rclcpp::Node
{
public:
  ReachyController()
  : Node("reachy_moveit2"),
    move_group_(std::shared_ptr<rclcpp::Node>(this), "dual_arm"), // Change "panda_arm" to your joint group name.
    planning_scene_interface_()
  {
    // Subscribers for custom topics.
    control_command_sub_ = this->create_subscription<reachy_moveit2::msg::RobotControlCommand>(
      "/robot_control_command", 10,
      std::bind(&ReachyController::controlCommandCallback, this, std::placeholders::_1));

    obstacle_sub_ = this->create_subscription<reachy_moveit2::msg::AddObstacle>(
      "/planning_scene_obstacle", 10,
      std::bind(&ReachyController::obstacleCallback, this, std::placeholders::_1));

    execute_request_sub_ = this->create_subscription<reachy_moveit2::msg::ExecuteRequest>(
      "/execute_request", 10,
      std::bind(&ReachyController::executeRequestCallback, this, std::placeholders::_1));

    // Adjust planning parameters.
    move_group_.setMaxVelocityScalingFactor(0.25);
    RCLCPP_INFO(this->get_logger(), "ReachyController initialized.");
  }

private:
  // MoveIt interfaces.
  moveit::planning_interface::MoveGroupInterface move_group_;
  moveit::planning_interface::PlanningSceneInterface planning_scene_interface_;

  // Latest control command stored.
  reachy_moveit2::msg::RobotControlCommand::SharedPtr latest_control_command_;
  std::mutex command_mutex_;

  // Subscribers.
  rclcpp::Subscription<reachy_moveit2::msg::RobotControlCommand>::SharedPtr control_command_sub_;
  rclcpp::Subscription<reachy_moveit2::msg::AddObstacle>::SharedPtr obstacle_sub_;
  rclcpp::Subscription<reachy_moveit2::msg::ExecuteRequest>::SharedPtr execute_request_sub_;

  // Callback for control command messages.
  void controlCommandCallback(const reachy_moveit2::msg::RobotControlCommand::SharedPtr msg)
  {
    std::lock_guard<std::mutex> lock(command_mutex_);
    latest_control_command_ = msg;
    RCLCPP_INFO(this->get_logger(), "Received control command in [%s] mode.", msg->mode.c_str());
  }

  // Callback for obstacle messages.
  void obstacleCallback(const reachy_moveit2::msg::AddObstacle::SharedPtr msg)
  {
    RCLCPP_INFO(this->get_logger(), "Received obstacle update for id [%s] with operation [%s].",
                msg->id.c_str(), msg->operation.c_str());
    if (msg->operation == "ADD")
    {
      // Create a CollisionObject message from the AddObstacle message.
      moveit_msgs::msg::CollisionObject collision_object;
      collision_object.header = msg->header;
      collision_object.id = msg->id;
      collision_object.primitives.push_back(msg->primitive);
      collision_object.primitive_poses.push_back(msg->pose.pose);
      collision_object.operation = collision_object.ADD;
      planning_scene_interface_.applyCollisionObjects({collision_object});
      RCLCPP_INFO(this->get_logger(), "Added obstacle [%s].", msg->id.c_str());
    }
    else if (msg->operation == "REMOVE")
    {
      planning_scene_interface_.removeCollisionObjects({msg->id});
      RCLCPP_INFO(this->get_logger(), "Removed obstacle [%s].", msg->id.c_str());
    }
    else
    {
      RCLCPP_WARN(this->get_logger(), "Unknown obstacle operation: [%s].", msg->operation.c_str());
    }
  }

  // Callback for execution request messages.
  void executeRequestCallback(const reachy_moveit2::msg::ExecuteRequest::SharedPtr msg)
  {
    RCLCPP_INFO(this->get_logger(), "Received execution request: [%s].", msg->command.c_str());
    if (msg->command == "EXECUTE")
    {
      std::lock_guard<std::mutex> lock(command_mutex_);
      if (!latest_control_command_)
      {
        RCLCPP_WARN(this->get_logger(), "No control command received to execute.");
        return;
      }
      processControlCommand(latest_control_command_);
      // Optionally clear the command after executing.
      latest_control_command_.reset();
    }
    else
    {
      RCLCPP_WARN(this->get_logger(), "Unknown execution command: [%s].", msg->command.c_str());
    }
  }

  // Process the stored control command.
  void processControlCommand(const reachy_moveit2::msg::RobotControlCommand::SharedPtr &command_msg)
  {
    moveit::planning_interface::MoveGroupInterface::Plan plan;
    bool success = false;
    if (command_msg->mode == "joint")
    {
      // For joint control, we expect the joint_state to contain the target joint positions.
      if (command_msg->joint_state.position.empty())
      {
        RCLCPP_ERROR(this->get_logger(), "Received joint control command with empty joint_state.");
        return;
      }
      // Set the joint target using the JointState message.
      move_group_.setJointValueTarget(command_msg->joint_state);
      RCLCPP_INFO(this->get_logger(), "Planning for joint control command...");
      success = (move_group_.plan(plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);
    }
    else if (command_msg->mode == "cartesian")
    {
      // For Cartesian control, we expect the cartesian_target field to contain the target pose.
      move_group_.setPoseTarget(command_msg->cartesian_target.pose);
      RCLCPP_INFO(this->get_logger(), "Planning for Cartesian control command...");
      success = (move_group_.plan(plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);
    }
    else
    {
      RCLCPP_ERROR(this->get_logger(), "Unknown control mode: [%s].", command_msg->mode.c_str());
      return;
    }

    if (success)
    {
      RCLCPP_INFO(this->get_logger(), "Plan computed successfully, executing...");
      auto exec_result = move_group_.execute(plan);
      if (exec_result != moveit::core::MoveItErrorCode::SUCCESS)
      {
        RCLCPP_ERROR(this->get_logger(), "Execution failed with error code: %d", exec_result.val);
      }
      else
      {
        RCLCPP_INFO(this->get_logger(), "Motion executed successfully.");
      }
    }
    else
    {
      RCLCPP_ERROR(this->get_logger(), "Planning failed for the control command.");
    }
  }
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto controller_node = std::make_shared<ReachyController>();

  // Use a multi-threaded executor if needed.
  rclcpp::spin(controller_node);
  rclcpp::shutdown();
  return 0;
}
