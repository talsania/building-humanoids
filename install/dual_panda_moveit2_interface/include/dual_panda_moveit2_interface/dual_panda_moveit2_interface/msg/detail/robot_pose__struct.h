// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from dual_panda_moveit2_interface:msg/RobotPose.idl
// generated code does not contain a copyright notice

#ifndef DUAL_PANDA_MOVEIT2_INTERFACE__MSG__DETAIL__ROBOT_POSE__STRUCT_H_
#define DUAL_PANDA_MOVEIT2_INTERFACE__MSG__DETAIL__ROBOT_POSE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'head'
// Member 'left_pose'
// Member 'right_pose'
#include "geometry_msgs/msg/detail/pose_stamped__struct.h"

/// Struct defined in msg/RobotPose in the package dual_panda_moveit2_interface.
/**
  * RobotPose.msg
 */
typedef struct dual_panda_moveit2_interface__msg__RobotPose
{
  geometry_msgs__msg__PoseStamped head;
  geometry_msgs__msg__PoseStamped left_pose;
  geometry_msgs__msg__PoseStamped right_pose;
} dual_panda_moveit2_interface__msg__RobotPose;

// Struct for a sequence of dual_panda_moveit2_interface__msg__RobotPose.
typedef struct dual_panda_moveit2_interface__msg__RobotPose__Sequence
{
  dual_panda_moveit2_interface__msg__RobotPose * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} dual_panda_moveit2_interface__msg__RobotPose__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DUAL_PANDA_MOVEIT2_INTERFACE__MSG__DETAIL__ROBOT_POSE__STRUCT_H_
