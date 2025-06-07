// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from dual_panda_moveit2_interface:srv/SpawnObject.idl
// generated code does not contain a copyright notice
#include "dual_panda_moveit2_interface/srv/detail/spawn_object__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `objects`
#include "dual_panda_moveit2_interface/msg/detail/object_spec__functions.h"

bool
dual_panda_moveit2_interface__srv__SpawnObject_Request__init(dual_panda_moveit2_interface__srv__SpawnObject_Request * msg)
{
  if (!msg) {
    return false;
  }
  // objects
  if (!dual_panda_moveit2_interface__msg__ObjectSpec__Sequence__init(&msg->objects, 0)) {
    dual_panda_moveit2_interface__srv__SpawnObject_Request__fini(msg);
    return false;
  }
  return true;
}

void
dual_panda_moveit2_interface__srv__SpawnObject_Request__fini(dual_panda_moveit2_interface__srv__SpawnObject_Request * msg)
{
  if (!msg) {
    return;
  }
  // objects
  dual_panda_moveit2_interface__msg__ObjectSpec__Sequence__fini(&msg->objects);
}

bool
dual_panda_moveit2_interface__srv__SpawnObject_Request__are_equal(const dual_panda_moveit2_interface__srv__SpawnObject_Request * lhs, const dual_panda_moveit2_interface__srv__SpawnObject_Request * rhs)
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
dual_panda_moveit2_interface__srv__SpawnObject_Request__copy(
  const dual_panda_moveit2_interface__srv__SpawnObject_Request * input,
  dual_panda_moveit2_interface__srv__SpawnObject_Request * output)
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

dual_panda_moveit2_interface__srv__SpawnObject_Request *
dual_panda_moveit2_interface__srv__SpawnObject_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dual_panda_moveit2_interface__srv__SpawnObject_Request * msg = (dual_panda_moveit2_interface__srv__SpawnObject_Request *)allocator.allocate(sizeof(dual_panda_moveit2_interface__srv__SpawnObject_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(dual_panda_moveit2_interface__srv__SpawnObject_Request));
  bool success = dual_panda_moveit2_interface__srv__SpawnObject_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
dual_panda_moveit2_interface__srv__SpawnObject_Request__destroy(dual_panda_moveit2_interface__srv__SpawnObject_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    dual_panda_moveit2_interface__srv__SpawnObject_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
dual_panda_moveit2_interface__srv__SpawnObject_Request__Sequence__init(dual_panda_moveit2_interface__srv__SpawnObject_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dual_panda_moveit2_interface__srv__SpawnObject_Request * data = NULL;

  if (size) {
    data = (dual_panda_moveit2_interface__srv__SpawnObject_Request *)allocator.zero_allocate(size, sizeof(dual_panda_moveit2_interface__srv__SpawnObject_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = dual_panda_moveit2_interface__srv__SpawnObject_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        dual_panda_moveit2_interface__srv__SpawnObject_Request__fini(&data[i - 1]);
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
dual_panda_moveit2_interface__srv__SpawnObject_Request__Sequence__fini(dual_panda_moveit2_interface__srv__SpawnObject_Request__Sequence * array)
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
      dual_panda_moveit2_interface__srv__SpawnObject_Request__fini(&array->data[i]);
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

dual_panda_moveit2_interface__srv__SpawnObject_Request__Sequence *
dual_panda_moveit2_interface__srv__SpawnObject_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dual_panda_moveit2_interface__srv__SpawnObject_Request__Sequence * array = (dual_panda_moveit2_interface__srv__SpawnObject_Request__Sequence *)allocator.allocate(sizeof(dual_panda_moveit2_interface__srv__SpawnObject_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = dual_panda_moveit2_interface__srv__SpawnObject_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
dual_panda_moveit2_interface__srv__SpawnObject_Request__Sequence__destroy(dual_panda_moveit2_interface__srv__SpawnObject_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    dual_panda_moveit2_interface__srv__SpawnObject_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
dual_panda_moveit2_interface__srv__SpawnObject_Request__Sequence__are_equal(const dual_panda_moveit2_interface__srv__SpawnObject_Request__Sequence * lhs, const dual_panda_moveit2_interface__srv__SpawnObject_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!dual_panda_moveit2_interface__srv__SpawnObject_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
dual_panda_moveit2_interface__srv__SpawnObject_Request__Sequence__copy(
  const dual_panda_moveit2_interface__srv__SpawnObject_Request__Sequence * input,
  dual_panda_moveit2_interface__srv__SpawnObject_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(dual_panda_moveit2_interface__srv__SpawnObject_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    dual_panda_moveit2_interface__srv__SpawnObject_Request * data =
      (dual_panda_moveit2_interface__srv__SpawnObject_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!dual_panda_moveit2_interface__srv__SpawnObject_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          dual_panda_moveit2_interface__srv__SpawnObject_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!dual_panda_moveit2_interface__srv__SpawnObject_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `current_objects`
// already included above
// #include "dual_panda_moveit2_interface/msg/detail/object_spec__functions.h"

bool
dual_panda_moveit2_interface__srv__SpawnObject_Response__init(dual_panda_moveit2_interface__srv__SpawnObject_Response * msg)
{
  if (!msg) {
    return false;
  }
  // success
  // current_objects
  if (!dual_panda_moveit2_interface__msg__ObjectSpec__Sequence__init(&msg->current_objects, 0)) {
    dual_panda_moveit2_interface__srv__SpawnObject_Response__fini(msg);
    return false;
  }
  return true;
}

void
dual_panda_moveit2_interface__srv__SpawnObject_Response__fini(dual_panda_moveit2_interface__srv__SpawnObject_Response * msg)
{
  if (!msg) {
    return;
  }
  // success
  // current_objects
  dual_panda_moveit2_interface__msg__ObjectSpec__Sequence__fini(&msg->current_objects);
}

bool
dual_panda_moveit2_interface__srv__SpawnObject_Response__are_equal(const dual_panda_moveit2_interface__srv__SpawnObject_Response * lhs, const dual_panda_moveit2_interface__srv__SpawnObject_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  // current_objects
  if (!dual_panda_moveit2_interface__msg__ObjectSpec__Sequence__are_equal(
      &(lhs->current_objects), &(rhs->current_objects)))
  {
    return false;
  }
  return true;
}

bool
dual_panda_moveit2_interface__srv__SpawnObject_Response__copy(
  const dual_panda_moveit2_interface__srv__SpawnObject_Response * input,
  dual_panda_moveit2_interface__srv__SpawnObject_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  // current_objects
  if (!dual_panda_moveit2_interface__msg__ObjectSpec__Sequence__copy(
      &(input->current_objects), &(output->current_objects)))
  {
    return false;
  }
  return true;
}

dual_panda_moveit2_interface__srv__SpawnObject_Response *
dual_panda_moveit2_interface__srv__SpawnObject_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dual_panda_moveit2_interface__srv__SpawnObject_Response * msg = (dual_panda_moveit2_interface__srv__SpawnObject_Response *)allocator.allocate(sizeof(dual_panda_moveit2_interface__srv__SpawnObject_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(dual_panda_moveit2_interface__srv__SpawnObject_Response));
  bool success = dual_panda_moveit2_interface__srv__SpawnObject_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
dual_panda_moveit2_interface__srv__SpawnObject_Response__destroy(dual_panda_moveit2_interface__srv__SpawnObject_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    dual_panda_moveit2_interface__srv__SpawnObject_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
dual_panda_moveit2_interface__srv__SpawnObject_Response__Sequence__init(dual_panda_moveit2_interface__srv__SpawnObject_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dual_panda_moveit2_interface__srv__SpawnObject_Response * data = NULL;

  if (size) {
    data = (dual_panda_moveit2_interface__srv__SpawnObject_Response *)allocator.zero_allocate(size, sizeof(dual_panda_moveit2_interface__srv__SpawnObject_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = dual_panda_moveit2_interface__srv__SpawnObject_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        dual_panda_moveit2_interface__srv__SpawnObject_Response__fini(&data[i - 1]);
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
dual_panda_moveit2_interface__srv__SpawnObject_Response__Sequence__fini(dual_panda_moveit2_interface__srv__SpawnObject_Response__Sequence * array)
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
      dual_panda_moveit2_interface__srv__SpawnObject_Response__fini(&array->data[i]);
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

dual_panda_moveit2_interface__srv__SpawnObject_Response__Sequence *
dual_panda_moveit2_interface__srv__SpawnObject_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  dual_panda_moveit2_interface__srv__SpawnObject_Response__Sequence * array = (dual_panda_moveit2_interface__srv__SpawnObject_Response__Sequence *)allocator.allocate(sizeof(dual_panda_moveit2_interface__srv__SpawnObject_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = dual_panda_moveit2_interface__srv__SpawnObject_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
dual_panda_moveit2_interface__srv__SpawnObject_Response__Sequence__destroy(dual_panda_moveit2_interface__srv__SpawnObject_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    dual_panda_moveit2_interface__srv__SpawnObject_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
dual_panda_moveit2_interface__srv__SpawnObject_Response__Sequence__are_equal(const dual_panda_moveit2_interface__srv__SpawnObject_Response__Sequence * lhs, const dual_panda_moveit2_interface__srv__SpawnObject_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!dual_panda_moveit2_interface__srv__SpawnObject_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
dual_panda_moveit2_interface__srv__SpawnObject_Response__Sequence__copy(
  const dual_panda_moveit2_interface__srv__SpawnObject_Response__Sequence * input,
  dual_panda_moveit2_interface__srv__SpawnObject_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(dual_panda_moveit2_interface__srv__SpawnObject_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    dual_panda_moveit2_interface__srv__SpawnObject_Response * data =
      (dual_panda_moveit2_interface__srv__SpawnObject_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!dual_panda_moveit2_interface__srv__SpawnObject_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          dual_panda_moveit2_interface__srv__SpawnObject_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!dual_panda_moveit2_interface__srv__SpawnObject_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
