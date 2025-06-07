// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from dual_panda_moveit2_interface:action/Move.idl
// generated code does not contain a copyright notice

#ifndef DUAL_PANDA_MOVEIT2_INTERFACE__ACTION__DETAIL__MOVE__STRUCT_H_
#define DUAL_PANDA_MOVEIT2_INTERFACE__ACTION__DETAIL__MOVE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'head_pose'
// Member 'left_pose'
// Member 'right_pose'
#include "geometry_msgs/msg/detail/pose__struct.h"
// Member 'joint_values'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in action/Move in the package dual_panda_moveit2_interface.
typedef struct dual_panda_moveit2_interface__action__Move_Goal
{
  bool use_joint_state;
  geometry_msgs__msg__Pose head_pose;
  geometry_msgs__msg__Pose left_pose;
  geometry_msgs__msg__Pose right_pose;
  rosidl_runtime_c__double__Sequence joint_values;
} dual_panda_moveit2_interface__action__Move_Goal;

// Struct for a sequence of dual_panda_moveit2_interface__action__Move_Goal.
typedef struct dual_panda_moveit2_interface__action__Move_Goal__Sequence
{
  dual_panda_moveit2_interface__action__Move_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} dual_panda_moveit2_interface__action__Move_Goal__Sequence;


// Constants defined in the message

/// Struct defined in action/Move in the package dual_panda_moveit2_interface.
typedef struct dual_panda_moveit2_interface__action__Move_Result
{
  bool success;
} dual_panda_moveit2_interface__action__Move_Result;

// Struct for a sequence of dual_panda_moveit2_interface__action__Move_Result.
typedef struct dual_panda_moveit2_interface__action__Move_Result__Sequence
{
  dual_panda_moveit2_interface__action__Move_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} dual_panda_moveit2_interface__action__Move_Result__Sequence;


// Constants defined in the message

/// Struct defined in action/Move in the package dual_panda_moveit2_interface.
typedef struct dual_panda_moveit2_interface__action__Move_Feedback
{
  uint8_t structure_needs_at_least_one_member;
} dual_panda_moveit2_interface__action__Move_Feedback;

// Struct for a sequence of dual_panda_moveit2_interface__action__Move_Feedback.
typedef struct dual_panda_moveit2_interface__action__Move_Feedback__Sequence
{
  dual_panda_moveit2_interface__action__Move_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} dual_panda_moveit2_interface__action__Move_Feedback__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "dual_panda_moveit2_interface/action/detail/move__struct.h"

/// Struct defined in action/Move in the package dual_panda_moveit2_interface.
typedef struct dual_panda_moveit2_interface__action__Move_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  dual_panda_moveit2_interface__action__Move_Goal goal;
} dual_panda_moveit2_interface__action__Move_SendGoal_Request;

// Struct for a sequence of dual_panda_moveit2_interface__action__Move_SendGoal_Request.
typedef struct dual_panda_moveit2_interface__action__Move_SendGoal_Request__Sequence
{
  dual_panda_moveit2_interface__action__Move_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} dual_panda_moveit2_interface__action__Move_SendGoal_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/Move in the package dual_panda_moveit2_interface.
typedef struct dual_panda_moveit2_interface__action__Move_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} dual_panda_moveit2_interface__action__Move_SendGoal_Response;

// Struct for a sequence of dual_panda_moveit2_interface__action__Move_SendGoal_Response.
typedef struct dual_panda_moveit2_interface__action__Move_SendGoal_Response__Sequence
{
  dual_panda_moveit2_interface__action__Move_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} dual_panda_moveit2_interface__action__Move_SendGoal_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/Move in the package dual_panda_moveit2_interface.
typedef struct dual_panda_moveit2_interface__action__Move_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} dual_panda_moveit2_interface__action__Move_GetResult_Request;

// Struct for a sequence of dual_panda_moveit2_interface__action__Move_GetResult_Request.
typedef struct dual_panda_moveit2_interface__action__Move_GetResult_Request__Sequence
{
  dual_panda_moveit2_interface__action__Move_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} dual_panda_moveit2_interface__action__Move_GetResult_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "dual_panda_moveit2_interface/action/detail/move__struct.h"

/// Struct defined in action/Move in the package dual_panda_moveit2_interface.
typedef struct dual_panda_moveit2_interface__action__Move_GetResult_Response
{
  int8_t status;
  dual_panda_moveit2_interface__action__Move_Result result;
} dual_panda_moveit2_interface__action__Move_GetResult_Response;

// Struct for a sequence of dual_panda_moveit2_interface__action__Move_GetResult_Response.
typedef struct dual_panda_moveit2_interface__action__Move_GetResult_Response__Sequence
{
  dual_panda_moveit2_interface__action__Move_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} dual_panda_moveit2_interface__action__Move_GetResult_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "dual_panda_moveit2_interface/action/detail/move__struct.h"

/// Struct defined in action/Move in the package dual_panda_moveit2_interface.
typedef struct dual_panda_moveit2_interface__action__Move_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  dual_panda_moveit2_interface__action__Move_Feedback feedback;
} dual_panda_moveit2_interface__action__Move_FeedbackMessage;

// Struct for a sequence of dual_panda_moveit2_interface__action__Move_FeedbackMessage.
typedef struct dual_panda_moveit2_interface__action__Move_FeedbackMessage__Sequence
{
  dual_panda_moveit2_interface__action__Move_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} dual_panda_moveit2_interface__action__Move_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DUAL_PANDA_MOVEIT2_INTERFACE__ACTION__DETAIL__MOVE__STRUCT_H_
