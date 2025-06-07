// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from dual_panda_moveit2_interface:msg/RobotPose.idl
// generated code does not contain a copyright notice

#ifndef DUAL_PANDA_MOVEIT2_INTERFACE__MSG__DETAIL__ROBOT_POSE__TRAITS_HPP_
#define DUAL_PANDA_MOVEIT2_INTERFACE__MSG__DETAIL__ROBOT_POSE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "dual_panda_moveit2_interface/msg/detail/robot_pose__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'head'
// Member 'left_pose'
// Member 'right_pose'
#include "geometry_msgs/msg/detail/pose_stamped__traits.hpp"

namespace dual_panda_moveit2_interface
{

namespace msg
{

inline void to_flow_style_yaml(
  const RobotPose & msg,
  std::ostream & out)
{
  out << "{";
  // member: head
  {
    out << "head: ";
    to_flow_style_yaml(msg.head, out);
    out << ", ";
  }

  // member: left_pose
  {
    out << "left_pose: ";
    to_flow_style_yaml(msg.left_pose, out);
    out << ", ";
  }

  // member: right_pose
  {
    out << "right_pose: ";
    to_flow_style_yaml(msg.right_pose, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RobotPose & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: head
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "head:\n";
    to_block_style_yaml(msg.head, out, indentation + 2);
  }

  // member: left_pose
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "left_pose:\n";
    to_block_style_yaml(msg.left_pose, out, indentation + 2);
  }

  // member: right_pose
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "right_pose:\n";
    to_block_style_yaml(msg.right_pose, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RobotPose & msg, bool use_flow_style = false)
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

}  // namespace dual_panda_moveit2_interface

namespace rosidl_generator_traits
{

[[deprecated("use dual_panda_moveit2_interface::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const dual_panda_moveit2_interface::msg::RobotPose & msg,
  std::ostream & out, size_t indentation = 0)
{
  dual_panda_moveit2_interface::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use dual_panda_moveit2_interface::msg::to_yaml() instead")]]
inline std::string to_yaml(const dual_panda_moveit2_interface::msg::RobotPose & msg)
{
  return dual_panda_moveit2_interface::msg::to_yaml(msg);
}

template<>
inline const char * data_type<dual_panda_moveit2_interface::msg::RobotPose>()
{
  return "dual_panda_moveit2_interface::msg::RobotPose";
}

template<>
inline const char * name<dual_panda_moveit2_interface::msg::RobotPose>()
{
  return "dual_panda_moveit2_interface/msg/RobotPose";
}

template<>
struct has_fixed_size<dual_panda_moveit2_interface::msg::RobotPose>
  : std::integral_constant<bool, has_fixed_size<geometry_msgs::msg::PoseStamped>::value> {};

template<>
struct has_bounded_size<dual_panda_moveit2_interface::msg::RobotPose>
  : std::integral_constant<bool, has_bounded_size<geometry_msgs::msg::PoseStamped>::value> {};

template<>
struct is_message<dual_panda_moveit2_interface::msg::RobotPose>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // DUAL_PANDA_MOVEIT2_INTERFACE__MSG__DETAIL__ROBOT_POSE__TRAITS_HPP_
