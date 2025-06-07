// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from dual_panda_moveit2_interface:srv/AttachObject.idl
// generated code does not contain a copyright notice

#ifndef DUAL_PANDA_MOVEIT2_INTERFACE__SRV__DETAIL__ATTACH_OBJECT__STRUCT_H_
#define DUAL_PANDA_MOVEIT2_INTERFACE__SRV__DETAIL__ATTACH_OBJECT__STRUCT_H_

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
// Member 'link'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/AttachObject in the package dual_panda_moveit2_interface.
typedef struct dual_panda_moveit2_interface__srv__AttachObject_Request
{
  rosidl_runtime_c__String id;
  rosidl_runtime_c__String link;
} dual_panda_moveit2_interface__srv__AttachObject_Request;

// Struct for a sequence of dual_panda_moveit2_interface__srv__AttachObject_Request.
typedef struct dual_panda_moveit2_interface__srv__AttachObject_Request__Sequence
{
  dual_panda_moveit2_interface__srv__AttachObject_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} dual_panda_moveit2_interface__srv__AttachObject_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/AttachObject in the package dual_panda_moveit2_interface.
typedef struct dual_panda_moveit2_interface__srv__AttachObject_Response
{
  bool success;
} dual_panda_moveit2_interface__srv__AttachObject_Response;

// Struct for a sequence of dual_panda_moveit2_interface__srv__AttachObject_Response.
typedef struct dual_panda_moveit2_interface__srv__AttachObject_Response__Sequence
{
  dual_panda_moveit2_interface__srv__AttachObject_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} dual_panda_moveit2_interface__srv__AttachObject_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DUAL_PANDA_MOVEIT2_INTERFACE__SRV__DETAIL__ATTACH_OBJECT__STRUCT_H_
