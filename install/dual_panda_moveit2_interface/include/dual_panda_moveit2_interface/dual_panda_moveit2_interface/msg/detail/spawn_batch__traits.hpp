// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from dual_panda_moveit2_interface:msg/SpawnBatch.idl
// generated code does not contain a copyright notice

#ifndef DUAL_PANDA_MOVEIT2_INTERFACE__MSG__DETAIL__SPAWN_BATCH__TRAITS_HPP_
#define DUAL_PANDA_MOVEIT2_INTERFACE__MSG__DETAIL__SPAWN_BATCH__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "dual_panda_moveit2_interface/msg/detail/spawn_batch__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'objects'
#include "dual_panda_moveit2_interface/msg/detail/object_spec__traits.hpp"

namespace dual_panda_moveit2_interface
{

namespace msg
{

inline void to_flow_style_yaml(
  const SpawnBatch & msg,
  std::ostream & out)
{
  out << "{";
  // member: objects
  {
    if (msg.objects.size() == 0) {
      out << "objects: []";
    } else {
      out << "objects: [";
      size_t pending_items = msg.objects.size();
      for (auto item : msg.objects) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SpawnBatch & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: objects
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.objects.size() == 0) {
      out << "objects: []\n";
    } else {
      out << "objects:\n";
      for (auto item : msg.objects) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SpawnBatch & msg, bool use_flow_style = false)
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
  const dual_panda_moveit2_interface::msg::SpawnBatch & msg,
  std::ostream & out, size_t indentation = 0)
{
  dual_panda_moveit2_interface::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use dual_panda_moveit2_interface::msg::to_yaml() instead")]]
inline std::string to_yaml(const dual_panda_moveit2_interface::msg::SpawnBatch & msg)
{
  return dual_panda_moveit2_interface::msg::to_yaml(msg);
}

template<>
inline const char * data_type<dual_panda_moveit2_interface::msg::SpawnBatch>()
{
  return "dual_panda_moveit2_interface::msg::SpawnBatch";
}

template<>
inline const char * name<dual_panda_moveit2_interface::msg::SpawnBatch>()
{
  return "dual_panda_moveit2_interface/msg/SpawnBatch";
}

template<>
struct has_fixed_size<dual_panda_moveit2_interface::msg::SpawnBatch>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<dual_panda_moveit2_interface::msg::SpawnBatch>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<dual_panda_moveit2_interface::msg::SpawnBatch>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // DUAL_PANDA_MOVEIT2_INTERFACE__MSG__DETAIL__SPAWN_BATCH__TRAITS_HPP_
