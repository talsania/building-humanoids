// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from reachy_moveit2:msg/RobotControlCommand.idl
// generated code does not contain a copyright notice

#ifndef REACHY_MOVEIT2__MSG__DETAIL__ROBOT_CONTROL_COMMAND__STRUCT_H_
#define REACHY_MOVEIT2__MSG__DETAIL__ROBOT_CONTROL_COMMAND__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'mode'
#include "rosidl_runtime_c/string.h"
// Member 'joint_state'
#include "sensor_msgs/msg/detail/joint_state__struct.h"
// Member 'cartesian_target'
#include "geometry_msgs/msg/detail/pose_stamped__struct.h"

/// Struct defined in msg/RobotControlCommand in the package reachy_moveit2.
/**
  * RobotControlCommand.msg
 */
typedef struct reachy_moveit2__msg__RobotControlCommand
{
  std_msgs__msg__Header header;
  /// Mode for control: "cartesian" or "joint"
  rosidl_runtime_c__String mode;
  /// For joint state control (if mode is "joint")
  sensor_msgs__msg__JointState joint_state;
  /// For Cartesian control (if mode is "cartesian")
  geometry_msgs__msg__PoseStamped cartesian_target;
} reachy_moveit2__msg__RobotControlCommand;

// Struct for a sequence of reachy_moveit2__msg__RobotControlCommand.
typedef struct reachy_moveit2__msg__RobotControlCommand__Sequence
{
  reachy_moveit2__msg__RobotControlCommand * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} reachy_moveit2__msg__RobotControlCommand__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // REACHY_MOVEIT2__MSG__DETAIL__ROBOT_CONTROL_COMMAND__STRUCT_H_
