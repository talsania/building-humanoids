// // Reachy Dual Arm Controller with Object Pick-and-Place
// #include <rclcpp/rclcpp.hpp>
// #include <moveit/move_group_interface/move_group_interface.h>
// #include <moveit/planning_scene_interface/planning_scene_interface.h>
// #include <geometry_msgs/msg/pose.hpp>
// #include <moveit_msgs/msg/collision_object.hpp>
// #include <shape_msgs/msg/solid_primitive.hpp>
// #include <thread>
// #include <chrono>
// #include <vector>
// #include <iostream>

// using namespace std::chrono_literals;

// class DualArmReachyController
// {
// public:
//   DualArmReachyController(const rclcpp::Node::SharedPtr &node)
//       : node_(node),
//         move_group_(node, "dual_arm"),
//         planning_scene_interface_()
//   {
//     move_group_.setMaxVelocityScalingFactor(0.25);
//   }

//   void execute()
//   {
//     try
//     {
//       waitForValidState();

//       spawnObject("box", "box", {0.05, 0.05, 0.05}, getBoxPose());
//       rclcpp::sleep_for(1s);

//       auto [left_pose, right_pose] = getCurrentPoses();
//       printRobotState(left_pose, right_pose);

//       // Simulate pick by moving right hand over object and attaching
//       geometry_msgs::msg::Pose right_target = getBoxPose();
//       right_target.position.z += 0.1;

//       setTargetPose(right_pose, right_target);
//       attachObject("box", "r_gripper_thumb");

//       // Simulate place
//       geometry_msgs::msg::Pose place_pose = right_target;
//       place_pose.position.y += 0.2;

//       setTargetPose(right_pose, place_pose);
//       detachObject("box");

//       RCLCPP_INFO(node_->get_logger(), "Pick-and-place complete.");
//     }
//     catch (const std::exception &e)
//     {
//       RCLCPP_FATAL(node_->get_logger(), "Execution error: %s", e.what());
//     }
//   }

// private:
//   rclcpp::Node::SharedPtr node_;
//   moveit::planning_interface::MoveGroupInterface move_group_;
//   moveit::planning_interface::PlanningSceneInterface
//   planning_scene_interface_;

//   void waitForValidState()
//   {
//     move_group_.startStateMonitor();
//     auto current_state = move_group_.getCurrentState(10.0);
//     if (!current_state)
//       throw std::runtime_error("Invalid initial state");
//   }

//   std::pair<geometry_msgs::msg::Pose, geometry_msgs::msg::Pose>
//   getCurrentPoses()
//   {
//     auto left = move_group_.getCurrentPose("l_gripper_thumb").pose;
//     auto right = move_group_.getCurrentPose("r_gripper_thumb").pose;
//     return {left, right};
//   }

//   void printRobotState(const geometry_msgs::msg::Pose &left, const
//   geometry_msgs::msg::Pose &right)
//   {
//     std::cout << "Left Pose: " << left.position.x << ", " << left.position.y
//     << ", " << left.position.z << std::endl; std::cout << "Right Pose: " <<
//     right.position.x << ", " << right.position.y << ", " << right.position.z
//     << std::endl;
//   }

//   void setTargetPose(const geometry_msgs::msg::Pose &left_pose, const
//   geometry_msgs::msg::Pose &right_pose)
//   {
//     moveit::core::RobotStatePtr state = move_group_.getCurrentState(10.0);
//     robot_model_loader::RobotModelLoader loader(node_);
//     const auto &model = loader.getModel();
//     moveit::core::RobotState robot_state(model);
//     robot_state.setToDefaultValues();

//     const auto *left_group = model->getJointModelGroup("left_arm");
//     const auto *right_group = model->getJointModelGroup("right_arm");

//     bool left_ok = robot_state.setFromIK(left_group, left_pose);
//     bool right_ok = robot_state.setFromIK(right_group, right_pose);

//     if (!left_ok || !right_ok)
//       throw std::runtime_error("IK failed for one or both arms");

//     move_group_.setJointValueTarget(robot_state);

//     moveit::planning_interface::MoveGroupInterface::Plan plan;
//     if (move_group_.plan(plan) == moveit::core::MoveItErrorCode::SUCCESS)
//     {
//       move_group_.execute(plan);
//     }
//     else
//     {
//       throw std::runtime_error("Planning failed");
//     }
//   }

//   void spawnObject(const std::string &id, const std::string &type, const
//   std::vector<double> &dims, const geometry_msgs::msg::Pose &pose)
//   {
//     moveit_msgs::msg::CollisionObject obj;
//     obj.id = id;
//     obj.header.frame_id = move_group_.getPlanningFrame();

//     shape_msgs::msg::SolidPrimitive primitive;
//     if (type == "box")
//     {
//       primitive.type = primitive.BOX;
//       primitive.dimensions = dims;
//     }

//     obj.primitives.push_back(primitive);
//     obj.primitive_poses.push_back(pose);
//     obj.operation = obj.ADD;

//     planning_scene_interface_.applyCollisionObjects({obj});
//   }

//   void attachObject(const std::string &id, const std::string &link)
//   {
//     move_group_.attachObject(id, link);
//   }

//   void detachObject(const std::string &id)
//   {
//     move_group_.detachObject(id);
//   }

//   geometry_msgs::msg::Pose getBoxPose()
//   {
//     geometry_msgs::msg::Pose pose;
//     pose.position.x = 0.4;
//     pose.position.y = 0.0;
//     pose.position.z = 0.4;
//     pose.orientation.w = 1.0;
//     return pose;
//   }
// };

// int main(int argc, char **argv)
// {
//   rclcpp::init(argc, argv);
//   auto node = rclcpp::Node::make_shared("dual_arm_reachy_control");

//   auto executor =
//   std::make_shared<rclcpp::executors::SingleThreadedExecutor>();
//   executor->add_node(node);
//   std::thread exec_thread([&executor]() { executor->spin(); });

//   DualArmReachyController controller(node);
//   controller.execute();

//   executor->cancel();
//   exec_thread.join();
//   rclcpp::shutdown();
//   return 0;
// }
int main() { return 0; }