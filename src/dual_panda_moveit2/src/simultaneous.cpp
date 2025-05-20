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

using namespace std::chrono_literals;
using namespace dual_panda_moveit2_interface::srv;
using namespace dual_panda_moveit2_interface::action;

class ReachyController
{
public:
  ReachyController(const rclcpp::Node::SharedPtr &node)
      : node_(node), move_group_(node, "dual_arm"),
        head_group_(node, "head"),
        left_gripper_(node, "left_gripper"),
        right_gripper_(node, "right_gripper"),
        planning_scene_interface_()
  {
    move_group_.setMaxVelocityScalingFactor(0.5);
    left_gripper_.setMaxVelocityScalingFactor(0.5);
    right_gripper_.setMaxVelocityScalingFactor(0.5);
    head_group_.setMaxVelocityScalingFactor(0.5);

    planning_scene_publisher_ = node_->create_publisher<moveit_msgs::msg::PlanningScene>(
        "/planning_scene", rclcpp::QoS(10));
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
      object.header.frame_id = move_group_.getPlanningFrame();

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

private:
  rclcpp::Node::SharedPtr node_;
  moveit::planning_interface::PlanningSceneInterface planning_scene_interface_;
  rclcpp::Publisher<moveit_msgs::msg::PlanningScene>::SharedPtr planning_scene_publisher_;
  moveit::planning_interface::MoveGroupInterface move_group_;
  moveit::planning_interface::MoveGroupInterface head_group_;
  moveit::planning_interface::MoveGroupInterface left_gripper_;
  moveit::planning_interface::MoveGroupInterface right_gripper_;
};

class ReachyControlServer : public rclcpp::Node
{
public:
  using SpawnObject = dual_panda_moveit2_interface::srv::SpawnObject;

  ReachyControlServer()
      : Node("reachy_control_server", rclcpp::NodeOptions().allow_undeclared_parameters(true).use_intra_process_comms(true).parameter_overrides({
            {"use_sim_time", rclcpp::ParameterValue(true)}}))
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

    controller_ = std::make_shared<ReachyController>(this->shared_from_this());

    // ✅ Register spawn_object service
    spawn_srv_ = this->create_service<SpawnObject>(
        "/spawn_object",
        std::bind(&ReachyControlServer::spawnCallback, this, std::placeholders::_1, std::placeholders::_2));
  }

private:
  std::shared_ptr<ReachyController> controller_;
  rclcpp::Service<SpawnObject>::SharedPtr spawn_srv_;

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
