// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from reachy_moveit2:msg/ExecuteRequest.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "reachy_moveit2/msg/detail/execute_request__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace reachy_moveit2
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void ExecuteRequest_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) reachy_moveit2::msg::ExecuteRequest(_init);
}

void ExecuteRequest_fini_function(void * message_memory)
{
  auto typed_message = static_cast<reachy_moveit2::msg::ExecuteRequest *>(message_memory);
  typed_message->~ExecuteRequest();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember ExecuteRequest_message_member_array[2] = {
  {
    "header",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<std_msgs::msg::Header>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(reachy_moveit2::msg::ExecuteRequest, header),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "command",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(reachy_moveit2::msg::ExecuteRequest, command),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers ExecuteRequest_message_members = {
  "reachy_moveit2::msg",  // message namespace
  "ExecuteRequest",  // message name
  2,  // number of fields
  sizeof(reachy_moveit2::msg::ExecuteRequest),
  ExecuteRequest_message_member_array,  // message members
  ExecuteRequest_init_function,  // function to initialize message memory (memory has to be allocated)
  ExecuteRequest_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t ExecuteRequest_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &ExecuteRequest_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace reachy_moveit2


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<reachy_moveit2::msg::ExecuteRequest>()
{
  return &::reachy_moveit2::msg::rosidl_typesupport_introspection_cpp::ExecuteRequest_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, reachy_moveit2, msg, ExecuteRequest)() {
  return &::reachy_moveit2::msg::rosidl_typesupport_introspection_cpp::ExecuteRequest_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
