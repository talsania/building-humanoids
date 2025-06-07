// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from reachy_moveit2:msg/RobotControlCommand.idl
// generated code does not contain a copyright notice
#include "reachy_moveit2/msg/detail/robot_control_command__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `mode`
#include "rosidl_runtime_c/string_functions.h"
// Member `joint_state`
#include "sensor_msgs/msg/detail/joint_state__functions.h"
// Member `cartesian_target`
#include "geometry_msgs/msg/detail/pose_stamped__functions.h"

bool
reachy_moveit2__msg__RobotControlCommand__init(reachy_moveit2__msg__RobotControlCommand * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    reachy_moveit2__msg__RobotControlCommand__fini(msg);
    return false;
  }
  // mode
  if (!rosidl_runtime_c__String__init(&msg->mode)) {
    reachy_moveit2__msg__RobotControlCommand__fini(msg);
    return false;
  }
  // joint_state
  if (!sensor_msgs__msg__JointState__init(&msg->joint_state)) {
    reachy_moveit2__msg__RobotControlCommand__fini(msg);
    return false;
  }
  // cartesian_target
  if (!geometry_msgs__msg__PoseStamped__init(&msg->cartesian_target)) {
    reachy_moveit2__msg__RobotControlCommand__fini(msg);
    return false;
  }
  return true;
}

void
reachy_moveit2__msg__RobotControlCommand__fini(reachy_moveit2__msg__RobotControlCommand * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // mode
  rosidl_runtime_c__String__fini(&msg->mode);
  // joint_state
  sensor_msgs__msg__JointState__fini(&msg->joint_state);
  // cartesian_target
  geometry_msgs__msg__PoseStamped__fini(&msg->cartesian_target);
}

bool
reachy_moveit2__msg__RobotControlCommand__are_equal(const reachy_moveit2__msg__RobotControlCommand * lhs, const reachy_moveit2__msg__RobotControlCommand * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // mode
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->mode), &(rhs->mode)))
  {
    return false;
  }
  // joint_state
  if (!sensor_msgs__msg__JointState__are_equal(
      &(lhs->joint_state), &(rhs->joint_state)))
  {
    return false;
  }
  // cartesian_target
  if (!geometry_msgs__msg__PoseStamped__are_equal(
      &(lhs->cartesian_target), &(rhs->cartesian_target)))
  {
    return false;
  }
  return true;
}

bool
reachy_moveit2__msg__RobotControlCommand__copy(
  const reachy_moveit2__msg__RobotControlCommand * input,
  reachy_moveit2__msg__RobotControlCommand * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // mode
  if (!rosidl_runtime_c__String__copy(
      &(input->mode), &(output->mode)))
  {
    return false;
  }
  // joint_state
  if (!sensor_msgs__msg__JointState__copy(
      &(input->joint_state), &(output->joint_state)))
  {
    return false;
  }
  // cartesian_target
  if (!geometry_msgs__msg__PoseStamped__copy(
      &(input->cartesian_target), &(output->cartesian_target)))
  {
    return false;
  }
  return true;
}

reachy_moveit2__msg__RobotControlCommand *
reachy_moveit2__msg__RobotControlCommand__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  reachy_moveit2__msg__RobotControlCommand * msg = (reachy_moveit2__msg__RobotControlCommand *)allocator.allocate(sizeof(reachy_moveit2__msg__RobotControlCommand), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(reachy_moveit2__msg__RobotControlCommand));
  bool success = reachy_moveit2__msg__RobotControlCommand__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
reachy_moveit2__msg__RobotControlCommand__destroy(reachy_moveit2__msg__RobotControlCommand * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    reachy_moveit2__msg__RobotControlCommand__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
reachy_moveit2__msg__RobotControlCommand__Sequence__init(reachy_moveit2__msg__RobotControlCommand__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  reachy_moveit2__msg__RobotControlCommand * data = NULL;

  if (size) {
    data = (reachy_moveit2__msg__RobotControlCommand *)allocator.zero_allocate(size, sizeof(reachy_moveit2__msg__RobotControlCommand), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = reachy_moveit2__msg__RobotControlCommand__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        reachy_moveit2__msg__RobotControlCommand__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
reachy_moveit2__msg__RobotControlCommand__Sequence__fini(reachy_moveit2__msg__RobotControlCommand__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      reachy_moveit2__msg__RobotControlCommand__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

reachy_moveit2__msg__RobotControlCommand__Sequence *
reachy_moveit2__msg__RobotControlCommand__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  reachy_moveit2__msg__RobotControlCommand__Sequence * array = (reachy_moveit2__msg__RobotControlCommand__Sequence *)allocator.allocate(sizeof(reachy_moveit2__msg__RobotControlCommand__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = reachy_moveit2__msg__RobotControlCommand__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
reachy_moveit2__msg__RobotControlCommand__Sequence__destroy(reachy_moveit2__msg__RobotControlCommand__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    reachy_moveit2__msg__RobotControlCommand__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
reachy_moveit2__msg__RobotControlCommand__Sequence__are_equal(const reachy_moveit2__msg__RobotControlCommand__Sequence * lhs, const reachy_moveit2__msg__RobotControlCommand__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!reachy_moveit2__msg__RobotControlCommand__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
reachy_moveit2__msg__RobotControlCommand__Sequence__copy(
  const reachy_moveit2__msg__RobotControlCommand__Sequence * input,
  reachy_moveit2__msg__RobotControlCommand__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(reachy_moveit2__msg__RobotControlCommand);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    reachy_moveit2__msg__RobotControlCommand * data =
      (reachy_moveit2__msg__RobotControlCommand *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!reachy_moveit2__msg__RobotControlCommand__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          reachy_moveit2__msg__RobotControlCommand__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!reachy_moveit2__msg__RobotControlCommand__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
