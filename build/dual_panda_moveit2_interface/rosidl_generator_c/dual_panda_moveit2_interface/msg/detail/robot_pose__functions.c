// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from dual_panda_moveit2_interface:msg/RobotPose.idl
// generated code does not contain a copyright notice
#include "dual_panda_moveit2_interface/msg/detail/robot_pose__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `head`
// Member `left_pose`
// Member `right_pose`
#include "geometry_msgs/msg/detail/pose_stamped__functions.h"

bool
dual_panda_moveit2_interface__msg__RobotPose__init(dual_panda_moveit2_interface__msg__RobotPose * msg)
{
  if (!msg) {
    return false;
  }
  // head
  if (!geometry_msgs__msg__PoseStamped__init(&msg->head)) {
    dual_panda_moveit2_interface__msg__RobotPose__fini(msg);
    return false;
  }
  // left_pose
  if (!geometry_msgs__msg__PoseStamped__init(&msg->left_pose)) {
    dual_panda_moveit2_interface__msg__RobotPose__fini(msg);
    return false;
  }
  // right_pose
  if (!geometry_msgs__msg__PoseStamped__init(&msg->right_pose)) {
    dual_panda_moveit2_interface__msg__RobotPose__fini(msg);
    return false;
  }
  return true;
}

void
dual_panda_moveit2_interface__msg__RobotPose__fini(dual_panda_moveit2_interface__msg__RobotPose * msg)
{
  if (!msg) {
    return;
  }
  // head
  geometry_msgs__msg__PoseStamped__fini(&msg->head);
  // left_pose
  geometry_msgs__msg__PoseStamped__fini(&msg->left_pose);
  // right_pose
  geometry_msgs__msg__PoseStamped__fini(&msg->right_pose);
}

bool
dual_panda_moveit2_interface__msg__RobotPose__are_equal(const dual_panda_moveit2_interface__msg__RobotPose * lhs, const dual_panda_moveit2_interface__msg__RobotPose * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // head
  if (!geometry_msgs__msg__PoseStamped__are_equal(
      &(lhs->head), &(rhs->head)))
  {
    return false;
  }
  // left_pose
  if (!geometry_msgs__msg__PoseStamped__are_equal(
      &(lhs->left_pose), &(rhs->left_pose)))
  {
    return false;
  }
  // right_pose
  if (!geometry_msgs__msg__PoseStamped__are_equal(
      &(lhs->right_pose), &(rhs->right_pose)))
  {
    return false;
  }
  return true;
}

bool
dual_panda_moveit2_interface__msg__RobotPose__copy(
  const dual_panda_moveit2_interface__msg__RobotPose * input,
  dual_panda_moveit2_interface__msg__RobotPose * output)
{
  if (!input || !output) {
    return false;
  }
  // head
  if (!geometry_msgs__msg__PoseStamped__copy(
      &(input->head), &(output->head)))
  {
    return false;
  }
  // left_pose
  if (!geometry_msgs__msg__PoseStamped__copy(
      &(input->left_pose), &(output->left_pose)))
  {
    return false;
  }
  // right_pose
  if (!geometry_msgs__msg__PoseStamped__copy(
      &(input->right_pose), &(output->right_pose)))
  {
    return false;
  }
  return true;
}

dual_panda_moveit2_interface__msg__RobotPose *
dual_panda_moveit2_interface__msg__RobotPose__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dual_panda_moveit2_interface__msg__RobotPose * msg = (dual_panda_moveit2_interface__msg__RobotPose *)allocator.allocate(sizeof(dual_panda_moveit2_interface__msg__RobotPose), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(dual_panda_moveit2_interface__msg__RobotPose));
  bool success = dual_panda_moveit2_interface__msg__RobotPose__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
dual_panda_moveit2_interface__msg__RobotPose__destroy(dual_panda_moveit2_interface__msg__RobotPose * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    dual_panda_moveit2_interface__msg__RobotPose__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
dual_panda_moveit2_interface__msg__RobotPose__Sequence__init(dual_panda_moveit2_interface__msg__RobotPose__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dual_panda_moveit2_interface__msg__RobotPose * data = NULL;

  if (size) {
    data = (dual_panda_moveit2_interface__msg__RobotPose *)allocator.zero_allocate(size, sizeof(dual_panda_moveit2_interface__msg__RobotPose), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = dual_panda_moveit2_interface__msg__RobotPose__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        dual_panda_moveit2_interface__msg__RobotPose__fini(&data[i - 1]);
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
dual_panda_moveit2_interface__msg__RobotPose__Sequence__fini(dual_panda_moveit2_interface__msg__RobotPose__Sequence * array)
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
      dual_panda_moveit2_interface__msg__RobotPose__fini(&array->data[i]);
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

dual_panda_moveit2_interface__msg__RobotPose__Sequence *
dual_panda_moveit2_interface__msg__RobotPose__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dual_panda_moveit2_interface__msg__RobotPose__Sequence * array = (dual_panda_moveit2_interface__msg__RobotPose__Sequence *)allocator.allocate(sizeof(dual_panda_moveit2_interface__msg__RobotPose__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = dual_panda_moveit2_interface__msg__RobotPose__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
dual_panda_moveit2_interface__msg__RobotPose__Sequence__destroy(dual_panda_moveit2_interface__msg__RobotPose__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    dual_panda_moveit2_interface__msg__RobotPose__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
dual_panda_moveit2_interface__msg__RobotPose__Sequence__are_equal(const dual_panda_moveit2_interface__msg__RobotPose__Sequence * lhs, const dual_panda_moveit2_interface__msg__RobotPose__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!dual_panda_moveit2_interface__msg__RobotPose__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
dual_panda_moveit2_interface__msg__RobotPose__Sequence__copy(
  const dual_panda_moveit2_interface__msg__RobotPose__Sequence * input,
  dual_panda_moveit2_interface__msg__RobotPose__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(dual_panda_moveit2_interface__msg__RobotPose);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    dual_panda_moveit2_interface__msg__RobotPose * data =
      (dual_panda_moveit2_interface__msg__RobotPose *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!dual_panda_moveit2_interface__msg__RobotPose__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          dual_panda_moveit2_interface__msg__RobotPose__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!dual_panda_moveit2_interface__msg__RobotPose__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
