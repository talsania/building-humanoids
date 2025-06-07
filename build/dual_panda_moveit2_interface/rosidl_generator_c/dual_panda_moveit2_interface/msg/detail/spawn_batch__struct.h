// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from dual_panda_moveit2_interface:msg/SpawnBatch.idl
// generated code does not contain a copyright notice

#ifndef DUAL_PANDA_MOVEIT2_INTERFACE__MSG__DETAIL__SPAWN_BATCH__STRUCT_H_
#define DUAL_PANDA_MOVEIT2_INTERFACE__MSG__DETAIL__SPAWN_BATCH__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'objects'
#include "dual_panda_moveit2_interface/msg/detail/object_spec__struct.h"

/// Struct defined in msg/SpawnBatch in the package dual_panda_moveit2_interface.
typedef struct dual_panda_moveit2_interface__msg__SpawnBatch
{
  dual_panda_moveit2_interface__msg__ObjectSpec__Sequence objects;
} dual_panda_moveit2_interface__msg__SpawnBatch;

// Struct for a sequence of dual_panda_moveit2_interface__msg__SpawnBatch.
typedef struct dual_panda_moveit2_interface__msg__SpawnBatch__Sequence
{
  dual_panda_moveit2_interface__msg__SpawnBatch * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} dual_panda_moveit2_interface__msg__SpawnBatch__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DUAL_PANDA_MOVEIT2_INTERFACE__MSG__DETAIL__SPAWN_BATCH__STRUCT_H_
