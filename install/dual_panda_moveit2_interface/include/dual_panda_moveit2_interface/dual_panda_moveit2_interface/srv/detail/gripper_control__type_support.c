// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from dual_panda_moveit2_interface:srv/GripperControl.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "dual_panda_moveit2_interface/srv/detail/gripper_control__rosidl_typesupport_introspection_c.h"
#include "dual_panda_moveit2_interface/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "dual_panda_moveit2_interface/srv/detail/gripper_control__functions.h"
#include "dual_panda_moveit2_interface/srv/detail/gripper_control__struct.h"


// Include directives for member types
// Member `gripper_name`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void dual_panda_moveit2_interface__srv__GripperControl_Request__rosidl_typesupport_introspection_c__GripperControl_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  dual_panda_moveit2_interface__srv__GripperControl_Request__init(message_memory);
}

void dual_panda_moveit2_interface__srv__GripperControl_Request__rosidl_typesupport_introspection_c__GripperControl_Request_fini_function(void * message_memory)
{
  dual_panda_moveit2_interface__srv__GripperControl_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember dual_panda_moveit2_interface__srv__GripperControl_Request__rosidl_typesupport_introspection_c__GripperControl_Request_message_member_array[2] = {
  {
    "gripper_name",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(dual_panda_moveit2_interface__srv__GripperControl_Request, gripper_name),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "open",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(dual_panda_moveit2_interface__srv__GripperControl_Request, open),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers dual_panda_moveit2_interface__srv__GripperControl_Request__rosidl_typesupport_introspection_c__GripperControl_Request_message_members = {
  "dual_panda_moveit2_interface__srv",  // message namespace
  "GripperControl_Request",  // message name
  2,  // number of fields
  sizeof(dual_panda_moveit2_interface__srv__GripperControl_Request),
  dual_panda_moveit2_interface__srv__GripperControl_Request__rosidl_typesupport_introspection_c__GripperControl_Request_message_member_array,  // message members
  dual_panda_moveit2_interface__srv__GripperControl_Request__rosidl_typesupport_introspection_c__GripperControl_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  dual_panda_moveit2_interface__srv__GripperControl_Request__rosidl_typesupport_introspection_c__GripperControl_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t dual_panda_moveit2_interface__srv__GripperControl_Request__rosidl_typesupport_introspection_c__GripperControl_Request_message_type_support_handle = {
  0,
  &dual_panda_moveit2_interface__srv__GripperControl_Request__rosidl_typesupport_introspection_c__GripperControl_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_dual_panda_moveit2_interface
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dual_panda_moveit2_interface, srv, GripperControl_Request)() {
  if (!dual_panda_moveit2_interface__srv__GripperControl_Request__rosidl_typesupport_introspection_c__GripperControl_Request_message_type_support_handle.typesupport_identifier) {
    dual_panda_moveit2_interface__srv__GripperControl_Request__rosidl_typesupport_introspection_c__GripperControl_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &dual_panda_moveit2_interface__srv__GripperControl_Request__rosidl_typesupport_introspection_c__GripperControl_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "dual_panda_moveit2_interface/srv/detail/gripper_control__rosidl_typesupport_introspection_c.h"
// already included above
// #include "dual_panda_moveit2_interface/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "dual_panda_moveit2_interface/srv/detail/gripper_control__functions.h"
// already included above
// #include "dual_panda_moveit2_interface/srv/detail/gripper_control__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void dual_panda_moveit2_interface__srv__GripperControl_Response__rosidl_typesupport_introspection_c__GripperControl_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  dual_panda_moveit2_interface__srv__GripperControl_Response__init(message_memory);
}

void dual_panda_moveit2_interface__srv__GripperControl_Response__rosidl_typesupport_introspection_c__GripperControl_Response_fini_function(void * message_memory)
{
  dual_panda_moveit2_interface__srv__GripperControl_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember dual_panda_moveit2_interface__srv__GripperControl_Response__rosidl_typesupport_introspection_c__GripperControl_Response_message_member_array[1] = {
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(dual_panda_moveit2_interface__srv__GripperControl_Response, success),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers dual_panda_moveit2_interface__srv__GripperControl_Response__rosidl_typesupport_introspection_c__GripperControl_Response_message_members = {
  "dual_panda_moveit2_interface__srv",  // message namespace
  "GripperControl_Response",  // message name
  1,  // number of fields
  sizeof(dual_panda_moveit2_interface__srv__GripperControl_Response),
  dual_panda_moveit2_interface__srv__GripperControl_Response__rosidl_typesupport_introspection_c__GripperControl_Response_message_member_array,  // message members
  dual_panda_moveit2_interface__srv__GripperControl_Response__rosidl_typesupport_introspection_c__GripperControl_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  dual_panda_moveit2_interface__srv__GripperControl_Response__rosidl_typesupport_introspection_c__GripperControl_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t dual_panda_moveit2_interface__srv__GripperControl_Response__rosidl_typesupport_introspection_c__GripperControl_Response_message_type_support_handle = {
  0,
  &dual_panda_moveit2_interface__srv__GripperControl_Response__rosidl_typesupport_introspection_c__GripperControl_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_dual_panda_moveit2_interface
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dual_panda_moveit2_interface, srv, GripperControl_Response)() {
  if (!dual_panda_moveit2_interface__srv__GripperControl_Response__rosidl_typesupport_introspection_c__GripperControl_Response_message_type_support_handle.typesupport_identifier) {
    dual_panda_moveit2_interface__srv__GripperControl_Response__rosidl_typesupport_introspection_c__GripperControl_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &dual_panda_moveit2_interface__srv__GripperControl_Response__rosidl_typesupport_introspection_c__GripperControl_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "dual_panda_moveit2_interface/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "dual_panda_moveit2_interface/srv/detail/gripper_control__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers dual_panda_moveit2_interface__srv__detail__gripper_control__rosidl_typesupport_introspection_c__GripperControl_service_members = {
  "dual_panda_moveit2_interface__srv",  // service namespace
  "GripperControl",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // dual_panda_moveit2_interface__srv__detail__gripper_control__rosidl_typesupport_introspection_c__GripperControl_Request_message_type_support_handle,
  NULL  // response message
  // dual_panda_moveit2_interface__srv__detail__gripper_control__rosidl_typesupport_introspection_c__GripperControl_Response_message_type_support_handle
};

static rosidl_service_type_support_t dual_panda_moveit2_interface__srv__detail__gripper_control__rosidl_typesupport_introspection_c__GripperControl_service_type_support_handle = {
  0,
  &dual_panda_moveit2_interface__srv__detail__gripper_control__rosidl_typesupport_introspection_c__GripperControl_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dual_panda_moveit2_interface, srv, GripperControl_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dual_panda_moveit2_interface, srv, GripperControl_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_dual_panda_moveit2_interface
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dual_panda_moveit2_interface, srv, GripperControl)() {
  if (!dual_panda_moveit2_interface__srv__detail__gripper_control__rosidl_typesupport_introspection_c__GripperControl_service_type_support_handle.typesupport_identifier) {
    dual_panda_moveit2_interface__srv__detail__gripper_control__rosidl_typesupport_introspection_c__GripperControl_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)dual_panda_moveit2_interface__srv__detail__gripper_control__rosidl_typesupport_introspection_c__GripperControl_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dual_panda_moveit2_interface, srv, GripperControl_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, dual_panda_moveit2_interface, srv, GripperControl_Response)()->data;
  }

  return &dual_panda_moveit2_interface__srv__detail__gripper_control__rosidl_typesupport_introspection_c__GripperControl_service_type_support_handle;
}
