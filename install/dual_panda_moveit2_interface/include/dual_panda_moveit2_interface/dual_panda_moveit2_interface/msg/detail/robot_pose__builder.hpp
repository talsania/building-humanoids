// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from dual_panda_moveit2_interface:msg/RobotPose.idl
// generated code does not contain a copyright notice

#ifndef DUAL_PANDA_MOVEIT2_INTERFACE__MSG__DETAIL__ROBOT_POSE__BUILDER_HPP_
#define DUAL_PANDA_MOVEIT2_INTERFACE__MSG__DETAIL__ROBOT_POSE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "dual_panda_moveit2_interface/msg/detail/robot_pose__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace dual_panda_moveit2_interface
{

namespace msg
{

namespace builder
{

class Init_RobotPose_right_pose
{
public:
  explicit Init_RobotPose_right_pose(::dual_panda_moveit2_interface::msg::RobotPose & msg)
  : msg_(msg)
  {}
  ::dual_panda_moveit2_interface::msg::RobotPose right_pose(::dual_panda_moveit2_interface::msg::RobotPose::_right_pose_type arg)
  {
    msg_.right_pose = std::move(arg);
    return std::move(msg_);
  }

private:
  ::dual_panda_moveit2_interface::msg::RobotPose msg_;
};

class Init_RobotPose_left_pose
{
public:
  explicit Init_RobotPose_left_pose(::dual_panda_moveit2_interface::msg::RobotPose & msg)
  : msg_(msg)
  {}
  Init_RobotPose_right_pose left_pose(::dual_panda_moveit2_interface::msg::RobotPose::_left_pose_type arg)
  {
    msg_.left_pose = std::move(arg);
    return Init_RobotPose_right_pose(msg_);
  }

private:
  ::dual_panda_moveit2_interface::msg::RobotPose msg_;
};

class Init_RobotPose_head
{
public:
  Init_RobotPose_head()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RobotPose_left_pose head(::dual_panda_moveit2_interface::msg::RobotPose::_head_type arg)
  {
    msg_.head = std::move(arg);
    return Init_RobotPose_left_pose(msg_);
  }

private:
  ::dual_panda_moveit2_interface::msg::RobotPose msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::dual_panda_moveit2_interface::msg::RobotPose>()
{
  return dual_panda_moveit2_interface::msg::builder::Init_RobotPose_head();
}

}  // namespace dual_panda_moveit2_interface

#endif  // DUAL_PANDA_MOVEIT2_INTERFACE__MSG__DETAIL__ROBOT_POSE__BUILDER_HPP_
