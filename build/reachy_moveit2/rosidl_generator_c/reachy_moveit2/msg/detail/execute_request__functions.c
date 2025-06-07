// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from reachy_moveit2:msg/ExecuteRequest.idl
// generated code does not contain a copyright notice
#include "reachy_moveit2/msg/detail/execute_request__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `command`
#include "rosidl_runtime_c/string_functions.h"

bool
reachy_moveit2__msg__ExecuteRequest__init(reachy_moveit2__msg__ExecuteRequest * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    reachy_moveit2__msg__ExecuteRequest__fini(msg);
    return false;
  }
  // command
  if (!rosidl_runtime_c__String__init(&msg->command)) {
    reachy_moveit2__msg__ExecuteRequest__fini(msg);
    return false;
  }
  return true;
}

void
reachy_moveit2__msg__ExecuteRequest__fini(reachy_moveit2__msg__ExecuteRequest * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // command
  rosidl_runtime_c__String__fini(&msg->command);
}

bool
reachy_moveit2__msg__ExecuteRequest__are_equal(const reachy_moveit2__msg__ExecuteRequest * lhs, const reachy_moveit2__msg__ExecuteRequest * rhs)
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
  // command
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->command), &(rhs->command)))
  {
    return false;
  }
  return true;
}

bool
reachy_moveit2__msg__ExecuteRequest__copy(
  const reachy_moveit2__msg__ExecuteRequest * input,
  reachy_moveit2__msg__ExecuteRequest * output)
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
  // command
  if (!rosidl_runtime_c__String__copy(
      &(input->command), &(output->command)))
  {
    return false;
  }
  return true;
}

reachy_moveit2__msg__ExecuteRequest *
reachy_moveit2__msg__ExecuteRequest__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  reachy_moveit2__msg__ExecuteRequest * msg = (reachy_moveit2__msg__ExecuteRequest *)allocator.allocate(sizeof(reachy_moveit2__msg__ExecuteRequest), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(reachy_moveit2__msg__ExecuteRequest));
  bool success = reachy_moveit2__msg__ExecuteRequest__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
reachy_moveit2__msg__ExecuteRequest__destroy(reachy_moveit2__msg__ExecuteRequest * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    reachy_moveit2__msg__ExecuteRequest__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
reachy_moveit2__msg__ExecuteRequest__Sequence__init(reachy_moveit2__msg__ExecuteRequest__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  reachy_moveit2__msg__ExecuteRequest * data = NULL;

  if (size) {
    data = (reachy_moveit2__msg__ExecuteRequest *)allocator.zero_allocate(size, sizeof(reachy_moveit2__msg__ExecuteRequest), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = reachy_moveit2__msg__ExecuteRequest__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        reachy_moveit2__msg__ExecuteRequest__fini(&data[i - 1]);
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
reachy_moveit2__msg__ExecuteRequest__Sequence__fini(reachy_moveit2__msg__ExecuteRequest__Sequence * array)
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
      reachy_moveit2__msg__ExecuteRequest__fini(&array->data[i]);
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

reachy_moveit2__msg__ExecuteRequest__Sequence *
reachy_moveit2__msg__ExecuteRequest__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  reachy_moveit2__msg__ExecuteRequest__Sequence * array = (reachy_moveit2__msg__ExecuteRequest__Sequence *)allocator.allocate(sizeof(reachy_moveit2__msg__ExecuteRequest__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = reachy_moveit2__msg__ExecuteRequest__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
reachy_moveit2__msg__ExecuteRequest__Sequence__destroy(reachy_moveit2__msg__ExecuteRequest__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    reachy_moveit2__msg__ExecuteRequest__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
reachy_moveit2__msg__ExecuteRequest__Sequence__are_equal(const reachy_moveit2__msg__ExecuteRequest__Sequence * lhs, const reachy_moveit2__msg__ExecuteRequest__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!reachy_moveit2__msg__ExecuteRequest__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
reachy_moveit2__msg__ExecuteRequest__Sequence__copy(
  const reachy_moveit2__msg__ExecuteRequest__Sequence * input,
  reachy_moveit2__msg__ExecuteRequest__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(reachy_moveit2__msg__ExecuteRequest);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    reachy_moveit2__msg__ExecuteRequest * data =
      (reachy_moveit2__msg__ExecuteRequest *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!reachy_moveit2__msg__ExecuteRequest__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          reachy_moveit2__msg__ExecuteRequest__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!reachy_moveit2__msg__ExecuteRequest__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
