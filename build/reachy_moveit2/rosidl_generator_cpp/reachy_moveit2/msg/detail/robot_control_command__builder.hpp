// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from reachy_moveit2:msg/RobotControlCommand.idl
// generated code does not contain a copyright notice

#ifndef REACHY_MOVEIT2__MSG__DETAIL__ROBOT_CONTROL_COMMAND__BUILDER_HPP_
#define REACHY_MOVEIT2__MSG__DETAIL__ROBOT_CONTROL_COMMAND__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "reachy_moveit2/msg/detail/robot_control_command__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace reachy_moveit2
{

namespace msg
{

namespace builder
{

class Init_RobotControlCommand_cartesian_target
{
public:
  explicit Init_RobotControlCommand_cartesian_target(::reachy_moveit2::msg::RobotControlCommand & msg)
  : msg_(msg)
  {}
  ::reachy_moveit2::msg::RobotControlCommand cartesian_target(::reachy_moveit2::msg::RobotControlCommand::_cartesian_target_type arg)
  {
    msg_.cartesian_target = std::move(arg);
    return std::move(msg_);
  }

private:
  ::reachy_moveit2::msg::RobotControlCommand msg_;
};

class Init_RobotControlCommand_joint_state
{
public:
  explicit Init_RobotControlCommand_joint_state(::reachy_moveit2::msg::RobotControlCommand & msg)
  : msg_(msg)
  {}
  Init_RobotControlCommand_cartesian_target joint_state(::reachy_moveit2::msg::RobotControlCommand::_joint_state_type arg)
  {
    msg_.joint_state = std::move(arg);
    return Init_RobotControlCommand_cartesian_target(msg_);
  }

private:
  ::reachy_moveit2::msg::RobotControlCommand msg_;
};

class Init_RobotControlCommand_mode
{
public:
  explicit Init_RobotControlCommand_mode(::reachy_moveit2::msg::RobotControlCommand & msg)
  : msg_(msg)
  {}
  Init_RobotControlCommand_joint_state mode(::reachy_moveit2::msg::RobotControlCommand::_mode_type arg)
  {
    msg_.mode = std::move(arg);
    return Init_RobotControlCommand_joint_state(msg_);
  }

private:
  ::reachy_moveit2::msg::RobotControlCommand msg_;
};

class Init_RobotControlCommand_header
{
public:
  Init_RobotControlCommand_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RobotControlCommand_mode header(::reachy_moveit2::msg::RobotControlCommand::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_RobotControlCommand_mode(msg_);
  }

private:
  ::reachy_moveit2::msg::RobotControlCommand msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::reachy_moveit2::msg::RobotControlCommand>()
{
  return reachy_moveit2::msg::builder::Init_RobotControlCommand_header();
}

}  // namespace reachy_moveit2

#endif  // REACHY_MOVEIT2__MSG__DETAIL__ROBOT_CONTROL_COMMAND__BUILDER_HPP_
