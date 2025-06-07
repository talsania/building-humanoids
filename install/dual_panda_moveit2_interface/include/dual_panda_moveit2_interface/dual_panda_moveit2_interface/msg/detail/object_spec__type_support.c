// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from dual_panda_moveit2_interface:msg/ObjectSpec.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "dual_panda_moveit2_interface/msg/detail/object_spec__rosidl_typesupport_introspection_c.h"
#include "dual_panda_moveit2_interface/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "dual_panda_moveit2_interface/msg/detail/object_spec__functions.h"
#include "dual_panda_moveit2_interface/msg/detail/object_spec__struct.h"


// Include directives for member types
// Member `id`
// Member `type`
#include "rosidl_runtime_c/string_functions.h"
// Member `dimensions`
#include "rosidl_runtime_c/primitives_sequence_functions.h"
// Member `pose`
#include "geometry_msgs/msg/pose.h"
// Member `pose`
#include "geometry_msgs/msg/detail/pose__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void dual_panda_moveit2_interface__msg__ObjectSpec__rosidl_typesupport_introspection_c__ObjectSpec_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  dual_panda_moveit2_interface__msg__ObjectSpec__init(message_memory);
}

void dual_panda_moveit2_interface__msg__ObjectSpec__rosidl_typesupport_introspection_c__ObjectSpec_fini_function(void * message_memory)
{
  dual_panda_moveit2_interface__msg__ObjectSpec__fini(message_memory);
}

size_t dual_panda_moveit2_interface__msg__ObjectSpec__rosidl_typesupport_introspection_c__size_function__ObjectSpec__dimensions(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * dual_panda_moveit2_interface__msg__ObjectSpec__rosidl_typesupport_introspection_c__get_const_function__ObjectSpec__dimensions(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * dual_panda_moveit2_interface__msg__ObjectSpec__rosidl_typesupport_introspection_c__get_function__ObjectSpec__dimensions(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void dual_panda_moveit2_interface__msg__ObjectSpec__rosidl_typesupport_introspection_c__fetch_function__ObjectSpec__dimensions(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    dual_panda_moveit2_interface__msg__ObjectSpec__rosidl_typesupport_introspection_c__get_const_function__ObjectSpec__dimensions(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void dual_panda_moveit2_interface__msg__ObjectSpec__rosidl_typesupport_introspection_c__assign_function__ObjectSpec__dimensions(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    dual_panda_moveit2_interface__msg__ObjectSpec__rosidl_typesupport_introspection_c__get_function__ObjectSpec__dimensions(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool dual_panda_moveit2_interface__msg__ObjectSpec__rosidl_typesupport_introspection_c__resize_function__ObjectSpec__dimensions(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember dual_panda_moveit2_interface__msg__ObjectSpec__rosidl_typesupport_introspection_c__ObjectSpec_message_member_array[4] = {
  {
    "id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(dual_panda_moveit2_interface__msg__ObjectSpec, id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "type",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(dual_panda_moveit2_interface__msg__ObjectSpec, type),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "dimensions",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(dual_panda_moveit2_interface__msg__ObjectSpec, dimensions),  // bytes offset in struct
    NULL,  // default value
    dual_panda_moveit2_interface__msg__ObjectSpec__rosidl_typesupport_introspection_c__size_function__ObjectSpec__dimensions,  // size() function pointer
    dual_panda_moveit2_interface__msg__ObjectSpec__rosidl_typesupport_introspection_c__get_const_function__ObjectSpec__dimensions,  // get_const(index) function pointer
    dual_panda_moveit2_interface__msg__ObjectSpec__rosidl_typesupport_introspection_c__get_function__ObjectSpec__dimensions,  // get(index) function pointer
    dual_panda_moveit2_interface__msg__ObjectSpec__rosidl_typesupport_introspection_c__fetch_function__ObjectSpec__dimensions,  // fetch(index, &value) function pointer
    dual_panda_moveit2_interface__msg__ObjectSpec__rosidl_typesupport_introspection_c__assign_function__ObjectSpec__dimensions,  // assign(index, value) function pointer
    dual_panda_moveit2_interface__msg__ObjectSpec__rosidl_typesupport_introspection_c__resize_function__ObjectSpec__dimensions  // resize(index) function pointer
  },
  {
    "pose",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(dual_panda_moveit2_interface__msg__ObjectSpec, pose),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers dual_panda_moveit2_interface__msg__ObjectSpec__rosidl_typesupport_introspection_c__ObjectSpec_message_members = {
  "dual_panda_moveit2_interface__msg",  // message namespace
  "ObjectSpec",  // message name
  4,  // number of fields
  sizeof(dual_panda_moveit2_interface__msg__ObjectSpec),
  dual_panda_moveit2_interface__msg__ObjectSpec__rosidl_typesupport_introspection_c__ObjectSpec_message_member_array,  // message members
  dual_panda_moveit2_interface__msg__ObjectSpec__rosidl_typesupport_introspection_c__ObjectSpec_init_function,  // function to initialize message memory (memory has to be allocated)
  dual_panda_moveit2_interface__msg__ObjectSpec__rosidl_typesupport_introspection_c__ObjectSpec_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t dual_panda_moveit2_interface__msg__ObjectSpec__rosidl_typesupport_introspection_c__ObjectSpec_message_type_support_handle = {
  0,
  &dual_panda_moveit2_interface__msg__ObjectSpec__rosidl_typesupport_introspection_c__ObjectSpec_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_dual_panda_moveit2_interface
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dual_panda_moveit2_interface, msg, ObjectSpec)() {
  dual_panda_moveit2_interface__msg__ObjectSpec__rosidl_typesupport_introspection_c__ObjectSpec_message_member_array[3].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Pose)();
  if (!dual_panda_moveit2_interface__msg__ObjectSpec__rosidl_typesupport_introspection_c__ObjectSpec_message_type_support_handle.typesupport_identifier) {
    dual_panda_moveit2_interface__msg__ObjectSpec__rosidl_typesupport_introspection_c__ObjectSpec_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &dual_panda_moveit2_interface__msg__ObjectSpec__rosidl_typesupport_introspection_c__ObjectSpec_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
