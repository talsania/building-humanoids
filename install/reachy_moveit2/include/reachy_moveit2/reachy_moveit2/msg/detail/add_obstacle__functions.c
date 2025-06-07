// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from reachy_moveit2:msg/AddObstacle.idl
// generated code does not contain a copyright notice
#include "reachy_moveit2/msg/detail/add_obstacle__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `id`
// Member `operation`
#include "rosidl_runtime_c/string_functions.h"
// Member `primitive`
#include "shape_msgs/msg/detail/solid_primitive__functions.h"
// Member `pose`
#include "geometry_msgs/msg/detail/pose_stamped__functions.h"

bool
reachy_moveit2__msg__AddObstacle__init(reachy_moveit2__msg__AddObstacle * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    reachy_moveit2__msg__AddObstacle__fini(msg);
    return false;
  }
  // id
  if (!rosidl_runtime_c__String__init(&msg->id)) {
    reachy_moveit2__msg__AddObstacle__fini(msg);
    return false;
  }
  // operation
  if (!rosidl_runtime_c__String__init(&msg->operation)) {
    reachy_moveit2__msg__AddObstacle__fini(msg);
    return false;
  }
  // primitive
  if (!shape_msgs__msg__SolidPrimitive__init(&msg->primitive)) {
    reachy_moveit2__msg__AddObstacle__fini(msg);
    return false;
  }
  // pose
  if (!geometry_msgs__msg__PoseStamped__init(&msg->pose)) {
    reachy_moveit2__msg__AddObstacle__fini(msg);
    return false;
  }
  return true;
}

void
reachy_moveit2__msg__AddObstacle__fini(reachy_moveit2__msg__AddObstacle * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // id
  rosidl_runtime_c__String__fini(&msg->id);
  // operation
  rosidl_runtime_c__String__fini(&msg->operation);
  // primitive
  shape_msgs__msg__SolidPrimitive__fini(&msg->primitive);
  // pose
  geometry_msgs__msg__PoseStamped__fini(&msg->pose);
}

bool
reachy_moveit2__msg__AddObstacle__are_equal(const reachy_moveit2__msg__AddObstacle * lhs, const reachy_moveit2__msg__AddObstacle * rhs)
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
  // id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->id), &(rhs->id)))
  {
    return false;
  }
  // operation
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->operation), &(rhs->operation)))
  {
    return false;
  }
  // primitive
  if (!shape_msgs__msg__SolidPrimitive__are_equal(
      &(lhs->primitive), &(rhs->primitive)))
  {
    return false;
  }
  // pose
  if (!geometry_msgs__msg__PoseStamped__are_equal(
      &(lhs->pose), &(rhs->pose)))
  {
    return false;
  }
  return true;
}

bool
reachy_moveit2__msg__AddObstacle__copy(
  const reachy_moveit2__msg__AddObstacle * input,
  reachy_moveit2__msg__AddObstacle * output)
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
  // id
  if (!rosidl_runtime_c__String__copy(
      &(input->id), &(output->id)))
  {
    return false;
  }
  // operation
  if (!rosidl_runtime_c__String__copy(
      &(input->operation), &(output->operation)))
  {
    return false;
  }
  // primitive
  if (!shape_msgs__msg__SolidPrimitive__copy(
      &(input->primitive), &(output->primitive)))
  {
    return false;
  }
  // pose
  if (!geometry_msgs__msg__PoseStamped__copy(
      &(input->pose), &(output->pose)))
  {
    return false;
  }
  return true;
}

reachy_moveit2__msg__AddObstacle *
reachy_moveit2__msg__AddObstacle__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  reachy_moveit2__msg__AddObstacle * msg = (reachy_moveit2__msg__AddObstacle *)allocator.allocate(sizeof(reachy_moveit2__msg__AddObstacle), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(reachy_moveit2__msg__AddObstacle));
  bool success = reachy_moveit2__msg__AddObstacle__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
reachy_moveit2__msg__AddObstacle__destroy(reachy_moveit2__msg__AddObstacle * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    reachy_moveit2__msg__AddObstacle__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
reachy_moveit2__msg__AddObstacle__Sequence__init(reachy_moveit2__msg__AddObstacle__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  reachy_moveit2__msg__AddObstacle * data = NULL;

  if (size) {
    data = (reachy_moveit2__msg__AddObstacle *)allocator.zero_allocate(size, sizeof(reachy_moveit2__msg__AddObstacle), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = reachy_moveit2__msg__AddObstacle__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        reachy_moveit2__msg__AddObstacle__fini(&data[i - 1]);
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
reachy_moveit2__msg__AddObstacle__Sequence__fini(reachy_moveit2__msg__AddObstacle__Sequence * array)
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
      reachy_moveit2__msg__AddObstacle__fini(&array->data[i]);
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

reachy_moveit2__msg__AddObstacle__Sequence *
reachy_moveit2__msg__AddObstacle__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  reachy_moveit2__msg__AddObstacle__Sequence * array = (reachy_moveit2__msg__AddObstacle__Sequence *)allocator.allocate(sizeof(reachy_moveit2__msg__AddObstacle__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = reachy_moveit2__msg__AddObstacle__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
reachy_moveit2__msg__AddObstacle__Sequence__destroy(reachy_moveit2__msg__AddObstacle__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    reachy_moveit2__msg__AddObstacle__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
reachy_moveit2__msg__AddObstacle__Sequence__are_equal(const reachy_moveit2__msg__AddObstacle__Sequence * lhs, const reachy_moveit2__msg__AddObstacle__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!reachy_moveit2__msg__AddObstacle__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
reachy_moveit2__msg__AddObstacle__Sequence__copy(
  const reachy_moveit2__msg__AddObstacle__Sequence * input,
  reachy_moveit2__msg__AddObstacle__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(reachy_moveit2__msg__AddObstacle);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    reachy_moveit2__msg__AddObstacle * data =
      (reachy_moveit2__msg__AddObstacle *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!reachy_moveit2__msg__AddObstacle__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          reachy_moveit2__msg__AddObstacle__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!reachy_moveit2__msg__AddObstacle__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
