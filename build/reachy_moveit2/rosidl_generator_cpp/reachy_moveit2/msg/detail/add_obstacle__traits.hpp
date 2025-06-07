// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from reachy_moveit2:msg/AddObstacle.idl
// generated code does not contain a copyright notice

#ifndef REACHY_MOVEIT2__MSG__DETAIL__ADD_OBSTACLE__TRAITS_HPP_
#define REACHY_MOVEIT2__MSG__DETAIL__ADD_OBSTACLE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "reachy_moveit2/msg/detail/add_obstacle__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'primitive'
#include "shape_msgs/msg/detail/solid_primitive__traits.hpp"
// Member 'pose'
#include "geometry_msgs/msg/detail/pose_stamped__traits.hpp"

namespace reachy_moveit2
{

namespace msg
{

inline void to_flow_style_yaml(
  const AddObstacle & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: id
  {
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << ", ";
  }

  // member: operation
  {
    out << "operation: ";
    rosidl_generator_traits::value_to_yaml(msg.operation, out);
    out << ", ";
  }

  // member: primitive
  {
    out << "primitive: ";
    to_flow_style_yaml(msg.primitive, out);
    out << ", ";
  }

  // member: pose
  {
    out << "pose: ";
    to_flow_style_yaml(msg.pose, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const AddObstacle & msg,
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

  // member: id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << "\n";
  }

  // member: operation
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "operation: ";
    rosidl_generator_traits::value_to_yaml(msg.operation, out);
    out << "\n";
  }

  // member: primitive
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "primitive:\n";
    to_block_style_yaml(msg.primitive, out, indentation + 2);
  }

  // member: pose
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pose:\n";
    to_block_style_yaml(msg.pose, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const AddObstacle & msg, bool use_flow_style = false)
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
  const reachy_moveit2::msg::AddObstacle & msg,
  std::ostream & out, size_t indentation = 0)
{
  reachy_moveit2::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use reachy_moveit2::msg::to_yaml() instead")]]
inline std::string to_yaml(const reachy_moveit2::msg::AddObstacle & msg)
{
  return reachy_moveit2::msg::to_yaml(msg);
}

template<>
inline const char * data_type<reachy_moveit2::msg::AddObstacle>()
{
  return "reachy_moveit2::msg::AddObstacle";
}

template<>
inline const char * name<reachy_moveit2::msg::AddObstacle>()
{
  return "reachy_moveit2/msg/AddObstacle";
}

template<>
struct has_fixed_size<reachy_moveit2::msg::AddObstacle>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<reachy_moveit2::msg::AddObstacle>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<reachy_moveit2::msg::AddObstacle>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // REACHY_MOVEIT2__MSG__DETAIL__ADD_OBSTACLE__TRAITS_HPP_
