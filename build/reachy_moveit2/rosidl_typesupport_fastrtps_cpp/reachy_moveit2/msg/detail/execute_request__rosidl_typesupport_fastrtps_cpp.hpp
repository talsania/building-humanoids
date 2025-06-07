// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from reachy_moveit2:msg/ExecuteRequest.idl
// generated code does not contain a copyright notice

#ifndef REACHY_MOVEIT2__MSG__DETAIL__EXECUTE_REQUEST__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define REACHY_MOVEIT2__MSG__DETAIL__EXECUTE_REQUEST__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "reachy_moveit2/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "reachy_moveit2/msg/detail/execute_request__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace reachy_moveit2
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_reachy_moveit2
cdr_serialize(
  const reachy_moveit2::msg::ExecuteRequest & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_reachy_moveit2
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  reachy_moveit2::msg::ExecuteRequest & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_reachy_moveit2
get_serialized_size(
  const reachy_moveit2::msg::ExecuteRequest & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_reachy_moveit2
max_serialized_size_ExecuteRequest(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace reachy_moveit2

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_reachy_moveit2
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, reachy_moveit2, msg, ExecuteRequest)();

#ifdef __cplusplus
}
#endif

#endif  // REACHY_MOVEIT2__MSG__DETAIL__EXECUTE_REQUEST__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
