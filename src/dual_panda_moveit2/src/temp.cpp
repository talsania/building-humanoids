#include <chrono>
#include <geometry_msgs/msg/pose.hpp>
#include <iostream>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit/robot_model/robot_model.h>
#include <moveit/robot_model_loader/robot_model_loader.h>
#include <moveit/robot_state/robot_state.h>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <thread>
#include <vector>

#include "dual_panda_moveit2_interface/action/move.hpp"
#include "dual_panda_moveit2_interface/srv/gripper_control.hpp"
#include "dual_panda_moveit2_interface/srv/spawn_object.hpp"
#include "dual_panda_moveit2_interface/srv/remove_object.hpp"
#include "dual_panda_moveit2_interface/srv/attach_object.hpp"
#include "dual_panda_moveit2_interface/srv/detach_object.hpp"
#include "dual_panda_moveit2_interface/msg/robot_pose.hpp"
#include "dual_panda_moveit2_interface/msg/object_spec.hpp"
#include "dual_panda_moveit2_interface/msg/spawn_batch.hpp"
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>

using namespace std::chrono_literals;
using namespace dual_panda_moveit2_interface::srv;
using namespace dual_panda_moveit2_interface::action;

// Utility function to wait for a valid robot state before querying it
void waitForValidRobotState(moveit::planning_interface::MoveGroupInterface &group,
                            const rclcpp::Node::SharedPtr &node,
                            const std::string &eef_link,
                            const std::chrono::duration<double> &timeout = 5.0s)
{
  auto start = node->now();
  while (rclcpp::ok() && (node->now() - start).seconds() < timeout.count())
  {
    auto pose_stamped = group.getCurrentPose(eef_link);
    // Check if the header stamp is not zero.
    if (pose_stamped.header.stamp.sec != 0 || pose_stamped.header.stamp.nanosec != 0)
    {
      return; // Valid state obtained.
    }
    std::this_thread::sleep_for(100ms);
  }
  throw std::runtime_error("Failed to obtain a valid robot state within the timeout period.");
}

class ReachyController
{
public:
  ReachyController(const rclcpp::Node::SharedPtr &node)
      : node_(node), move_group_(node, "dual_arm"),
        head_group_(node, "head"),
        left_gripper_(node, "left_gripper"),
        right_gripper_(node, "right_gripper"),
        tf_buffer_(node_->get_clock()),
        tf_listener_(tf_buffer_),
        planning_scene_interface_()
  {
    move_group_.setMaxVelocityScalingFactor(0.5);
    left_gripper_.setMaxVelocityScalingFactor(0.5);
    right_gripper_.setMaxVelocityScalingFactor(0.5);
    head_group_.setMaxVelocityScalingFactor(0.5);
    planning_scene_publisher_ =
        node_->create_publisher<moveit_msgs::msg::PlanningScene>(
            "/planning_scene", rclcpp::QoS(10));
  }

  moveit::planning_interface::MoveGroupInterface move_group_;
  moveit::planning_interface::MoveGroupInterface left_gripper_;
  moveit::planning_interface::MoveGroupInterface right_gripper_;
  moveit::planning_interface::MoveGroupInterface head_group_;

  std::vector<moveit_msgs::msg::CollisionObject> getCurrentCollisionObjects()
  {
    std::map<std::string, moveit_msgs::msg::CollisionObject> obj_map = planning_scene_interface_.getObjects();
    std::vector<moveit_msgs::msg::CollisionObject> objects;
  
    for (const auto& pair : obj_map)
    {
      objects.push_back(pair.second);
    }
  
    return objects;
  }

  void setJointStates(moveit::planning_interface::MoveGroupInterface &group,
                      const std::vector<double> &joint_values)
  {
    auto current_state = group.getCurrentState();
    if (!current_state)
      throw std::runtime_error("Invalid current state");
    const auto &joint_names = group.getJointNames();
    if (joint_values.size() != joint_names.size())
      throw std::runtime_error("Joint values size mismatch");
    current_state->setVariablePositions(joint_names, joint_values);
    group.setJointValueTarget(*current_state);
    moveit::planning_interface::MoveGroupInterface::Plan plan;
    if (!group.plan(plan))
      throw std::runtime_error("Planning failure");
    if (group.execute(plan) != moveit::core::MoveItErrorCode::SUCCESS)
      throw std::runtime_error("Execution failure");
  }

  void controlGripper(moveit::planning_interface::MoveGroupInterface &gripper,
                      bool open)
  {
    std::vector<double> values;
    values = open ? ((gripper.getName() == "left_gripper") ? std::vector<double>{1.2} : std::vector<double>{-1.2})
                  : ((gripper.getName() == "left_gripper") ? std::vector<double>{-0.30} : std::vector<double>{0.30});
    setJointStates(gripper, values);
  }


  void setTargetPose(const geometry_msgs::msg::Pose &left_target_pose_in_head,
      const geometry_msgs::msg::Pose &right_target_pose_in_head)
  {
    // Transform poses to base frame
    geometry_msgs::msg::PoseStamped left_in_head, right_in_head;
    left_in_head.header.frame_id = "head";
    right_in_head.header.frame_id = "head";
    left_in_head.header.stamp = node_->now();
    right_in_head.header.stamp = node_->now();
    geometry_msgs::msg::PoseStamped current_left_pose_stamped, current_right_pose_stamped;
    current_left_pose_stamped.header.frame_id = "world";
    current_right_pose_stamped.header.frame_id = "world";
    current_left_pose_stamped.header.stamp = node_->now();
    current_right_pose_stamped.header.stamp = node_->now();
    current_left_pose_stamped.pose = move_group_.getCurrentPose("l_arm_tip").pose;
    current_right_pose_stamped.pose = move_group_.getCurrentPose("r_arm_tip").pose;

    geometry_msgs::msg::PoseStamped current_left_pose_in_head, current_right_pose_in_head;
    try
    {
      current_left_pose_in_head = tf_buffer_.transform(current_left_pose_stamped, "head", tf2::durationFromSec(0.5));
      current_right_pose_in_head = tf_buffer_.transform(current_right_pose_stamped, "head", tf2::durationFromSec(0.5));
    }
    catch (tf2::TransformException &ex)
    {
      RCLCPP_ERROR(node_->get_logger(), "TF transform failed: %s", ex.what());
      throw std::runtime_error("TF transform failed");
    }

    geometry_msgs::msg::Pose current_left_pose = current_left_pose_in_head.pose;
    geometry_msgs::msg::Pose current_right_pose = current_right_pose_in_head.pose;

    // Check for NaN values in the left target pose and replace them with current pose values
    left_in_head.pose.position.x = std::isnan(left_target_pose_in_head.position.x) ? current_left_pose.position.x : left_target_pose_in_head.position.x;
    left_in_head.pose.position.y = std::isnan(left_target_pose_in_head.position.y) ? current_left_pose.position.y : left_target_pose_in_head.position.y;
    left_in_head.pose.position.z = std::isnan(left_target_pose_in_head.position.z) ? current_left_pose.position.z : left_target_pose_in_head.position.z;

    left_in_head.pose.orientation.x = std::isnan(left_target_pose_in_head.orientation.x) ? current_left_pose.orientation.x : left_target_pose_in_head.orientation.x;
    left_in_head.pose.orientation.y = std::isnan(left_target_pose_in_head.orientation.y) ? current_left_pose.orientation.y : left_target_pose_in_head.orientation.y;
    left_in_head.pose.orientation.z = std::isnan(left_target_pose_in_head.orientation.z) ? current_left_pose.orientation.z : left_target_pose_in_head.orientation.z;
    left_in_head.pose.orientation.w = std::isnan(left_target_pose_in_head.orientation.w) ? current_left_pose.orientation.w : left_target_pose_in_head.orientation.w;

    // Check for NaN values in the right target pose and replace them with current pose values
    right_in_head.pose.position.x = std::isnan(right_target_pose_in_head.position.x) ? current_right_pose.position.x : right_target_pose_in_head.position.x;
    right_in_head.pose.position.y = std::isnan(right_target_pose_in_head.position.y) ? current_right_pose.position.y : right_target_pose_in_head.position.y;
    right_in_head.pose.position.z = std::isnan(right_target_pose_in_head.position.z) ? current_right_pose.position.z : right_target_pose_in_head.position.z;

    right_in_head.pose.orientation.x = std::isnan(right_target_pose_in_head.orientation.x) ? current_right_pose.orientation.x : right_target_pose_in_head.orientation.x;
    right_in_head.pose.orientation.y = std::isnan(right_target_pose_in_head.orientation.y) ? current_right_pose.orientation.y : right_target_pose_in_head.orientation.y;
    right_in_head.pose.orientation.z = std::isnan(right_target_pose_in_head.orientation.z) ? current_right_pose.orientation.z : right_target_pose_in_head.orientation.z;
    right_in_head.pose.orientation.w = std::isnan(right_target_pose_in_head.orientation.w) ? current_right_pose.orientation.w : right_target_pose_in_head.orientation.w;

    geometry_msgs::msg::PoseStamped left_transformed, right_transformed;

    try
    {
      left_transformed = tf_buffer_.transform(left_in_head, "world", tf2::durationFromSec(0.5));
      right_transformed = tf_buffer_.transform(right_in_head, "world", tf2::durationFromSec(0.5));
    }
    catch (tf2::TransformException &ex)
    {
      RCLCPP_ERROR(node_->get_logger(), "TF transform failed: %s", ex.what());
      throw std::runtime_error("TF transform failed");
    }

    // Proceed as before but with transformed poses
    moveit::planning_interface::MoveGroupInterface::Plan plan;
    robot_model_loader::RobotModelLoader robot_model_loader(node_);
    const auto &kinematic_model = robot_model_loader.getModel();
    if (!kinematic_model)
      throw std::runtime_error("Robot model loading failed");

    moveit::core::RobotStatePtr robot_state(new moveit::core::RobotState(kinematic_model));
    robot_state->setToDefaultValues();

    const auto *left_group = kinematic_model->getJointModelGroup("left_arm");
    const auto *right_group = kinematic_model->getJointModelGroup("right_arm");
    if (!left_group || !right_group)
      throw std::runtime_error("Missing joint model groups");

    bool found_ik_left = robot_state->setFromIK(left_group, left_transformed.pose, 0.1);
    bool found_ik_right = robot_state->setFromIK(right_group, right_transformed.pose, 0.1);
    if (!found_ik_left && !found_ik_right)
      throw std::runtime_error("IK failure both");
    else if (!found_ik_left)
      throw std::runtime_error("IK failure left");
    else if (!found_ik_right)
      throw std::runtime_error("IK failure right");
 
    move_group_.setJointValueTarget(*robot_state);
    if (!move_group_.plan(plan))
      throw std::runtime_error("Planning failure");

    if (move_group_.execute(plan) != moveit::core::MoveItErrorCode::SUCCESS)
      throw std::runtime_error("Execution failure");
  }

  void setHeadTargetPose(const geometry_msgs::msg::Pose &head_target_pose)
  {
    // Transform pose to base frame
    geometry_msgs::msg::PoseStamped head;
    head.header.frame_id = "world";
    head.header.stamp = node_->now();
    // Get the current head pose
    geometry_msgs::msg::Pose current_head_pose = head_group_.getCurrentPose().pose;

    // Check for NaN values in the target pose and replace them with current pose values
    head.pose.position.x = std::isnan(head_target_pose.position.x) ? current_head_pose.position.x : head_target_pose.position.x;
    head.pose.position.y = std::isnan(head_target_pose.position.y) ? current_head_pose.position.y : head_target_pose.position.y;
    head.pose.position.z = std::isnan(head_target_pose.position.z) ? current_head_pose.position.z : head_target_pose.position.z;

    head.pose.orientation.x = std::isnan(head_target_pose.orientation.x) ? current_head_pose.orientation.x : head_target_pose.orientation.x;
    head.pose.orientation.y = std::isnan(head_target_pose.orientation.y) ? current_head_pose.orientation.y : head_target_pose.orientation.y;
    head.pose.orientation.z = std::isnan(head_target_pose.orientation.z) ? current_head_pose.orientation.z : head_target_pose.orientation.z;
    head.pose.orientation.w = std::isnan(head_target_pose.orientation.w) ? current_head_pose.orientation.w : head_target_pose.orientation.w;

    // Proceed as before but with transformed pose
    moveit::planning_interface::MoveGroupInterface::Plan plan;

    robot_model_loader::RobotModelLoader robot_model_loader(node_);
    const auto &kinematic_model = robot_model_loader.getModel();
    if (!kinematic_model)
      throw std::runtime_error("Robot model loading failed");

    moveit::core::RobotStatePtr robot_state(new moveit::core::RobotState(kinematic_model));
    robot_state->setToDefaultValues();

    const auto *head_group = kinematic_model->getJointModelGroup("head");

    if (!head_group)
      throw std::runtime_error("Missing head joint model group");

    bool found_ik_head = robot_state->setFromIK(head_group, head.pose, 0.1);

    if (!found_ik_head)
      throw std::runtime_error("IK failure for head");

    head_group_.setJointValueTarget(*robot_state);
    if (!head_group_.plan(plan))
      throw std::runtime_error("Head planning failure");

    if (head_group_.execute(plan) != moveit::core::MoveItErrorCode::SUCCESS)
      throw std::runtime_error("Head execution failure");
  }


  void objectSpawnBatch(const std::vector<std::string> &ids,
      const std::vector<std::string> &types,
      const std::vector<std::vector<double>> &dims,
      const std::vector<geometry_msgs::msg::Pose> &poses)
  {
  std::vector<moveit_msgs::msg::CollisionObject> objects;

  for (size_t i = 0; i < ids.size(); ++i)
  {
  moveit_msgs::msg::CollisionObject object;
  object.id = ids[i];
  object.header.frame_id = "head"; // Explicitly set to the head frame

  shape_msgs::msg::SolidPrimitive primitive;
  primitive.type = (types[i] == "box") ? primitive.BOX : primitive.CYLINDER;
  primitive.dimensions.clear();
  for (const auto &d : dims[i])
  {
  primitive.dimensions.push_back(d);
  }
  object.primitives.push_back(primitive);
  object.primitive_poses.push_back(poses[i]);
  object.operation = object.ADD;
  objects.push_back(object);
  }

  planning_scene_interface_.applyCollisionObjects(objects);
  }

  // 🔄 New method to get all object poses in the planning scene
  std::map<std::string, geometry_msgs::msg::Pose> getAllObjectPoses()
  {
  std::vector<std::string> object_ids = planning_scene_interface_.getKnownObjectNames();
  return planning_scene_interface_.getObjectPoses(object_ids);
  }

  void objectRemove(const std::string &id)
  {
    moveit_msgs::msg::CollisionObject object;
    object.id = id;
    object.operation = object.REMOVE;
    planning_scene_interface_.applyCollisionObjects({object});
  }

  void objectAttach(const std::string &id, const std::string &link)
  {
    move_group_.attachObject(id, link);
  }

  void objectDetach(const std::string &id)
  {
    move_group_.detachObject(id);
  }

  std::pair<geometry_msgs::msg::Pose, geometry_msgs::msg::Pose>
  getCurrentPoses()
  {
    geometry_msgs::msg::Pose left_pose =
        move_group_.getCurrentPose("l_arm_tip").pose;
    geometry_msgs::msg::Pose right_pose =
        move_group_.getCurrentPose("r_arm_tip").pose;
    return {left_pose, right_pose};
  }

private:
  rclcpp::Node::SharedPtr node_;
  moveit::planning_interface::PlanningSceneInterface planning_scene_interface_;
  rclcpp::Publisher<moveit_msgs::msg::PlanningScene>::SharedPtr planning_scene_publisher_;
  tf2_ros::Buffer tf_buffer_;
  tf2_ros::TransformListener tf_listener_; 
};

class ReachyControlServer : public rclcpp::Node
{
private:
  rclcpp::Publisher<dual_panda_moveit2_interface::msg::RobotPose>::SharedPtr pose_publisher_;
  rclcpp::TimerBase::SharedPtr pose_timer_;
  tf2_ros::Buffer tf_buffer_;
  tf2_ros::TransformListener tf_listener_;
public:
  using Move = dual_panda_moveit2_interface::action::Move;
  using GripperControl = dual_panda_moveit2_interface::srv::GripperControl;
  using SpawnObject = dual_panda_moveit2_interface::srv::SpawnObject;
  using RemoveObject = dual_panda_moveit2_interface::srv::RemoveObject;
  using AttachObject = dual_panda_moveit2_interface::srv::AttachObject;
  using DetachObject = dual_panda_moveit2_interface::srv::DetachObject;

  ReachyControlServer()
    : Node("reachy_control_server", rclcpp::NodeOptions().allow_undeclared_parameters(true).use_intra_process_comms(true).parameter_overrides({
      {"use_sim_time", rclcpp::ParameterValue(true)}
  })),
      tf_buffer_(this->get_clock()),
      tf_listener_(tf_buffer_)
  {
    RCLCPP_INFO(this->get_logger(), "Reachy Control Server started");
  }

  void init()
  {
    auto parameters_client = std::make_shared<rclcpp::SyncParametersClient>(this->shared_from_this(), "/move_group");
  
    while (!parameters_client->wait_for_service(1s))
    {
      if (!rclcpp::ok())
      {
        RCLCPP_ERROR(this->get_logger(), "Interrupted while waiting for parameter service.");
        rclcpp::shutdown();
        return;
      }
      RCLCPP_INFO(this->get_logger(), "Waiting for parameter service...");
    }
    
    auto param_list = parameters_client->list_parameters({"robot_description_kinematics"}, 10);
    auto params = parameters_client->get_parameters(param_list.names);
    this->set_parameters(params);
  
    // Initialize the Reachy controller
    controller_ = std::make_shared<ReachyController>(this->shared_from_this());

    // Wait for valid states for both arms to avoid getCurrentPose errors
    // try {
    //   waitForValidRobotState(controller_->move_group_, this->shared_from_this(), "l_arm_tip");
    //   waitForValidRobotState(controller_->move_group_, this->shared_from_this(), "r_arm_tip");
    // } catch (const std::exception &ex) {
    //   RCLCPP_ERROR(this->get_logger(), "Error waiting for valid robot state: %s", ex.what());
    //   rclcpp::shutdown();
    //   return;
    // }

    // Once valid states are received, retrieve and log the current poses
    pose_publisher_ = this->create_publisher<dual_panda_moveit2_interface::msg::RobotPose>("/robot_pose", 10);

    pose_timer_ = this->create_wall_timer(
      50ms,  // publish every 500 ms
      [this]() {
        geometry_msgs::msg::PoseStamped head;
        head.header.stamp = this->now();
        head.header.frame_id = controller_->head_group_.getPlanningFrame();
        // Replace "l_arm_tip" with the appropriate end-effector link name if needed
        head.pose = controller_->head_group_.getCurrentPose().pose;

        geometry_msgs::msg::PoseStamped left_pose;
        left_pose.header.stamp = this->now();
        left_pose.header.frame_id = controller_->move_group_.getPlanningFrame();
        // Replace "l_arm_tip" with the appropriate end-effector link name if needed
        left_pose.pose = controller_->move_group_.getCurrentPose("l_arm_tip").pose;
    
        geometry_msgs::msg::PoseStamped right_pose;
        right_pose.header.stamp = this->now();
        right_pose.header.frame_id = controller_->move_group_.getPlanningFrame();
        // Replace "r_arm_tip" with the appropriate end-effector link name if needed
        right_pose.pose = controller_->move_group_.getCurrentPose("r_arm_tip").pose;
    
        // Transform left and right poses to the head frame
        geometry_msgs::msg::PoseStamped head_transformed, left_transformed, right_transformed;
        try
        {
          // head_transformed = tf_buffer_.transform(head, "head", tf2::durationFromSec(0.5));
          left_transformed = tf_buffer_.transform(left_pose, "head", tf2::durationFromSec(0.5));
          right_transformed = tf_buffer_.transform(right_pose, "head", tf2::durationFromSec(0.5));
        }
        catch (const tf2::TransformException &ex)
        {
          RCLCPP_ERROR(this->get_logger(), "TF transform failed: %s", ex.what());
          return;
        }

        // Set the transformed poses' headers to "head"
        left_transformed.header.stamp = this->now();
        left_transformed.header.frame_id = "head";

        right_transformed.header.stamp = this->now();
        right_transformed.header.frame_id = "head";

        // Create and publish the RobotPose message
        dual_panda_moveit2_interface::msg::RobotPose poses;
        poses.head = head;
        poses.left_pose = left_transformed;
        poses.right_pose = right_transformed;
        pose_publisher_->publish(poses);

        RCLCPP_DEBUG(this->get_logger(), "Published robot poses in head frame.");
      });

    // auto [left_pose, right_pose] = controller_->getCurrentPoses();
    // RCLCPP_INFO(this->get_logger(), "Left arm pose: [%f, %f, %f]",
    //             left_pose.position.x, left_pose.position.y, left_pose.position.z);
    // RCLCPP_INFO(this->get_logger(), "Right arm pose: [%f, %f, %f]",
    //             right_pose.position.x, right_pose.position.y, right_pose.position.z);
  
    move_action_server_ = rclcpp_action::create_server<Move>(
        this->shared_from_this(), "move_robot",
        std::bind(&ReachyControlServer::handle_goal, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&ReachyControlServer::handle_cancel, this, std::placeholders::_1),
        std::bind(&ReachyControlServer::handle_accepted, this, std::placeholders::_1));
  
    gripper_srv_ = this->create_service<GripperControl>("gripper_control", 
                  std::bind(&ReachyControlServer::gripperCallback, this, std::placeholders::_1, std::placeholders::_2));
    spawn_srv_ = this->create_service<SpawnObject>("spawn_object", 
                  std::bind(&ReachyControlServer::spawnCallback, this, std::placeholders::_1, std::placeholders::_2));
    remove_srv_ = this->create_service<RemoveObject>("remove_object", 
                  std::bind(&ReachyControlServer::removeCallback, this, std::placeholders::_1, std::placeholders::_2));
    attach_srv_ = this->create_service<AttachObject>("attach_object", 
                  std::bind(&ReachyControlServer::attachCallback, this, std::placeholders::_1, std::placeholders::_2));
    detach_srv_ = this->create_service<DetachObject>("detach_object", 
                  std::bind(&ReachyControlServer::detachCallback, this, std::placeholders::_1, std::placeholders::_2));
    spawn_topic_sub_ = this->create_subscription<dual_panda_moveit2_interface::msg::SpawnBatch>(
      "/spawn_objects", 10,
      [this](const dual_panda_moveit2_interface::msg::SpawnBatch::SharedPtr msg)
      {
        latest_msg_ = msg;
      });
    
    spawn_timer_ = this->create_wall_timer(
      5s,
      [this]()
      {
        if (!latest_msg_)
          return;
    
        // Remove all objects
        auto current_objects = controller_->getCurrentCollisionObjects();
        for (const auto &obj : current_objects)
        {
          controller_->objectRemove(obj.id);
        }
    
        // Spawn new batch
        std::vector<std::string> ids, types;
        std::vector<std::vector<double>> dims;
        std::vector<geometry_msgs::msg::Pose> poses;
    
        for (const auto &obj : latest_msg_->objects)
        {
          ids.push_back(obj.id);
          types.push_back(obj.type);
          dims.push_back(obj.dimensions);
          poses.push_back(obj.pose);
        }
    
        controller_->objectSpawnBatch(ids, types, dims, poses);
        RCLCPP_INFO(this->get_logger(), "Spawned %zu objects via topic.", ids.size());
      });
                  
  }
  
private:
  std::shared_ptr<ReachyController> controller_;
  rclcpp_action::Server<Move>::SharedPtr move_action_server_;
  rclcpp::Service<GripperControl>::SharedPtr gripper_srv_;
  rclcpp::Service<SpawnObject>::SharedPtr spawn_srv_;
  rclcpp::Service<RemoveObject>::SharedPtr remove_srv_;
  rclcpp::Service<AttachObject>::SharedPtr attach_srv_;
  rclcpp::Service<DetachObject>::SharedPtr detach_srv_;
  rclcpp::Subscription<dual_panda_moveit2_interface::msg::SpawnBatch>::SharedPtr spawn_topic_sub_;
  dual_panda_moveit2_interface::msg::SpawnBatch::SharedPtr latest_msg_;
  rclcpp::TimerBase::SharedPtr spawn_timer_;

  
  rclcpp_action::GoalResponse handle_goal(const rclcpp_action::GoalUUID &, std::shared_ptr<const Move::Goal> goal)
  {
    RCLCPP_INFO(this->get_logger(), "Received move goal");
    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
  }

  rclcpp_action::CancelResponse handle_cancel(const std::shared_ptr<rclcpp_action::ServerGoalHandle<Move>>)
  {
    return rclcpp_action::CancelResponse::ACCEPT;
  }

  void handle_accepted(const std::shared_ptr<rclcpp_action::ServerGoalHandle<Move>> goal_handle)
  {
    std::thread([this, goal_handle]()
                {
      const auto goal = goal_handle->get_goal();
      auto result = std::make_shared<Move::Result>();
      try {
        if (goal->use_joint_state){
            controller_->setJointStates(controller_->head_group_, 
                          std::vector<double>(goal->joint_values.begin(), goal->joint_values.begin() + 3));
            controller_->setJointStates(controller_->move_group_, 
                          std::vector<double>(goal->joint_values.begin() + 3, goal->joint_values.end()));
        }else{
          controller_->setTargetPose(goal->left_pose, goal->right_pose);
          controller_->setHeadTargetPose(goal->head_pose);
        }
        result->success = true;
        goal_handle->succeed(result);
      } catch (const std::exception &e) {
        RCLCPP_ERROR(this->get_logger(), "Motion error: %s", e.what());
        result->success = false;
        goal_handle->abort(result);
      } })
        .detach();
  }

  void gripperCallback(const std::shared_ptr<GripperControl::Request> req, 
                       std::shared_ptr<GripperControl::Response> res)
  {
    try
    {
      if (req->gripper_name == "left")
        controller_->controlGripper(controller_->left_gripper_, req->open);
      else
        controller_->controlGripper(controller_->right_gripper_, req->open);
      res->success = true;
    }
    catch (...)
    {
      res->success = false;
    }
  }

  void spawnCallback(const std::shared_ptr<SpawnObject::Request> req,
    std::shared_ptr<SpawnObject::Response> res)
  {
  try
  {
  std::vector<std::string> ids;
  std::vector<std::string> types;
  std::vector<std::vector<double>> dimensions;
  std::vector<geometry_msgs::msg::Pose> poses;

  for (const auto &obj : req->objects)
  {
  ids.push_back(obj.id);
  types.push_back(obj.type);
  dimensions.push_back(obj.dimensions);
  poses.push_back(obj.pose);
  }

  controller_->objectSpawnBatch(ids, types, dimensions, poses);

  rclcpp::sleep_for(500ms); // Allow planning scene update

  res->success = true;

  // ✅ Now retrieve actual object poses from the planning scene
  auto actual_poses = controller_->getAllObjectPoses();
  for (const auto &pair : actual_poses)
  {
  dual_panda_moveit2_interface::msg::ObjectSpec spec;
  spec.id = pair.first;
  spec.pose = pair.second;
  res->current_objects.push_back(spec);
  }
  }
  catch (const std::exception &e)
  {
  RCLCPP_ERROR(this->get_logger(), "Spawn failed: %s", e.what());
  res->success = false;
  }
  }

  void removeCallback(const std::shared_ptr<RemoveObject::Request> req, 
                      std::shared_ptr<RemoveObject::Response> res)
  {
    try
    {
      auto known_objects = controller_->getCurrentCollisionObjects();
      auto it = std::find_if(known_objects.begin(), known_objects.end(),
                 [&req](const moveit_msgs::msg::CollisionObject &obj) {
                   return obj.id == req->id;
                 });

      if (it == known_objects.end())
      {
      RCLCPP_WARN(this->get_logger(), "Object with ID '%s' does not exist.", req->id.c_str());
      res->success = false;
      return;
      }

      controller_->objectRemove(req->id);
      res->success = true;
    }
    catch (const std::exception &e)
    {
      RCLCPP_ERROR(this->get_logger(), "Error removing object: %s", e.what());
      res->success = false;
    }
  }

  void attachCallback(const std::shared_ptr<AttachObject::Request> req, 
                      std::shared_ptr<AttachObject::Response> res)
  {
    try
    {
      controller_->objectAttach(req->id, req->link);
      res->success = true;
    }
    catch (...)
    {
      res->success = false;
    }
  }

  void detachCallback(const std::shared_ptr<DetachObject::Request> req, 
                      std::shared_ptr<DetachObject::Response> res)
  {
    try
    {
      controller_->objectDetach(req->id);
      res->success = true;
    }
    catch (...)
    {
      res->success = false;
    }
  }
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<ReachyControlServer>();
  node->init();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
