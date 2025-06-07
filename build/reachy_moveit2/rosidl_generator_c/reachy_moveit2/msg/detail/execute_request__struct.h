// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from reachy_moveit2:msg/ExecuteRequest.idl
// generated code does not contain a copyright notice

#ifndef REACHY_MOVEIT2__MSG__DETAIL__EXECUTE_REQUEST__STRUCT_H_
#define REACHY_MOVEIT2__MSG__DETAIL__EXECUTE_REQUEST__STRUCT_H_

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
// Member 'command'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/ExecuteRequest in the package reachy_moveit2.
/**
  * ExecuteRequest.msg
 */
typedef struct reachy_moveit2__msg__ExecuteRequest
{
  std_msgs__msg__Header header;
  /// Command for execution: e.g., "EXECUTE" or "CANCEL"
  rosidl_runtime_c__String command;
} reachy_moveit2__msg__ExecuteRequest;

// Struct for a sequence of reachy_moveit2__msg__ExecuteRequest.
typedef struct reachy_moveit2__msg__ExecuteRequest__Sequence
{
  reachy_moveit2__msg__ExecuteRequest * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} reachy_moveit2__msg__ExecuteRequest__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // REACHY_MOVEIT2__MSG__DETAIL__EXECUTE_REQUEST__STRUCT_H_
