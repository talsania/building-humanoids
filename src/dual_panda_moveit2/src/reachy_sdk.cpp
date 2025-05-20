#include <chrono>
#include <geometry_msgs/msg/pose.hpp>
#include <iostream>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit/robot_model/robot_model.h>
#include <moveit/robot_model_loader/robot_model_loader.h>
#include <moveit/robot_state/robot_state.h>
#include <rclcpp/rclcpp.hpp>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

class ReachyController
{
public:
  ReachyController(const rclcpp::Node::SharedPtr &node)
      : node_(node), move_group_(node, "dual_arm"),
        left_gripper_(node, "left_gripper"),
        right_gripper_(node, "right_gripper"), head_group_(node, "head"),
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

  void execute()
  {
    try
    {
      waitForValidState(move_group_);
      waitForValidState(left_gripper_);
      waitForValidState(right_gripper_);
      waitForValidState(head_group_);

      auto [left_pose_zero, right_pose_zero] = getCurrentPoses();

      std::vector<double> joint_values = {
          -4.449791554361582e-05,  // l_shoulder_pitch
          -4.5987713756039744e-05, // l_shoulder_roll
          -9.365531308576465e-05,  // l_arm_yaw
          -8.659403196070343e-05,  // l_elbow_pitch
          -8.913755202665926e-05,  // l_forearm_yaw
          9.550579311326152e-06,   // l_wrist_pitch
          6.0963440081104634e-05,  // l_wrist_roll
          0.09615772867012852,     // r_shoulder_pitch
          -0.35239492827981717,    // r_shoulder_roll
          0.14639729615867228,     // r_arm_yaw
          -1.4432453983729132,     // r_elbow_pitch
          -0.3510710848190251,     // r_forearm_yaw
          -0.1977982252032241,     // r_wrist_pitch
          -0.09382823906834833     // r_wrist_roll
      };

      // Open/Close grippers
      // controlGripper(right_gripper_, true); // Open left gripper

      geometry_msgs::msg::Pose boxPose;
      boxPose.position.x = 0.36;
      boxPose.position.y = -0.31;
      boxPose.position.z = 0.67;

      objectSpawn("box1", "box", {0.05, 0.05, 0.05},
                  boxPose); // Spawn object at left gripper pose

      // setTargetPose(left_pose, pre_grasp_pose);

      // printRobotPose(left_pose, right_pose);

      setJointStates(move_group_, joint_values);
      auto [left_pose, right_pose] = getCurrentPoses();
      setJointStates(move_group_, std::vector<double>(joint_values.size(), 0.0));
      setTargetPose(left_pose, right_pose);

      // auto pre_grasp_pose = right_pose;
      // pre_grasp_pose.position.x -= 0.1;
      // pre_grasp_pose.position.y -= 0.03;
      // pre_grasp_pose.orientation.w = 1.0;

      // setTargetPose(left_pose, pre_grasp_pose);

      // allowCollisionWithLinks("box1", {"r_gripper_finger", "r_gripper_thumb"});

      // controlGripper(right_gripper_, false); // Close left gripper

      // objectAttach("box1", "r_gripper_finger");
      objectAttach("box1", "r_gripper_thumb");

      // [INFO] [1743507082.694153444] [bimanual_control]:   Position - x: 0.196432, y: 0.007180, z: 0.685581
      // [INFO] [1743507082.694158006] [bimanual_control]:   Orientation - x: 0.633093, y: -0.360998, z: 0.426936, w: 0.535351
      geometry_msgs::msg::Pose right_place_pose;
      right_place_pose.position.x = 0.196432;
      right_place_pose.position.y = 0.007180;
      right_place_pose.position.z = 0.685581;
      right_place_pose.orientation.x = 0.633093;
      right_place_pose.orientation.y = -0.360998;
      right_place_pose.orientation.z = 0.426936;
      right_place_pose.orientation.w = 0.535351;

      setTargetPose(left_pose, right_place_pose);

      // [INFO] [1743507831.629898342] [bimanual_control]:   Position - x: 0.197324, y: 0.062383, z: 0.589659
      // [INFO] [1743507831.629907632] [bimanual_control]:   Orientation - x: 0.106532, y: 0.695905, z: 0.700098, w: -0.119293
      geometry_msgs::msg::Pose left_pick_pose;
      left_pick_pose.position.x = 0.197324;
      left_pick_pose.position.y = 0.062383;
      left_pick_pose.position.z = 0.589659;
      left_pick_pose.orientation.x = 0.106532;
      left_pick_pose.orientation.y = 0.695905;
      left_pick_pose.orientation.z = 0.700098;
      left_pick_pose.orientation.w = -0.119293;

      setTargetPose(left_pick_pose, right_place_pose);

      objectDetach("box1");
      objectAttach("box1", "l_gripper_thumb");

      setTargetPose(left_pose_zero, right_pose_zero);

      objectDetach("box1");

      RCLCPP_INFO(node_->get_logger(), "Robot motion complete!");
    }
    catch (const std::exception &e)
    {
      RCLCPP_FATAL(node_->get_logger(), "Critical error in execution: %s",
                   e.what());
    }
    catch (...)
    {
      RCLCPP_FATAL(node_->get_logger(), "Unknown critical error in execution.");
    }
  }

private:
  rclcpp::Node::SharedPtr node_;
  moveit::planning_interface::MoveGroupInterface move_group_;
  moveit::planning_interface::MoveGroupInterface left_gripper_;
  moveit::planning_interface::MoveGroupInterface right_gripper_;
  moveit::planning_interface::MoveGroupInterface head_group_;
  moveit::planning_interface::PlanningSceneInterface planning_scene_interface_;
  rclcpp::Publisher<moveit_msgs::msg::PlanningScene>::SharedPtr
      planning_scene_publisher_;

  void
  waitForValidState(moveit::planning_interface::MoveGroupInterface &group)
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

  std::pair<geometry_msgs::msg::Pose, geometry_msgs::msg::Pose>
  getCurrentPoses()
  {
    geometry_msgs::msg::Pose left_pose =
        move_group_.getCurrentPose("l_arm_tip").pose;
    geometry_msgs::msg::Pose right_pose =
        move_group_.getCurrentPose("r_arm_tip").pose;
    return {left_pose, right_pose};
  }

  void printRobotPose(const geometry_msgs::msg::Pose &left_pose,
                      const geometry_msgs::msg::Pose &right_pose)
  {
    RCLCPP_INFO(node_->get_logger(), "Current Pose State:");
    RCLCPP_INFO(node_->get_logger(), "Left End-Effector Pose:");
    RCLCPP_INFO(node_->get_logger(), "  Position - x: %f, y: %f, z: %f",
                left_pose.position.x, left_pose.position.y,
                left_pose.position.z);
    RCLCPP_INFO(node_->get_logger(),
                "  Orientation - x: %f, y: %f, z: %f, w: %f",
                left_pose.orientation.x, left_pose.orientation.y,
                left_pose.orientation.z, left_pose.orientation.w);

    RCLCPP_INFO(node_->get_logger(), "Right End-Effector Pose:");
    RCLCPP_INFO(node_->get_logger(), "  Position - x: %f, y: %f, z: %f",
                right_pose.position.x, right_pose.position.y,
                right_pose.position.z);
    RCLCPP_INFO(node_->get_logger(),
                "  Orientation - x: %f, y: %f, z: %f, w: %f",
                right_pose.orientation.x, right_pose.orientation.y,
                right_pose.orientation.z, right_pose.orientation.w);
  }

  void printJointStates(const std::vector<double> &joint_values)
  {
    const std::vector<std::string> &joint_names = move_group_.getJointNames();
    RCLCPP_INFO(node_->get_logger(), "Joint States:");
    for (size_t i = 0; i < joint_names.size(); ++i)
    {
      RCLCPP_INFO(node_->get_logger(), "  %s: %f", joint_names[i].c_str(),
                  joint_values[i]);
    }
  }

  void setJointStates(moveit::planning_interface::MoveGroupInterface &group,
                      const std::vector<double> &joint_values)
  {
    auto current_state = group.getCurrentState();
    if (!current_state)
    {
      RCLCPP_ERROR(
          node_->get_logger(),
          "Failed to get current state for setting joint values in %s!",
          group.getName().c_str());
      throw std::runtime_error("Invalid current state");
    }

    const std::vector<std::string> &joint_names = group.getJointNames();
    if (joint_values.size() != joint_names.size())
    {
      RCLCPP_ERROR(node_->get_logger(), "Mismatch in joint size for %s!",
                   group.getName().c_str());
      throw std::runtime_error("Joint values size mismatch");
    }

    current_state->setVariablePositions(joint_names, joint_values);
    group.setJointValueTarget(*current_state);

    moveit::planning_interface::MoveGroupInterface::Plan plan;
    bool success = static_cast<bool>(group.plan(plan));
    if (success)
    {
      RCLCPP_INFO(node_->get_logger(), "Executing plan for %s...",
                  group.getName().c_str());
      auto result = group.execute(plan);
      if (result != moveit::core::MoveItErrorCode::SUCCESS)
      {
        RCLCPP_ERROR(node_->get_logger(), "Execution failed for %s!",
                     group.getName().c_str());
        throw std::runtime_error("Execution failure");
      }
      RCLCPP_INFO(node_->get_logger(), "Execution completed for %s.",
                  group.getName().c_str());
    }
    else
    {
      RCLCPP_ERROR(node_->get_logger(), "Planning failed for %s!",
                   group.getName().c_str());
      throw std::runtime_error("Planning failure");
    }
  }

  void controlGripper(moveit::planning_interface::MoveGroupInterface &gripper,
                      bool open)
  {
    std::vector<double> values;
    if (open)
    {
      if (gripper.getName() == "left_gripper")
      {
        values = {1.2};
      }
      else
      {
        values = {-1.2};
      }
    }
    else
    {
      if (gripper.getName() == "left_gripper")
      {
        values = {-0.30};
      }
      else
      {
        values = {0.30};
      }
    }
    setJointStates(gripper, values);
  }

  void setTargetPose(const geometry_msgs::msg::Pose &left_target_pose,
                     const geometry_msgs::msg::Pose &right_target_pose)
  {
    robot_model_loader::RobotModelLoader robot_model_loader(node_);
    const moveit::core::RobotModelPtr &kinematic_model =
        robot_model_loader.getModel();
    if (!kinematic_model)
    {
      RCLCPP_ERROR(node_->get_logger(), "Failed to load robot model!");
      throw std::runtime_error("Robot model loading failed");
    }

    moveit::core::RobotStatePtr robot_state(
        new moveit::core::RobotState(kinematic_model));
    robot_state->setToDefaultValues();
    const auto *left_group = kinematic_model->getJointModelGroup("left_arm");
    const auto *right_group = kinematic_model->getJointModelGroup("right_arm");

    if (!left_group || !right_group)
    {
      RCLCPP_ERROR(node_->get_logger(), "Joint model group error!");
      throw std::runtime_error("Missing joint model groups");
    }

    bool found_ik_left =
        robot_state->setFromIK(left_group, left_target_pose, 0.1);
    bool found_ik_right =
        robot_state->setFromIK(right_group, right_target_pose, 0.1);

    if (!found_ik_left && !found_ik_right)
    {
      RCLCPP_ERROR(node_->get_logger(), "IK failed for both arms!");
      throw std::runtime_error("IK failure");
    }
    else if (!found_ik_left)
    {
      RCLCPP_ERROR(node_->get_logger(), "IK failed for left arm!");
      throw std::runtime_error("IK failure for left arm");
    }
    else if (!found_ik_right)
    {
      RCLCPP_ERROR(node_->get_logger(), "IK failed for right arm!");
      throw std::runtime_error("IK failure for right arm");
    }
    RCLCPP_INFO(node_->get_logger(),
                "IK solution found for both arms, setting joint target...");

    move_group_.setJointValueTarget(*robot_state);

    moveit::planning_interface::MoveGroupInterface::Plan plan;
    if (move_group_.plan(plan))
    {
      auto result = move_group_.execute(plan);
      if (result != moveit::core::MoveItErrorCode::SUCCESS)
      {
        RCLCPP_ERROR(node_->get_logger(), "Execution failed for dual_arm IK!");
        throw std::runtime_error("Execution failure");
      }
    }
    else
    {
      RCLCPP_ERROR(node_->get_logger(), "Planning failed for dual_arm IK!");
      throw std::runtime_error("Planning failure");
    }
  }

  void objectSpawn(const std::string &id, const std::string &type,
                   const std::vector<double> &dims,
                   const geometry_msgs::msg::Pose &pose)
  {
    moveit_msgs::msg::CollisionObject object;
    object.id = id;
    object.header.frame_id = move_group_.getPlanningFrame();

    shape_msgs::msg::SolidPrimitive primitive;
    if (type == "box")
    {
      primitive.type = primitive.BOX;
    }
    else if (type == "cylinder")
    {
      primitive.type = primitive.CYLINDER;
    }
    else
    {
      RCLCPP_ERROR(node_->get_logger(), "Unsupported object type: %s",
                   type.c_str());
      throw std::runtime_error("Unsupported object type");
    }
    primitive.dimensions.assign(dims.begin(), dims.end());
    object.primitives.push_back(primitive);
    object.primitive_poses.push_back(pose);
    object.operation = object.ADD;
    planning_scene_interface_.applyCollisionObjects({object});
    RCLCPP_INFO(node_->get_logger(), "Spawned object %s", id.c_str());
  }

  void objectRemove(const std::string &id)
  {
    moveit_msgs::msg::CollisionObject object;
    object.id = id;
    object.operation = object.REMOVE;
    planning_scene_interface_.applyCollisionObjects({object});
    RCLCPP_INFO(node_->get_logger(), "Removed object %s", id.c_str());
  }

  void objectAttach(const std::string &id, const std::string &link)
  {
    move_group_.attachObject(id, link);
    RCLCPP_INFO(node_->get_logger(), "Attached %s to %s", id.c_str(),
                link.c_str());
  }

  void objectDetach(const std::string &id)
  {
    move_group_.detachObject(id);
    RCLCPP_INFO(node_->get_logger(), "Detached %s", id.c_str());
  }

  void allowCollisionWithLinks(const std::string &object_id,
                               const std::vector<std::string> &links)
  {
    moveit_msgs::msg::PlanningScene planning_scene;
    planning_scene.is_diff = true;

    std::vector<std::string> all_names = links;
    all_names.push_back(object_id); // object last

    // Fill entry names
    planning_scene.allowed_collision_matrix.entry_names = all_names;

    // Construct a symmetric matrix of size N x N
    for (size_t i = 0; i < all_names.size(); ++i)
    {
      moveit_msgs::msg::AllowedCollisionEntry entry;
      entry.enabled.resize(all_names.size(), true);

      // Allow object-link or link-object collisions
      for (size_t j = 0; j < all_names.size(); ++j)
      {
        if ((all_names[i] == object_id &&
             std::find(links.begin(), links.end(), all_names[j]) !=
                 links.end()) ||
            (all_names[j] == object_id &&
             std::find(links.begin(), links.end(), all_names[i]) !=
                 links.end()))
        {
          entry.enabled[j] = true;
        }
      }

      planning_scene.allowed_collision_matrix.entry_values.push_back(entry);
    }

    planning_scene_publisher_->publish(planning_scene);
    RCLCPP_INFO(node_->get_logger(),
                "Allowed collision between '%s' and %lu links.",
                object_id.c_str(), links.size());
  }
};

int main(int argc, char **argv)
{
  try
  {
    rclcpp::init(argc, argv);
    rclcpp::NodeOptions options =
        rclcpp::NodeOptions().allow_undeclared_parameters(true);
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
