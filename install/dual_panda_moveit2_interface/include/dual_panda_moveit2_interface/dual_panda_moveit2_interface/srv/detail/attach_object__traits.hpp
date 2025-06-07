// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from dual_panda_moveit2_interface:srv/AttachObject.idl
// generated code does not contain a copyright notice

#ifndef DUAL_PANDA_MOVEIT2_INTERFACE__SRV__DETAIL__ATTACH_OBJECT__TRAITS_HPP_
#define DUAL_PANDA_MOVEIT2_INTERFACE__SRV__DETAIL__ATTACH_OBJECT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "dual_panda_moveit2_interface/srv/detail/attach_object__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace dual_panda_moveit2_interface
{

namespace srv
{

inline void to_flow_style_yaml(
  const AttachObject_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: id
  {
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << ", ";
  }

  // member: link
  {
    out << "link: ";
    rosidl_generator_traits::value_to_yaml(msg.link, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const AttachObject_Request & msg,
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

  // member: link
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "link: ";
    rosidl_generator_traits::value_to_yaml(msg.link, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const AttachObject_Request & msg, bool use_flow_style = false)
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
  const dual_panda_moveit2_interface::srv::AttachObject_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  dual_panda_moveit2_interface::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use dual_panda_moveit2_interface::srv::to_yaml() instead")]]
inline std::string to_yaml(const dual_panda_moveit2_interface::srv::AttachObject_Request & msg)
{
  return dual_panda_moveit2_interface::srv::to_yaml(msg);
}

template<>
inline const char * data_type<dual_panda_moveit2_interface::srv::AttachObject_Request>()
{
  return "dual_panda_moveit2_interface::srv::AttachObject_Request";
}

template<>
inline const char * name<dual_panda_moveit2_interface::srv::AttachObject_Request>()
{
  return "dual_panda_moveit2_interface/srv/AttachObject_Request";
}

template<>
struct has_fixed_size<dual_panda_moveit2_interface::srv::AttachObject_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<dual_panda_moveit2_interface::srv::AttachObject_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<dual_panda_moveit2_interface::srv::AttachObject_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace dual_panda_moveit2_interface
{

namespace srv
{

inline void to_flow_style_yaml(
  const AttachObject_Response & msg,
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
  const AttachObject_Response & msg,
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

inline std::string to_yaml(const AttachObject_Response & msg, bool use_flow_style = false)
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
  const dual_panda_moveit2_interface::srv::AttachObject_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  dual_panda_moveit2_interface::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use dual_panda_moveit2_interface::srv::to_yaml() instead")]]
inline std::string to_yaml(const dual_panda_moveit2_interface::srv::AttachObject_Response & msg)
{
  return dual_panda_moveit2_interface::srv::to_yaml(msg);
}

template<>
inline const char * data_type<dual_panda_moveit2_interface::srv::AttachObject_Response>()
{
  return "dual_panda_moveit2_interface::srv::AttachObject_Response";
}

template<>
inline const char * name<dual_panda_moveit2_interface::srv::AttachObject_Response>()
{
  return "dual_panda_moveit2_interface/srv/AttachObject_Response";
}

template<>
struct has_fixed_size<dual_panda_moveit2_interface::srv::AttachObject_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<dual_panda_moveit2_interface::srv::AttachObject_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<dual_panda_moveit2_interface::srv::AttachObject_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<dual_panda_moveit2_interface::srv::AttachObject>()
{
  return "dual_panda_moveit2_interface::srv::AttachObject";
}

template<>
inline const char * name<dual_panda_moveit2_interface::srv::AttachObject>()
{
  return "dual_panda_moveit2_interface/srv/AttachObject";
}

template<>
struct has_fixed_size<dual_panda_moveit2_interface::srv::AttachObject>
  : std::integral_constant<
    bool,
    has_fixed_size<dual_panda_moveit2_interface::srv::AttachObject_Request>::value &&
    has_fixed_size<dual_panda_moveit2_interface::srv::AttachObject_Response>::value
  >
{
};

template<>
struct has_bounded_size<dual_panda_moveit2_interface::srv::AttachObject>
  : std::integral_constant<
    bool,
    has_bounded_size<dual_panda_moveit2_interface::srv::AttachObject_Request>::value &&
    has_bounded_size<dual_panda_moveit2_interface::srv::AttachObject_Response>::value
  >
{
};

template<>
struct is_service<dual_panda_moveit2_interface::srv::AttachObject>
  : std::true_type
{
};

template<>
struct is_service_request<dual_panda_moveit2_interface::srv::AttachObject_Request>
  : std::true_type
{
};

template<>
struct is_service_response<dual_panda_moveit2_interface::srv::AttachObject_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // DUAL_PANDA_MOVEIT2_INTERFACE__SRV__DETAIL__ATTACH_OBJECT__TRAITS_HPP_
