// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from dual_panda_moveit2_interface:srv/SpawnObject.idl
// generated code does not contain a copyright notice

#ifndef DUAL_PANDA_MOVEIT2_INTERFACE__SRV__DETAIL__SPAWN_OBJECT__TRAITS_HPP_
#define DUAL_PANDA_MOVEIT2_INTERFACE__SRV__DETAIL__SPAWN_OBJECT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "dual_panda_moveit2_interface/srv/detail/spawn_object__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'objects'
#include "dual_panda_moveit2_interface/msg/detail/object_spec__traits.hpp"

namespace dual_panda_moveit2_interface
{

namespace srv
{

inline void to_flow_style_yaml(
  const SpawnObject_Request & msg,
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
  const SpawnObject_Request & msg,
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

inline std::string to_yaml(const SpawnObject_Request & msg, bool use_flow_style = false)
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
  const dual_panda_moveit2_interface::srv::SpawnObject_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  dual_panda_moveit2_interface::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use dual_panda_moveit2_interface::srv::to_yaml() instead")]]
inline std::string to_yaml(const dual_panda_moveit2_interface::srv::SpawnObject_Request & msg)
{
  return dual_panda_moveit2_interface::srv::to_yaml(msg);
}

template<>
inline const char * data_type<dual_panda_moveit2_interface::srv::SpawnObject_Request>()
{
  return "dual_panda_moveit2_interface::srv::SpawnObject_Request";
}

template<>
inline const char * name<dual_panda_moveit2_interface::srv::SpawnObject_Request>()
{
  return "dual_panda_moveit2_interface/srv/SpawnObject_Request";
}

template<>
struct has_fixed_size<dual_panda_moveit2_interface::srv::SpawnObject_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<dual_panda_moveit2_interface::srv::SpawnObject_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<dual_panda_moveit2_interface::srv::SpawnObject_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'current_objects'
// already included above
// #include "dual_panda_moveit2_interface/msg/detail/object_spec__traits.hpp"

namespace dual_panda_moveit2_interface
{

namespace srv
{

inline void to_flow_style_yaml(
  const SpawnObject_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: current_objects
  {
    if (msg.current_objects.size() == 0) {
      out << "current_objects: []";
    } else {
      out << "current_objects: [";
      size_t pending_items = msg.current_objects.size();
      for (auto item : msg.current_objects) {
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
  const SpawnObject_Response & msg,
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

  // member: current_objects
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.current_objects.size() == 0) {
      out << "current_objects: []\n";
    } else {
      out << "current_objects:\n";
      for (auto item : msg.current_objects) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SpawnObject_Response & msg, bool use_flow_style = false)
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
  const dual_panda_moveit2_interface::srv::SpawnObject_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  dual_panda_moveit2_interface::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use dual_panda_moveit2_interface::srv::to_yaml() instead")]]
inline std::string to_yaml(const dual_panda_moveit2_interface::srv::SpawnObject_Response & msg)
{
  return dual_panda_moveit2_interface::srv::to_yaml(msg);
}

template<>
inline const char * data_type<dual_panda_moveit2_interface::srv::SpawnObject_Response>()
{
  return "dual_panda_moveit2_interface::srv::SpawnObject_Response";
}

template<>
inline const char * name<dual_panda_moveit2_interface::srv::SpawnObject_Response>()
{
  return "dual_panda_moveit2_interface/srv/SpawnObject_Response";
}

template<>
struct has_fixed_size<dual_panda_moveit2_interface::srv::SpawnObject_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<dual_panda_moveit2_interface::srv::SpawnObject_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<dual_panda_moveit2_interface::srv::SpawnObject_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<dual_panda_moveit2_interface::srv::SpawnObject>()
{
  return "dual_panda_moveit2_interface::srv::SpawnObject";
}

template<>
inline const char * name<dual_panda_moveit2_interface::srv::SpawnObject>()
{
  return "dual_panda_moveit2_interface/srv/SpawnObject";
}

template<>
struct has_fixed_size<dual_panda_moveit2_interface::srv::SpawnObject>
  : std::integral_constant<
    bool,
    has_fixed_size<dual_panda_moveit2_interface::srv::SpawnObject_Request>::value &&
    has_fixed_size<dual_panda_moveit2_interface::srv::SpawnObject_Response>::value
  >
{
};

template<>
struct has_bounded_size<dual_panda_moveit2_interface::srv::SpawnObject>
  : std::integral_constant<
    bool,
    has_bounded_size<dual_panda_moveit2_interface::srv::SpawnObject_Request>::value &&
    has_bounded_size<dual_panda_moveit2_interface::srv::SpawnObject_Response>::value
  >
{
};

template<>
struct is_service<dual_panda_moveit2_interface::srv::SpawnObject>
  : std::true_type
{
};

template<>
struct is_service_request<dual_panda_moveit2_interface::srv::SpawnObject_Request>
  : std::true_type
{
};

template<>
struct is_service_response<dual_panda_moveit2_interface::srv::SpawnObject_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // DUAL_PANDA_MOVEIT2_INTERFACE__SRV__DETAIL__SPAWN_OBJECT__TRAITS_HPP_
