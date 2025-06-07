// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from dual_panda_moveit2_interface:msg/SpawnBatch.idl
// generated code does not contain a copyright notice
#include "dual_panda_moveit2_interface/msg/detail/spawn_batch__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `objects`
#include "dual_panda_moveit2_interface/msg/detail/object_spec__functions.h"

bool
dual_panda_moveit2_interface__msg__SpawnBatch__init(dual_panda_moveit2_interface__msg__SpawnBatch * msg)
{
  if (!msg) {
    return false;
  }
  // objects
  if (!dual_panda_moveit2_interface__msg__ObjectSpec__Sequence__init(&msg->objects, 0)) {
    dual_panda_moveit2_interface__msg__SpawnBatch__fini(msg);
    return false;
  }
  return true;
}

void
dual_panda_moveit2_interface__msg__SpawnBatch__fini(dual_panda_moveit2_interface__msg__SpawnBatch * msg)
{
  if (!msg) {
    return;
  }
  // objects
  dual_panda_moveit2_interface__msg__ObjectSpec__Sequence__fini(&msg->objects);
}

bool
dual_panda_moveit2_interface__msg__SpawnBatch__are_equal(const dual_panda_moveit2_interface__msg__SpawnBatch * lhs, const dual_panda_moveit2_interface__msg__SpawnBatch * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // objects
  if (!dual_panda_moveit2_interface__msg__ObjectSpec__Sequence__are_equal(
      &(lhs->objects), &(rhs->objects)))
  {
    return false;
  }
  return true;
}

bool
dual_panda_moveit2_interface__msg__SpawnBatch__copy(
  const dual_panda_moveit2_interface__msg__SpawnBatch * input,
  dual_panda_moveit2_interface__msg__SpawnBatch * output)
{
  if (!input || !output) {
    return false;
  }
  // objects
  if (!dual_panda_moveit2_interface__msg__ObjectSpec__Sequence__copy(
      &(input->objects), &(output->objects)))
  {
    return false;
  }
  return true;
}

dual_panda_moveit2_interface__msg__SpawnBatch *
dual_panda_moveit2_interface__msg__SpawnBatch__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dual_panda_moveit2_interface__msg__SpawnBatch * msg = (dual_panda_moveit2_interface__msg__SpawnBatch *)allocator.allocate(sizeof(dual_panda_moveit2_interface__msg__SpawnBatch), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(dual_panda_moveit2_interface__msg__SpawnBatch));
  bool success = dual_panda_moveit2_interface__msg__SpawnBatch__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
dual_panda_moveit2_interface__msg__SpawnBatch__destroy(dual_panda_moveit2_interface__msg__SpawnBatch * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    dual_panda_moveit2_interface__msg__SpawnBatch__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
dual_panda_moveit2_interface__msg__SpawnBatch__Sequence__init(dual_panda_moveit2_interface__msg__SpawnBatch__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dual_panda_moveit2_interface__msg__SpawnBatch * data = NULL;

  if (size) {
    data = (dual_panda_moveit2_interface__msg__SpawnBatch *)allocator.zero_allocate(size, sizeof(dual_panda_moveit2_interface__msg__SpawnBatch), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = dual_panda_moveit2_interface__msg__SpawnBatch__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        dual_panda_moveit2_interface__msg__SpawnBatch__fini(&data[i - 1]);
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
dual_panda_moveit2_interface__msg__SpawnBatch__Sequence__fini(dual_panda_moveit2_interface__msg__SpawnBatch__Sequence * array)
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
      dual_panda_moveit2_interface__msg__SpawnBatch__fini(&array->data[i]);
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

dual_panda_moveit2_interface__msg__SpawnBatch__Sequence *
dual_panda_moveit2_interface__msg__SpawnBatch__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dual_panda_moveit2_interface__msg__SpawnBatch__Sequence * array = (dual_panda_moveit2_interface__msg__SpawnBatch__Sequence *)allocator.allocate(sizeof(dual_panda_moveit2_interface__msg__SpawnBatch__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = dual_panda_moveit2_interface__msg__SpawnBatch__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
dual_panda_moveit2_interface__msg__SpawnBatch__Sequence__destroy(dual_panda_moveit2_interface__msg__SpawnBatch__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    dual_panda_moveit2_interface__msg__SpawnBatch__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
dual_panda_moveit2_interface__msg__SpawnBatch__Sequence__are_equal(const dual_panda_moveit2_interface__msg__SpawnBatch__Sequence * lhs, const dual_panda_moveit2_interface__msg__SpawnBatch__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!dual_panda_moveit2_interface__msg__SpawnBatch__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
dual_panda_moveit2_interface__msg__SpawnBatch__Sequence__copy(
  const dual_panda_moveit2_interface__msg__SpawnBatch__Sequence * input,
  dual_panda_moveit2_interface__msg__SpawnBatch__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(dual_panda_moveit2_interface__msg__SpawnBatch);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    dual_panda_moveit2_interface__msg__SpawnBatch * data =
      (dual_panda_moveit2_interface__msg__SpawnBatch *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!dual_panda_moveit2_interface__msg__SpawnBatch__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          dual_panda_moveit2_interface__msg__SpawnBatch__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!dual_panda_moveit2_interface__msg__SpawnBatch__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
