// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from dual_panda_moveit2_interface:srv/GripperControl.idl
// generated code does not contain a copyright notice

#ifndef DUAL_PANDA_MOVEIT2_INTERFACE__SRV__DETAIL__GRIPPER_CONTROL__TRAITS_HPP_
#define DUAL_PANDA_MOVEIT2_INTERFACE__SRV__DETAIL__GRIPPER_CONTROL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "dual_panda_moveit2_interface/srv/detail/gripper_control__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace dual_panda_moveit2_interface
{

namespace srv
{

inline void to_flow_style_yaml(
  const GripperControl_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: gripper_name
  {
    out << "gripper_name: ";
    rosidl_generator_traits::value_to_yaml(msg.gripper_name, out);
    out << ", ";
  }

  // member: open
  {
    out << "open: ";
    rosidl_generator_traits::value_to_yaml(msg.open, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GripperControl_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: gripper_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gripper_name: ";
    rosidl_generator_traits::value_to_yaml(msg.gripper_name, out);
    out << "\n";
  }

  // member: open
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "open: ";
    rosidl_generator_traits::value_to_yaml(msg.open, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GripperControl_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace dual_panda_moveit2_interface

namespace rosidl_generator_traits
{

[[deprecated("use dual_panda_moveit2_interface::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const dual_panda_moveit2_interface::srv::GripperControl_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  dual_panda_moveit2_interface::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use dual_panda_moveit2_interface::srv::to_yaml() instead")]]
inline std::string to_yaml(const dual_panda_moveit2_interface::srv::GripperControl_Request & msg)
{
  return dual_panda_moveit2_interface::srv::to_yaml(msg);
}

template<>
inline const char * data_type<dual_panda_moveit2_interface::srv::GripperControl_Request>()
{
  return "dual_panda_moveit2_interface::srv::GripperControl_Request";
}

template<>
inline const char * name<dual_panda_moveit2_interface::srv::GripperControl_Request>()
{
  return "dual_panda_moveit2_interface/srv/GripperControl_Request";
}

template<>
struct has_fixed_size<dual_panda_moveit2_interface::srv::GripperControl_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<dual_panda_moveit2_interface::srv::GripperControl_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<dual_panda_moveit2_interface::srv::GripperControl_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace dual_panda_moveit2_interface
{

namespace srv
{

inline void to_flow_style_yaml(
  const GripperControl_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GripperControl_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GripperControl_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace dual_panda_moveit2_interface

namespace rosidl_generator_traits
{

[[deprecated("use dual_panda_moveit2_interface::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const dual_panda_moveit2_interface::srv::GripperControl_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  dual_panda_moveit2_interface::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use dual_panda_moveit2_interface::srv::to_yaml() instead")]]
inline std::string to_yaml(const dual_panda_moveit2_interface::srv::GripperControl_Response & msg)
{
  return dual_panda_moveit2_interface::srv::to_yaml(msg);
}

template<>
inline const char * data_type<dual_panda_moveit2_interface::srv::GripperControl_Response>()
{
  return "dual_panda_moveit2_interface::srv::GripperControl_Response";
}

template<>
inline const char * name<dual_panda_moveit2_interface::srv::GripperControl_Response>()
{
  return "dual_panda_moveit2_interface/srv/GripperControl_Response";
}

template<>
struct has_fixed_size<dual_panda_moveit2_interface::srv::GripperControl_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<dual_panda_moveit2_interface::srv::GripperControl_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<dual_panda_moveit2_interface::srv::GripperControl_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<dual_panda_moveit2_interface::srv::GripperControl>()
{
  return "dual_panda_moveit2_interface::srv::GripperControl";
}

template<>
inline const char * name<dual_panda_moveit2_interface::srv::GripperControl>()
{
  return "dual_panda_moveit2_interface/srv/GripperControl";
}

template<>
struct has_fixed_size<dual_panda_moveit2_interface::srv::GripperControl>
  : std::integral_constant<
    bool,
    has_fixed_size<dual_panda_moveit2_interface::srv::GripperControl_Request>::value &&
    has_fixed_size<dual_panda_moveit2_interface::srv::GripperControl_Response>::value
  >
{
};

template<>
struct has_bounded_size<dual_panda_moveit2_interface::srv::GripperControl>
  : std::integral_constant<
    bool,
    has_bounded_size<dual_panda_moveit2_interface::srv::GripperControl_Request>::value &&
    has_bounded_size<dual_panda_moveit2_interface::srv::GripperControl_Response>::value
  >
{
};

template<>
struct is_service<dual_panda_moveit2_interface::srv::GripperControl>
  : std::true_type
{
};

template<>
struct is_service_request<dual_panda_moveit2_interface::srv::GripperControl_Request>
  : std::true_type
{
};

template<>
struct is_service_response<dual_panda_moveit2_interface::srv::GripperControl_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // DUAL_PANDA_MOVEIT2_INTERFACE__SRV__DETAIL__GRIPPER_CONTROL__TRAITS_HPP_
