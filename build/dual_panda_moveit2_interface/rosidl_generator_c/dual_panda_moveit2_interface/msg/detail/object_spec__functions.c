// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from dual_panda_moveit2_interface:msg/ObjectSpec.idl
// generated code does not contain a copyright notice
#include "dual_panda_moveit2_interface/msg/detail/object_spec__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `id`
// Member `type`
#include "rosidl_runtime_c/string_functions.h"
// Member `dimensions`
#include "rosidl_runtime_c/primitives_sequence_functions.h"
// Member `pose`
#include "geometry_msgs/msg/detail/pose__functions.h"

bool
dual_panda_moveit2_interface__msg__ObjectSpec__init(dual_panda_moveit2_interface__msg__ObjectSpec * msg)
{
  if (!msg) {
    return false;
  }
  // id
  if (!rosidl_runtime_c__String__init(&msg->id)) {
    dual_panda_moveit2_interface__msg__ObjectSpec__fini(msg);
    return false;
  }
  // type
  if (!rosidl_runtime_c__String__init(&msg->type)) {
    dual_panda_moveit2_interface__msg__ObjectSpec__fini(msg);
    return false;
  }
  // dimensions
  if (!rosidl_runtime_c__double__Sequence__init(&msg->dimensions, 0)) {
    dual_panda_moveit2_interface__msg__ObjectSpec__fini(msg);
    return false;
  }
  // pose
  if (!geometry_msgs__msg__Pose__init(&msg->pose)) {
    dual_panda_moveit2_interface__msg__ObjectSpec__fini(msg);
    return false;
  }
  return true;
}

void
dual_panda_moveit2_interface__msg__ObjectSpec__fini(dual_panda_moveit2_interface__msg__ObjectSpec * msg)
{
  if (!msg) {
    return;
  }
  // id
  rosidl_runtime_c__String__fini(&msg->id);
  // type
  rosidl_runtime_c__String__fini(&msg->type);
  // dimensions
  rosidl_runtime_c__double__Sequence__fini(&msg->dimensions);
  // pose
  geometry_msgs__msg__Pose__fini(&msg->pose);
}

bool
dual_panda_moveit2_interface__msg__ObjectSpec__are_equal(const dual_panda_moveit2_interface__msg__ObjectSpec * lhs, const dual_panda_moveit2_interface__msg__ObjectSpec * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->id), &(rhs->id)))
  {
    return false;
  }
  // type
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->type), &(rhs->type)))
  {
    return false;
  }
  // dimensions
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->dimensions), &(rhs->dimensions)))
  {
    return false;
  }
  // pose
  if (!geometry_msgs__msg__Pose__are_equal(
      &(lhs->pose), &(rhs->pose)))
  {
    return false;
  }
  return true;
}

bool
dual_panda_moveit2_interface__msg__ObjectSpec__copy(
  const dual_panda_moveit2_interface__msg__ObjectSpec * input,
  dual_panda_moveit2_interface__msg__ObjectSpec * output)
{
  if (!input || !output) {
    return false;
  }
  // id
  if (!rosidl_runtime_c__String__copy(
      &(input->id), &(output->id)))
  {
    return false;
  }
  // type
  if (!rosidl_runtime_c__String__copy(
      &(input->type), &(output->type)))
  {
    return false;
  }
  // dimensions
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->dimensions), &(output->dimensions)))
  {
    return false;
  }
  // pose
  if (!geometry_msgs__msg__Pose__copy(
      &(input->pose), &(output->pose)))
  {
    return false;
  }
  return true;
}

dual_panda_moveit2_interface__msg__ObjectSpec *
dual_panda_moveit2_interface__msg__ObjectSpec__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dual_panda_moveit2_interface__msg__ObjectSpec * msg = (dual_panda_moveit2_interface__msg__ObjectSpec *)allocator.allocate(sizeof(dual_panda_moveit2_interface__msg__ObjectSpec), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(dual_panda_moveit2_interface__msg__ObjectSpec));
  bool success = dual_panda_moveit2_interface__msg__ObjectSpec__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
dual_panda_moveit2_interface__msg__ObjectSpec__destroy(dual_panda_moveit2_interface__msg__ObjectSpec * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    dual_panda_moveit2_interface__msg__ObjectSpec__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
dual_panda_moveit2_interface__msg__ObjectSpec__Sequence__init(dual_panda_moveit2_interface__msg__ObjectSpec__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dual_panda_moveit2_interface__msg__ObjectSpec * data = NULL;

  if (size) {
    data = (dual_panda_moveit2_interface__msg__ObjectSpec *)allocator.zero_allocate(size, sizeof(dual_panda_moveit2_interface__msg__ObjectSpec), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = dual_panda_moveit2_interface__msg__ObjectSpec__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        dual_panda_moveit2_interface__msg__ObjectSpec__fini(&data[i - 1]);
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
dual_panda_moveit2_interface__msg__ObjectSpec__Sequence__fini(dual_panda_moveit2_interface__msg__ObjectSpec__Sequence * array)
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
      dual_panda_moveit2_interface__msg__ObjectSpec__fini(&array->data[i]);
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

dual_panda_moveit2_interface__msg__ObjectSpec__Sequence *
dual_panda_moveit2_interface__msg__ObjectSpec__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dual_panda_moveit2_interface__msg__ObjectSpec__Sequence * array = (dual_panda_moveit2_interface__msg__ObjectSpec__Sequence *)allocator.allocate(sizeof(dual_panda_moveit2_interface__msg__ObjectSpec__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = dual_panda_moveit2_interface__msg__ObjectSpec__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
dual_panda_moveit2_interface__msg__ObjectSpec__Sequence__destroy(dual_panda_moveit2_interface__msg__ObjectSpec__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    dual_panda_moveit2_interface__msg__ObjectSpec__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
dual_panda_moveit2_interface__msg__ObjectSpec__Sequence__are_equal(const dual_panda_moveit2_interface__msg__ObjectSpec__Sequence * lhs, const dual_panda_moveit2_interface__msg__ObjectSpec__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!dual_panda_moveit2_interface__msg__ObjectSpec__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
dual_panda_moveit2_interface__msg__ObjectSpec__Sequence__copy(
  const dual_panda_moveit2_interface__msg__ObjectSpec__Sequence * input,
  dual_panda_moveit2_interface__msg__ObjectSpec__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(dual_panda_moveit2_interface__msg__ObjectSpec);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    dual_panda_moveit2_interface__msg__ObjectSpec * data =
      (dual_panda_moveit2_interface__msg__ObjectSpec *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!dual_panda_moveit2_interface__msg__ObjectSpec__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          dual_panda_moveit2_interface__msg__ObjectSpec__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!dual_panda_moveit2_interface__msg__ObjectSpec__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
