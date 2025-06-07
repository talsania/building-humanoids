// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from reachy_moveit2:msg/ExecuteRequest.idl
// generated code does not contain a copyright notice

#ifndef REACHY_MOVEIT2__MSG__DETAIL__EXECUTE_REQUEST__FUNCTIONS_H_
#define REACHY_MOVEIT2__MSG__DETAIL__EXECUTE_REQUEST__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "reachy_moveit2/msg/rosidl_generator_c__visibility_control.h"

#include "reachy_moveit2/msg/detail/execute_request__struct.h"

/// Initialize msg/ExecuteRequest message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * reachy_moveit2__msg__ExecuteRequest
 * )) before or use
 * reachy_moveit2__msg__ExecuteRequest__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_reachy_moveit2
bool
reachy_moveit2__msg__ExecuteRequest__init(reachy_moveit2__msg__ExecuteRequest * msg);

/// Finalize msg/ExecuteRequest message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_reachy_moveit2
void
reachy_moveit2__msg__ExecuteRequest__fini(reachy_moveit2__msg__ExecuteRequest * msg);

/// Create msg/ExecuteRequest message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * reachy_moveit2__msg__ExecuteRequest__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_reachy_moveit2
reachy_moveit2__msg__ExecuteRequest *
reachy_moveit2__msg__ExecuteRequest__create();

/// Destroy msg/ExecuteRequest message.
/**
 * It calls
 * reachy_moveit2__msg__ExecuteRequest__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_reachy_moveit2
void
reachy_moveit2__msg__ExecuteRequest__destroy(reachy_moveit2__msg__ExecuteRequest * msg);

/// Check for msg/ExecuteRequest message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_reachy_moveit2
bool
reachy_moveit2__msg__ExecuteRequest__are_equal(const reachy_moveit2__msg__ExecuteRequest * lhs, const reachy_moveit2__msg__ExecuteRequest * rhs);

/// Copy a msg/ExecuteRequest message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_reachy_moveit2
bool
reachy_moveit2__msg__ExecuteRequest__copy(
  const reachy_moveit2__msg__ExecuteRequest * input,
  reachy_moveit2__msg__ExecuteRequest * output);

/// Initialize array of msg/ExecuteRequest messages.
/**
 * It allocates the memory for the number of elements and calls
 * reachy_moveit2__msg__ExecuteRequest__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_reachy_moveit2
bool
reachy_moveit2__msg__ExecuteRequest__Sequence__init(reachy_moveit2__msg__ExecuteRequest__Sequence * array, size_t size);

/// Finalize array of msg/ExecuteRequest messages.
/**
 * It calls
 * reachy_moveit2__msg__ExecuteRequest__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_reachy_moveit2
void
reachy_moveit2__msg__ExecuteRequest__Sequence__fini(reachy_moveit2__msg__ExecuteRequest__Sequence * array);

/// Create array of msg/ExecuteRequest messages.
/**
 * It allocates the memory for the array and calls
 * reachy_moveit2__msg__ExecuteRequest__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_reachy_moveit2
reachy_moveit2__msg__ExecuteRequest__Sequence *
reachy_moveit2__msg__ExecuteRequest__Sequence__create(size_t size);

/// Destroy array of msg/ExecuteRequest messages.
/**
 * It calls
 * reachy_moveit2__msg__ExecuteRequest__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_reachy_moveit2
void
reachy_moveit2__msg__ExecuteRequest__Sequence__destroy(reachy_moveit2__msg__ExecuteRequest__Sequence * array);

/// Check for msg/ExecuteRequest message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_reachy_moveit2
bool
reachy_moveit2__msg__ExecuteRequest__Sequence__are_equal(const reachy_moveit2__msg__ExecuteRequest__Sequence * lhs, const reachy_moveit2__msg__ExecuteRequest__Sequence * rhs);

/// Copy an array of msg/ExecuteRequest messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_reachy_moveit2
bool
reachy_moveit2__msg__ExecuteRequest__Sequence__copy(
  const reachy_moveit2__msg__ExecuteRequest__Sequence * input,
  reachy_moveit2__msg__ExecuteRequest__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // REACHY_MOVEIT2__MSG__DETAIL__EXECUTE_REQUEST__FUNCTIONS_H_
