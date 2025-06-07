// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from reachy_moveit2:msg/RobotControlCommand.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "reachy_moveit2/msg/detail/robot_control_command__rosidl_typesupport_introspection_c.h"
#include "reachy_moveit2/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "reachy_moveit2/msg/detail/robot_control_command__functions.h"
#include "reachy_moveit2/msg/detail/robot_control_command__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `mode`
#include "rosidl_runtime_c/string_functions.h"
// Member `joint_state`
#include "sensor_msgs/msg/joint_state.h"
// Member `joint_state`
#include "sensor_msgs/msg/detail/joint_state__rosidl_typesupport_introspection_c.h"
// Member `cartesian_target`
#include "geometry_msgs/msg/pose_stamped.h"
// Member `cartesian_target`
#include "geometry_msgs/msg/detail/pose_stamped__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void reachy_moveit2__msg__RobotControlCommand__rosidl_typesupport_introspection_c__RobotControlCommand_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  reachy_moveit2__msg__RobotControlCommand__init(message_memory);
}

void reachy_moveit2__msg__RobotControlCommand__rosidl_typesupport_introspection_c__RobotControlCommand_fini_function(void * message_memory)
{
  reachy_moveit2__msg__RobotControlCommand__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember reachy_moveit2__msg__RobotControlCommand__rosidl_typesupport_introspection_c__RobotControlCommand_message_member_array[4] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(reachy_moveit2__msg__RobotControlCommand, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "mode",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(reachy_moveit2__msg__RobotControlCommand, mode),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "joint_state",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(reachy_moveit2__msg__RobotControlCommand, joint_state),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "cartesian_target",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(reachy_moveit2__msg__RobotControlCommand, cartesian_target),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers reachy_moveit2__msg__RobotControlCommand__rosidl_typesupport_introspection_c__RobotControlCommand_message_members = {
  "reachy_moveit2__msg",  // message namespace
  "RobotControlCommand",  // message name
  4,  // number of fields
  sizeof(reachy_moveit2__msg__RobotControlCommand),
  reachy_moveit2__msg__RobotControlCommand__rosidl_typesupport_introspection_c__RobotControlCommand_message_member_array,  // message members
  reachy_moveit2__msg__RobotControlCommand__rosidl_typesupport_introspection_c__RobotControlCommand_init_function,  // function to initialize message memory (memory has to be allocated)
  reachy_moveit2__msg__RobotControlCommand__rosidl_typesupport_introspection_c__RobotControlCommand_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t reachy_moveit2__msg__RobotControlCommand__rosidl_typesupport_introspection_c__RobotControlCommand_message_type_support_handle = {
  0,
  &reachy_moveit2__msg__RobotControlCommand__rosidl_typesupport_introspection_c__RobotControlCommand_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_reachy_moveit2
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, reachy_moveit2, msg, RobotControlCommand)() {
  reachy_moveit2__msg__RobotControlCommand__rosidl_typesupport_introspection_c__RobotControlCommand_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  reachy_moveit2__msg__RobotControlCommand__rosidl_typesupport_introspection_c__RobotControlCommand_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, sensor_msgs, msg, JointState)();
  reachy_moveit2__msg__RobotControlCommand__rosidl_typesupport_introspection_c__RobotControlCommand_message_member_array[3].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, PoseStamped)();
  if (!reachy_moveit2__msg__RobotControlCommand__rosidl_typesupport_introspection_c__RobotControlCommand_message_type_support_handle.typesupport_identifier) {
    reachy_moveit2__msg__RobotControlCommand__rosidl_typesupport_introspection_c__RobotControlCommand_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &reachy_moveit2__msg__RobotControlCommand__rosidl_typesupport_introspection_c__RobotControlCommand_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
