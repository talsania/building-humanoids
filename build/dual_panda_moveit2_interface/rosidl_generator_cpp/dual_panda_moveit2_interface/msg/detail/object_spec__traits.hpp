// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from dual_panda_moveit2_interface:msg/ObjectSpec.idl
// generated code does not contain a copyright notice

#ifndef DUAL_PANDA_MOVEIT2_INTERFACE__MSG__DETAIL__OBJECT_SPEC__TRAITS_HPP_
#define DUAL_PANDA_MOVEIT2_INTERFACE__MSG__DETAIL__OBJECT_SPEC__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "dual_panda_moveit2_interface/msg/detail/object_spec__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'pose'
#include "geometry_msgs/msg/detail/pose__traits.hpp"

namespace dual_panda_moveit2_interface
{

namespace msg
{

inline void to_flow_style_yaml(
  const ObjectSpec & msg,
  std::ostream & out)
{
  out << "{";
  // member: id
  {
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << ", ";
  }

  // member: type
  {
    out << "type: ";
    rosidl_generator_traits::value_to_yaml(msg.type, out);
    out << ", ";
  }

  // member: dimensions
  {
    if (msg.dimensions.size() == 0) {
      out << "dimensions: []";
    } else {
      out << "dimensions: [";
      size_t pending_items = msg.dimensions.size();
      for (auto item : msg.dimensions) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
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
  const ObjectSpec & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << "\n";
  }

  // member: type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "type: ";
    rosidl_generator_traits::value_to_yaml(msg.type, out);
    out << "\n";
  }

  // member: dimensions
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.dimensions.size() == 0) {
      out << "dimensions: []\n";
    } else {
      out << "dimensions:\n";
      for (auto item : msg.dimensions) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
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

inline std::string to_yaml(const ObjectSpec & msg, bool use_flow_style = false)
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
  const dual_panda_moveit2_interface::msg::ObjectSpec & msg,
  std::ostream & out, size_t indentation = 0)
{
  dual_panda_moveit2_interface::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use dual_panda_moveit2_interface::msg::to_yaml() instead")]]
inline std::string to_yaml(const dual_panda_moveit2_interface::msg::ObjectSpec & msg)
{
  return dual_panda_moveit2_interface::msg::to_yaml(msg);
}

template<>
inline const char * data_type<dual_panda_moveit2_interface::msg::ObjectSpec>()
{
  return "dual_panda_moveit2_interface::msg::ObjectSpec";
}

template<>
inline const char * name<dual_panda_moveit2_interface::msg::ObjectSpec>()
{
  return "dual_panda_moveit2_interface/msg/ObjectSpec";
}

template<>
struct has_fixed_size<dual_panda_moveit2_interface::msg::ObjectSpec>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<dual_panda_moveit2_interface::msg::ObjectSpec>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<dual_panda_moveit2_interface::msg::ObjectSpec>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // DUAL_PANDA_MOVEIT2_INTERFACE__MSG__DETAIL__OBJECT_SPEC__TRAITS_HPP_
