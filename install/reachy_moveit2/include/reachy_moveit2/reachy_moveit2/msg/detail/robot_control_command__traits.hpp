// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from reachy_moveit2:msg/RobotControlCommand.idl
// generated code does not contain a copyright notice

#ifndef REACHY_MOVEIT2__MSG__DETAIL__ROBOT_CONTROL_COMMAND__TRAITS_HPP_
#define REACHY_MOVEIT2__MSG__DETAIL__ROBOT_CONTROL_COMMAND__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "reachy_moveit2/msg/detail/robot_control_command__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'joint_state'
#include "sensor_msgs/msg/detail/joint_state__traits.hpp"
// Member 'cartesian_target'
#include "geometry_msgs/msg/detail/pose_stamped__traits.hpp"

namespace reachy_moveit2
{

namespace msg
{

inline void to_flow_style_yaml(
  const RobotControlCommand & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: mode
  {
    out << "mode: ";
    rosidl_generator_traits::value_to_yaml(msg.mode, out);
    out << ", ";
  }

  // member: joint_state
  {
    out << "joint_state: ";
    to_flow_style_yaml(msg.joint_state, out);
    out << ", ";
  }

  // member: cartesian_target
  {
    out << "cartesian_target: ";
    to_flow_style_yaml(msg.cartesian_target, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RobotControlCommand & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mode: ";
    rosidl_generator_traits::value_to_yaml(msg.mode, out);
    out << "\n";
  }

  // member: joint_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "joint_state:\n";
    to_block_style_yaml(msg.joint_state, out, indentation + 2);
  }

  // member: cartesian_target
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cartesian_target:\n";
    to_block_style_yaml(msg.cartesian_target, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RobotControlCommand & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace reachy_moveit2

namespace rosidl_generator_traits
{

[[deprecated("use reachy_moveit2::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const reachy_moveit2::msg::RobotControlCommand & msg,
  std::ostream & out, size_t indentation = 0)
{
  reachy_moveit2::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use reachy_moveit2::msg::to_yaml() instead")]]
inline std::string to_yaml(const reachy_moveit2::msg::RobotControlCommand & msg)
{
  return reachy_moveit2::msg::to_yaml(msg);
}

template<>
inline const char * data_type<reachy_moveit2::msg::RobotControlCommand>()
{
  return "reachy_moveit2::msg::RobotControlCommand";
}

template<>
inline const char * name<reachy_moveit2::msg::RobotControlCommand>()
{
  return "reachy_moveit2/msg/RobotControlCommand";
}

template<>
struct has_fixed_size<reachy_moveit2::msg::RobotControlCommand>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<reachy_moveit2::msg::RobotControlCommand>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<reachy_moveit2::msg::RobotControlCommand>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // REACHY_MOVEIT2__MSG__DETAIL__ROBOT_CONTROL_COMMAND__TRAITS_HPP_
