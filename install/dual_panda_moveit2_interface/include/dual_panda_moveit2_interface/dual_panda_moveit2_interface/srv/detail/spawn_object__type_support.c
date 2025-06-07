// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from dual_panda_moveit2_interface:srv/SpawnObject.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "dual_panda_moveit2_interface/srv/detail/spawn_object__rosidl_typesupport_introspection_c.h"
#include "dual_panda_moveit2_interface/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "dual_panda_moveit2_interface/srv/detail/spawn_object__functions.h"
#include "dual_panda_moveit2_interface/srv/detail/spawn_object__struct.h"


// Include directives for member types
// Member `objects`
#include "dual_panda_moveit2_interface/msg/object_spec.h"
// Member `objects`
#include "dual_panda_moveit2_interface/msg/detail/object_spec__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void dual_panda_moveit2_interface__srv__SpawnObject_Request__rosidl_typesupport_introspection_c__SpawnObject_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  dual_panda_moveit2_interface__srv__SpawnObject_Request__init(message_memory);
}

void dual_panda_moveit2_interface__srv__SpawnObject_Request__rosidl_typesupport_introspection_c__SpawnObject_Request_fini_function(void * message_memory)
{
  dual_panda_moveit2_interface__srv__SpawnObject_Request__fini(message_memory);
}

size_t dual_panda_moveit2_interface__srv__SpawnObject_Request__rosidl_typesupport_introspection_c__size_function__SpawnObject_Request__objects(
  const void * untyped_member)
{
  const dual_panda_moveit2_interface__msg__ObjectSpec__Sequence * member =
    (const dual_panda_moveit2_interface__msg__ObjectSpec__Sequence *)(untyped_member);
  return member->size;
}

const void * dual_panda_moveit2_interface__srv__SpawnObject_Request__rosidl_typesupport_introspection_c__get_const_function__SpawnObject_Request__objects(
  const void * untyped_member, size_t index)
{
  const dual_panda_moveit2_interface__msg__ObjectSpec__Sequence * member =
    (const dual_panda_moveit2_interface__msg__ObjectSpec__Sequence *)(untyped_member);
  return &member->data[index];
}

void * dual_panda_moveit2_interface__srv__SpawnObject_Request__rosidl_typesupport_introspection_c__get_function__SpawnObject_Request__objects(
  void * untyped_member, size_t index)
{
  dual_panda_moveit2_interface__msg__ObjectSpec__Sequence * member =
    (dual_panda_moveit2_interface__msg__ObjectSpec__Sequence *)(untyped_member);
  return &member->data[index];
}

void dual_panda_moveit2_interface__srv__SpawnObject_Request__rosidl_typesupport_introspection_c__fetch_function__SpawnObject_Request__objects(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const dual_panda_moveit2_interface__msg__ObjectSpec * item =
    ((const dual_panda_moveit2_interface__msg__ObjectSpec *)
    dual_panda_moveit2_interface__srv__SpawnObject_Request__rosidl_typesupport_introspection_c__get_const_function__SpawnObject_Request__objects(untyped_member, index));
  dual_panda_moveit2_interface__msg__ObjectSpec * value =
    (dual_panda_moveit2_interface__msg__ObjectSpec *)(untyped_value);
  *value = *item;
}

void dual_panda_moveit2_interface__srv__SpawnObject_Request__rosidl_typesupport_introspection_c__assign_function__SpawnObject_Request__objects(
  void * untyped_member, size_t index, const void * untyped_value)
{
  dual_panda_moveit2_interface__msg__ObjectSpec * item =
    ((dual_panda_moveit2_interface__msg__ObjectSpec *)
    dual_panda_moveit2_interface__srv__SpawnObject_Request__rosidl_typesupport_introspection_c__get_function__SpawnObject_Request__objects(untyped_member, index));
  const dual_panda_moveit2_interface__msg__ObjectSpec * value =
    (const dual_panda_moveit2_interface__msg__ObjectSpec *)(untyped_value);
  *item = *value;
}

bool dual_panda_moveit2_interface__srv__SpawnObject_Request__rosidl_typesupport_introspection_c__resize_function__SpawnObject_Request__objects(
  void * untyped_member, size_t size)
{
  dual_panda_moveit2_interface__msg__ObjectSpec__Sequence * member =
    (dual_panda_moveit2_interface__msg__ObjectSpec__Sequence *)(untyped_member);
  dual_panda_moveit2_interface__msg__ObjectSpec__Sequence__fini(member);
  return dual_panda_moveit2_interface__msg__ObjectSpec__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember dual_panda_moveit2_interface__srv__SpawnObject_Request__rosidl_typesupport_introspection_c__SpawnObject_Request_message_member_array[1] = {
  {
    "objects",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(dual_panda_moveit2_interface__srv__SpawnObject_Request, objects),  // bytes offset in struct
    NULL,  // default value
    dual_panda_moveit2_interface__srv__SpawnObject_Request__rosidl_typesupport_introspection_c__size_function__SpawnObject_Request__objects,  // size() function pointer
    dual_panda_moveit2_interface__srv__SpawnObject_Request__rosidl_typesupport_introspection_c__get_const_function__SpawnObject_Request__objects,  // get_const(index) function pointer
    dual_panda_moveit2_interface__srv__SpawnObject_Request__rosidl_typesupport_introspection_c__get_function__SpawnObject_Request__objects,  // get(index) function pointer
    dual_panda_moveit2_interface__srv__SpawnObject_Request__rosidl_typesupport_introspection_c__fetch_function__SpawnObject_Request__objects,  // fetch(index, &value) function pointer
    dual_panda_moveit2_interface__srv__SpawnObject_Request__rosidl_typesupport_introspection_c__assign_function__SpawnObject_Request__objects,  // assign(index, value) function pointer
    dual_panda_moveit2_interface__srv__SpawnObject_Request__rosidl_typesupport_introspection_c__resize_function__SpawnObject_Request__objects  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers dual_panda_moveit2_interface__srv__SpawnObject_Request__rosidl_typesupport_introspection_c__SpawnObject_Request_message_members = {
  "dual_panda_moveit2_interface__srv",  // message namespace
  "SpawnObject_Request",  // message name
  1,  // number of fields
  sizeof(dual_panda_moveit2_interface__srv__SpawnObject_Request),
  dual_panda_moveit2_interface__srv__SpawnObject_Request__rosidl_typesupport_introspection_c__SpawnObject_Request_message_member_array,  // message members
  dual_panda_moveit2_interface__srv__SpawnObject_Request__rosidl_typesupport_introspection_c__SpawnObject_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  dual_panda_moveit2_interface__srv__SpawnObject_Request__rosidl_typesupport_introspection_c__SpawnObject_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t dual_panda_moveit2_interface__srv__SpawnObject_Request__rosidl_typesupport_introspection_c__SpawnObject_Request_message_type_support_handle = {
  0,
  &dual_panda_moveit2_interface__srv__SpawnObject_Request__rosidl_typesupport_introspection_c__SpawnObject_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_dual_panda_moveit2_interface
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dual_panda_moveit2_interface, srv, SpawnObject_Request)() {
  dual_panda_moveit2_interface__srv__SpawnObject_Request__rosidl_typesupport_introspection_c__SpawnObject_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dual_panda_moveit2_interface, msg, ObjectSpec)();
  if (!dual_panda_moveit2_interface__srv__SpawnObject_Request__rosidl_typesupport_introspection_c__SpawnObject_Request_message_type_support_handle.typesupport_identifier) {
    dual_panda_moveit2_interface__srv__SpawnObject_Request__rosidl_typesupport_introspection_c__SpawnObject_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &dual_panda_moveit2_interface__srv__SpawnObject_Request__rosidl_typesupport_introspection_c__SpawnObject_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "dual_panda_moveit2_interface/srv/detail/spawn_object__rosidl_typesupport_introspection_c.h"
// already included above
// #include "dual_panda_moveit2_interface/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "dual_panda_moveit2_interface/srv/detail/spawn_object__functions.h"
// already included above
// #include "dual_panda_moveit2_interface/srv/detail/spawn_object__struct.h"


// Include directives for member types
// Member `current_objects`
// already included above
// #include "dual_panda_moveit2_interface/msg/object_spec.h"
// Member `current_objects`
// already included above
// #include "dual_panda_moveit2_interface/msg/detail/object_spec__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void dual_panda_moveit2_interface__srv__SpawnObject_Response__rosidl_typesupport_introspection_c__SpawnObject_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  dual_panda_moveit2_interface__srv__SpawnObject_Response__init(message_memory);
}

void dual_panda_moveit2_interface__srv__SpawnObject_Response__rosidl_typesupport_introspection_c__SpawnObject_Response_fini_function(void * message_memory)
{
  dual_panda_moveit2_interface__srv__SpawnObject_Response__fini(message_memory);
}

size_t dual_panda_moveit2_interface__srv__SpawnObject_Response__rosidl_typesupport_introspection_c__size_function__SpawnObject_Response__current_objects(
  const void * untyped_member)
{
  const dual_panda_moveit2_interface__msg__ObjectSpec__Sequence * member =
    (const dual_panda_moveit2_interface__msg__ObjectSpec__Sequence *)(untyped_member);
  return member->size;
}

const void * dual_panda_moveit2_interface__srv__SpawnObject_Response__rosidl_typesupport_introspection_c__get_const_function__SpawnObject_Response__current_objects(
  const void * untyped_member, size_t index)
{
  const dual_panda_moveit2_interface__msg__ObjectSpec__Sequence * member =
    (const dual_panda_moveit2_interface__msg__ObjectSpec__Sequence *)(untyped_member);
  return &member->data[index];
}

void * dual_panda_moveit2_interface__srv__SpawnObject_Response__rosidl_typesupport_introspection_c__get_function__SpawnObject_Response__current_objects(
  void * untyped_member, size_t index)
{
  dual_panda_moveit2_interface__msg__ObjectSpec__Sequence * member =
    (dual_panda_moveit2_interface__msg__ObjectSpec__Sequence *)(untyped_member);
  return &member->data[index];
}

void dual_panda_moveit2_interface__srv__SpawnObject_Response__rosidl_typesupport_introspection_c__fetch_function__SpawnObject_Response__current_objects(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const dual_panda_moveit2_interface__msg__ObjectSpec * item =
    ((const dual_panda_moveit2_interface__msg__ObjectSpec *)
    dual_panda_moveit2_interface__srv__SpawnObject_Response__rosidl_typesupport_introspection_c__get_const_function__SpawnObject_Response__current_objects(untyped_member, index));
  dual_panda_moveit2_interface__msg__ObjectSpec * value =
    (dual_panda_moveit2_interface__msg__ObjectSpec *)(untyped_value);
  *value = *item;
}

void dual_panda_moveit2_interface__srv__SpawnObject_Response__rosidl_typesupport_introspection_c__assign_function__SpawnObject_Response__current_objects(
  void * untyped_member, size_t index, const void * untyped_value)
{
  dual_panda_moveit2_interface__msg__ObjectSpec * item =
    ((dual_panda_moveit2_interface__msg__ObjectSpec *)
    dual_panda_moveit2_interface__srv__SpawnObject_Response__rosidl_typesupport_introspection_c__get_function__SpawnObject_Response__current_objects(untyped_member, index));
  const dual_panda_moveit2_interface__msg__ObjectSpec * value =
    (const dual_panda_moveit2_interface__msg__ObjectSpec *)(untyped_value);
  *item = *value;
}

bool dual_panda_moveit2_interface__srv__SpawnObject_Response__rosidl_typesupport_introspection_c__resize_function__SpawnObject_Response__current_objects(
  void * untyped_member, size_t size)
{
  dual_panda_moveit2_interface__msg__ObjectSpec__Sequence * member =
    (dual_panda_moveit2_interface__msg__ObjectSpec__Sequence *)(untyped_member);
  dual_panda_moveit2_interface__msg__ObjectSpec__Sequence__fini(member);
  return dual_panda_moveit2_interface__msg__ObjectSpec__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember dual_panda_moveit2_interface__srv__SpawnObject_Response__rosidl_typesupport_introspection_c__SpawnObject_Response_message_member_array[2] = {
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(dual_panda_moveit2_interface__srv__SpawnObject_Response, success),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "current_objects",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(dual_panda_moveit2_interface__srv__SpawnObject_Response, current_objects),  // bytes offset in struct
    NULL,  // default value
    dual_panda_moveit2_interface__srv__SpawnObject_Response__rosidl_typesupport_introspection_c__size_function__SpawnObject_Response__current_objects,  // size() function pointer
    dual_panda_moveit2_interface__srv__SpawnObject_Response__rosidl_typesupport_introspection_c__get_const_function__SpawnObject_Response__current_objects,  // get_const(index) function pointer
    dual_panda_moveit2_interface__srv__SpawnObject_Response__rosidl_typesupport_introspection_c__get_function__SpawnObject_Response__current_objects,  // get(index) function pointer
    dual_panda_moveit2_interface__srv__SpawnObject_Response__rosidl_typesupport_introspection_c__fetch_function__SpawnObject_Response__current_objects,  // fetch(index, &value) function pointer
    dual_panda_moveit2_interface__srv__SpawnObject_Response__rosidl_typesupport_introspection_c__assign_function__SpawnObject_Response__current_objects,  // assign(index, value) function pointer
    dual_panda_moveit2_interface__srv__SpawnObject_Response__rosidl_typesupport_introspection_c__resize_function__SpawnObject_Response__current_objects  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers dual_panda_moveit2_interface__srv__SpawnObject_Response__rosidl_typesupport_introspection_c__SpawnObject_Response_message_members = {
  "dual_panda_moveit2_interface__srv",  // message namespace
  "SpawnObject_Response",  // message name
  2,  // number of fields
  sizeof(dual_panda_moveit2_interface__srv__SpawnObject_Response),
  dual_panda_moveit2_interface__srv__SpawnObject_Response__rosidl_typesupport_introspection_c__SpawnObject_Response_message_member_array,  // message members
  dual_panda_moveit2_interface__srv__SpawnObject_Response__rosidl_typesupport_introspection_c__SpawnObject_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  dual_panda_moveit2_interface__srv__SpawnObject_Response__rosidl_typesupport_introspection_c__SpawnObject_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t dual_panda_moveit2_interface__srv__SpawnObject_Response__rosidl_typesupport_introspection_c__SpawnObject_Response_message_type_support_handle = {
  0,
  &dual_panda_moveit2_interface__srv__SpawnObject_Response__rosidl_typesupport_introspection_c__SpawnObject_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_dual_panda_moveit2_interface
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dual_panda_moveit2_interface, srv, SpawnObject_Response)() {
  dual_panda_moveit2_interface__srv__SpawnObject_Response__rosidl_typesupport_introspection_c__SpawnObject_Response_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dual_panda_moveit2_interface, msg, ObjectSpec)();
  if (!dual_panda_moveit2_interface__srv__SpawnObject_Response__rosidl_typesupport_introspection_c__SpawnObject_Response_message_type_support_handle.typesupport_identifier) {
    dual_panda_moveit2_interface__srv__SpawnObject_Response__rosidl_typesupport_introspection_c__SpawnObject_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &dual_panda_moveit2_interface__srv__SpawnObject_Response__rosidl_typesupport_introspection_c__SpawnObject_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "dual_panda_moveit2_interface/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "dual_panda_moveit2_interface/srv/detail/spawn_object__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers dual_panda_moveit2_interface__srv__detail__spawn_object__rosidl_typesupport_introspection_c__SpawnObject_service_members = {
  "dual_panda_moveit2_interface__srv",  // service namespace
  "SpawnObject",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // dual_panda_moveit2_interface__srv__detail__spawn_object__rosidl_typesupport_introspection_c__SpawnObject_Request_message_type_support_handle,
  NULL  // response message
  // dual_panda_moveit2_interface__srv__detail__spawn_object__rosidl_typesupport_introspection_c__SpawnObject_Response_message_type_support_handle
};

static rosidl_service_type_support_t dual_panda_moveit2_interface__srv__detail__spawn_object__rosidl_typesupport_introspection_c__SpawnObject_service_type_support_handle = {
  0,
  &dual_panda_moveit2_interface__srv__detail__spawn_object__rosidl_typesupport_introspection_c__SpawnObject_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dual_panda_moveit2_interface, srv, SpawnObject_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dual_panda_moveit2_interface, srv, SpawnObject_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_dual_panda_moveit2_interface
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dual_panda_moveit2_interface, srv, SpawnObject)() {
  if (!dual_panda_moveit2_interface__srv__detail__spawn_object__rosidl_typesupport_introspection_c__SpawnObject_service_type_support_handle.typesupport_identifier) {
    dual_panda_moveit2_interface__srv__detail__spawn_object__rosidl_typesupport_introspection_c__SpawnObject_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)dual_panda_moveit2_interface__srv__detail__spawn_object__rosidl_typesupport_introspection_c__SpawnObject_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dual_panda_moveit2_interface, srv, SpawnObject_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dual_panda_moveit2_interface, srv, SpawnObject_Response)()->data;
  }

  return &dual_panda_moveit2_interface__srv__detail__spawn_object__rosidl_typesupport_introspection_c__SpawnObject_service_type_support_handle;
}
