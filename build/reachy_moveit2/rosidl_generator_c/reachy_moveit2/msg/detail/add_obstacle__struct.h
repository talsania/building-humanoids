// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from reachy_moveit2:msg/AddObstacle.idl
// generated code does not contain a copyright notice

#ifndef REACHY_MOVEIT2__MSG__DETAIL__ADD_OBSTACLE__STRUCT_H_
#define REACHY_MOVEIT2__MSG__DETAIL__ADD_OBSTACLE__STRUCT_H_

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
// Member 'id'
// Member 'operation'
#include "rosidl_runtime_c/string.h"
// Member 'primitive'
#include "shape_msgs/msg/detail/solid_primitive__struct.h"
// Member 'pose'
#include "geometry_msgs/msg/detail/pose_stamped__struct.h"

/// Struct defined in msg/AddObstacle in the package reachy_moveit2.
/**
  * AddObstacle.msg
 */
typedef struct reachy_moveit2__msg__AddObstacle
{
  std_msgs__msg__Header header;
  /// Unique identifier for the obstacle.
  rosidl_runtime_c__String id;
  /// Operation to perform: "ADD" or "REMOVE"
  rosidl_runtime_c__String operation;
  /// Shape of the obstacle.
  shape_msgs__msg__SolidPrimitive primitive;
  /// Pose of the obstacle in the planning frame.
  geometry_msgs__msg__PoseStamped pose;
} reachy_moveit2__msg__AddObstacle;

// Struct for a sequence of reachy_moveit2__msg__AddObstacle.
typedef struct reachy_moveit2__msg__AddObstacle__Sequence
{
  reachy_moveit2__msg__AddObstacle * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} reachy_moveit2__msg__AddObstacle__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // REACHY_MOVEIT2__MSG__DETAIL__ADD_OBSTACLE__STRUCT_H_
