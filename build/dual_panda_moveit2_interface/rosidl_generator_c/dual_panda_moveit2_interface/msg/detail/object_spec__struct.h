// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from dual_panda_moveit2_interface:msg/ObjectSpec.idl
// generated code does not contain a copyright notice

#ifndef DUAL_PANDA_MOVEIT2_INTERFACE__MSG__DETAIL__OBJECT_SPEC__STRUCT_H_
#define DUAL_PANDA_MOVEIT2_INTERFACE__MSG__DETAIL__OBJECT_SPEC__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'id'
// Member 'type'
#include "rosidl_runtime_c/string.h"
// Member 'dimensions'
#include "rosidl_runtime_c/primitives_sequence.h"
// Member 'pose'
#include "geometry_msgs/msg/detail/pose__struct.h"

/// Struct defined in msg/ObjectSpec in the package dual_panda_moveit2_interface.
typedef struct dual_panda_moveit2_interface__msg__ObjectSpec
{
  rosidl_runtime_c__String id;
  rosidl_runtime_c__String type;
  rosidl_runtime_c__double__Sequence dimensions;
  geometry_msgs__msg__Pose pose;
} dual_panda_moveit2_interface__msg__ObjectSpec;

// Struct for a sequence of dual_panda_moveit2_interface__msg__ObjectSpec.
typedef struct dual_panda_moveit2_interface__msg__ObjectSpec__Sequence
{
  dual_panda_moveit2_interface__msg__ObjectSpec * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} dual_panda_moveit2_interface__msg__ObjectSpec__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DUAL_PANDA_MOVEIT2_INTERFACE__MSG__DETAIL__OBJECT_SPEC__STRUCT_H_
