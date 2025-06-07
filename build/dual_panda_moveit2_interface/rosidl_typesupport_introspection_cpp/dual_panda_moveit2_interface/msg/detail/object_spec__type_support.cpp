// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from dual_panda_moveit2_interface:msg/ObjectSpec.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "dual_panda_moveit2_interface/msg/detail/object_spec__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace dual_panda_moveit2_interface
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void ObjectSpec_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) dual_panda_moveit2_interface::msg::ObjectSpec(_init);
}

void ObjectSpec_fini_function(void * message_memory)
{
  auto typed_message = static_cast<dual_panda_moveit2_interface::msg::ObjectSpec *>(message_memory);
  typed_message->~ObjectSpec();
}

size_t size_function__ObjectSpec__dimensions(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<double> *>(untyped_member);
  return member->size();
}

const void * get_const_function__ObjectSpec__dimensions(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<double> *>(untyped_member);
  return &member[index];
}

void * get_function__ObjectSpec__dimensions(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<double> *>(untyped_member);
  return &member[index];
}

void fetch_function__ObjectSpec__dimensions(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const double *>(
    get_const_function__ObjectSpec__dimensions(untyped_member, index));
  auto & value = *reinterpret_cast<double *>(untyped_value);
  value = item;
}

void assign_function__ObjectSpec__dimensions(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<double *>(
    get_function__ObjectSpec__dimensions(untyped_member, index));
  const auto & value = *reinterpret_cast<const double *>(untyped_value);
  item = value;
}

void resize_function__ObjectSpec__dimensions(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<double> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember ObjectSpec_message_member_array[4] = {
  {
    "id",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(dual_panda_moveit2_interface::msg::ObjectSpec, id),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "type",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(dual_panda_moveit2_interface::msg::ObjectSpec, type),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "dimensions",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(dual_panda_moveit2_interface::msg::ObjectSpec, dimensions),  // bytes offset in struct
    nullptr,  // default value
    size_function__ObjectSpec__dimensions,  // size() function pointer
    get_const_function__ObjectSpec__dimensions,  // get_const(index) function pointer
    get_function__ObjectSpec__dimensions,  // get(index) function pointer
    fetch_function__ObjectSpec__dimensions,  // fetch(index, &value) function pointer
    assign_function__ObjectSpec__dimensions,  // assign(index, value) function pointer
    resize_function__ObjectSpec__dimensions  // resize(index) function pointer
  },
  {
    "pose",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<geometry_msgs::msg::Pose>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(dual_panda_moveit2_interface::msg::ObjectSpec, pose),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers ObjectSpec_message_members = {
  "dual_panda_moveit2_interface::msg",  // message namespace
  "ObjectSpec",  // message name
  4,  // number of fields
  sizeof(dual_panda_moveit2_interface::msg::ObjectSpec),
  ObjectSpec_message_member_array,  // message members
  ObjectSpec_init_function,  // function to initialize message memory (memory has to be allocated)
  ObjectSpec_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t ObjectSpec_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &ObjectSpec_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace dual_panda_moveit2_interface


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<dual_panda_moveit2_interface::msg::ObjectSpec>()
{
  return &::dual_panda_moveit2_interface::msg::rosidl_typesupport_introspection_cpp::ObjectSpec_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, dual_panda_moveit2_interface, msg, ObjectSpec)() {
  return &::dual_panda_moveit2_interface::msg::rosidl_typesupport_introspection_cpp::ObjectSpec_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
