// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from dual_panda_moveit2_interface:msg/SpawnBatch.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "dual_panda_moveit2_interface/msg/detail/spawn_batch__rosidl_typesupport_introspection_c.h"
#include "dual_panda_moveit2_interface/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "dual_panda_moveit2_interface/msg/detail/spawn_batch__functions.h"
#include "dual_panda_moveit2_interface/msg/detail/spawn_batch__struct.h"


// Include directives for member types
// Member `objects`
#include "dual_panda_moveit2_interface/msg/object_spec.h"
// Member `objects`
#include "dual_panda_moveit2_interface/msg/detail/object_spec__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void dual_panda_moveit2_interface__msg__SpawnBatch__rosidl_typesupport_introspection_c__SpawnBatch_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  dual_panda_moveit2_interface__msg__SpawnBatch__init(message_memory);
}

void dual_panda_moveit2_interface__msg__SpawnBatch__rosidl_typesupport_introspection_c__SpawnBatch_fini_function(void * message_memory)
{
  dual_panda_moveit2_interface__msg__SpawnBatch__fini(message_memory);
}

size_t dual_panda_moveit2_interface__msg__SpawnBatch__rosidl_typesupport_introspection_c__size_function__SpawnBatch__objects(
  const void * untyped_member)
{
  const dual_panda_moveit2_interface__msg__ObjectSpec__Sequence * member =
    (const dual_panda_moveit2_interface__msg__ObjectSpec__Sequence *)(untyped_member);
  return member->size;
}

const void * dual_panda_moveit2_interface__msg__SpawnBatch__rosidl_typesupport_introspection_c__get_const_function__SpawnBatch__objects(
  const void * untyped_member, size_t index)
{
  const dual_panda_moveit2_interface__msg__ObjectSpec__Sequence * member =
    (const dual_panda_moveit2_interface__msg__ObjectSpec__Sequence *)(untyped_member);
  return &member->data[index];
}

void * dual_panda_moveit2_interface__msg__SpawnBatch__rosidl_typesupport_introspection_c__get_function__SpawnBatch__objects(
  void * untyped_member, size_t index)
{
  dual_panda_moveit2_interface__msg__ObjectSpec__Sequence * member =
    (dual_panda_moveit2_interface__msg__ObjectSpec__Sequence *)(untyped_member);
  return &member->data[index];
}

void dual_panda_moveit2_interface__msg__SpawnBatch__rosidl_typesupport_introspection_c__fetch_function__SpawnBatch__objects(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const dual_panda_moveit2_interface__msg__ObjectSpec * item =
    ((const dual_panda_moveit2_interface__msg__ObjectSpec *)
    dual_panda_moveit2_interface__msg__SpawnBatch__rosidl_typesupport_introspection_c__get_const_function__SpawnBatch__objects(untyped_member, index));
  dual_panda_moveit2_interface__msg__ObjectSpec * value =
    (dual_panda_moveit2_interface__msg__ObjectSpec *)(untyped_value);
  *value = *item;
}

void dual_panda_moveit2_interface__msg__SpawnBatch__rosidl_typesupport_introspection_c__assign_function__SpawnBatch__objects(
  void * untyped_member, size_t index, const void * untyped_value)
{
  dual_panda_moveit2_interface__msg__ObjectSpec * item =
    ((dual_panda_moveit2_interface__msg__ObjectSpec *)
    dual_panda_moveit2_interface__msg__SpawnBatch__rosidl_typesupport_introspection_c__get_function__SpawnBatch__objects(untyped_member, index));
  const dual_panda_moveit2_interface__msg__ObjectSpec * value =
    (const dual_panda_moveit2_interface__msg__ObjectSpec *)(untyped_value);
  *item = *value;
}

bool dual_panda_moveit2_interface__msg__SpawnBatch__rosidl_typesupport_introspection_c__resize_function__SpawnBatch__objects(
  void * untyped_member, size_t size)
{
  dual_panda_moveit2_interface__msg__ObjectSpec__Sequence * member =
    (dual_panda_moveit2_interface__msg__ObjectSpec__Sequence *)(untyped_member);
  dual_panda_moveit2_interface__msg__ObjectSpec__Sequence__fini(member);
  return dual_panda_moveit2_interface__msg__ObjectSpec__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember dual_panda_moveit2_interface__msg__SpawnBatch__rosidl_typesupport_introspection_c__SpawnBatch_message_member_array[1] = {
  {
    "objects",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(dual_panda_moveit2_interface__msg__SpawnBatch, objects),  // bytes offset in struct
    NULL,  // default value
    dual_panda_moveit2_interface__msg__SpawnBatch__rosidl_typesupport_introspection_c__size_function__SpawnBatch__objects,  // size() function pointer
    dual_panda_moveit2_interface__msg__SpawnBatch__rosidl_typesupport_introspection_c__get_const_function__SpawnBatch__objects,  // get_const(index) function pointer
    dual_panda_moveit2_interface__msg__SpawnBatch__rosidl_typesupport_introspection_c__get_function__SpawnBatch__objects,  // get(index) function pointer
    dual_panda_moveit2_interface__msg__SpawnBatch__rosidl_typesupport_introspection_c__fetch_function__SpawnBatch__objects,  // fetch(index, &value) function pointer
    dual_panda_moveit2_interface__msg__SpawnBatch__rosidl_typesupport_introspection_c__assign_function__SpawnBatch__objects,  // assign(index, value) function pointer
    dual_panda_moveit2_interface__msg__SpawnBatch__rosidl_typesupport_introspection_c__resize_function__SpawnBatch__objects  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers dual_panda_moveit2_interface__msg__SpawnBatch__rosidl_typesupport_introspection_c__SpawnBatch_message_members = {
  "dual_panda_moveit2_interface__msg",  // message namespace
  "SpawnBatch",  // message name
  1,  // number of fields
  sizeof(dual_panda_moveit2_interface__msg__SpawnBatch),
  dual_panda_moveit2_interface__msg__SpawnBatch__rosidl_typesupport_introspection_c__SpawnBatch_message_member_array,  // message members
  dual_panda_moveit2_interface__msg__SpawnBatch__rosidl_typesupport_introspection_c__SpawnBatch_init_function,  // function to initialize message memory (memory has to be allocated)
  dual_panda_moveit2_interface__msg__SpawnBatch__rosidl_typesupport_introspection_c__SpawnBatch_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t dual_panda_moveit2_interface__msg__SpawnBatch__rosidl_typesupport_introspection_c__SpawnBatch_message_type_support_handle = {
  0,
  &dual_panda_moveit2_interface__msg__SpawnBatch__rosidl_typesupport_introspection_c__SpawnBatch_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_dual_panda_moveit2_interface
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dual_panda_moveit2_interface, msg, SpawnBatch)() {
  dual_panda_moveit2_interface__msg__SpawnBatch__rosidl_typesupport_introspection_c__SpawnBatch_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dual_panda_moveit2_interface, msg, ObjectSpec)();
  if (!dual_panda_moveit2_interface__msg__SpawnBatch__rosidl_typesupport_introspection_c__SpawnBatch_message_type_support_handle.typesupport_identifier) {
    dual_panda_moveit2_interface__msg__SpawnBatch__rosidl_typesupport_introspection_c__SpawnBatch_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &dual_panda_moveit2_interface__msg__SpawnBatch__rosidl_typesupport_introspection_c__SpawnBatch_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
