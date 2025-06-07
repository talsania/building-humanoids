// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from reachy_moveit2:msg/AddObstacle.idl
// generated code does not contain a copyright notice

#ifndef REACHY_MOVEIT2__MSG__DETAIL__ADD_OBSTACLE__FUNCTIONS_H_
#define REACHY_MOVEIT2__MSG__DETAIL__ADD_OBSTACLE__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "reachy_moveit2/msg/rosidl_generator_c__visibility_control.h"

#include "reachy_moveit2/msg/detail/add_obstacle__struct.h"

/// Initialize msg/AddObstacle message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * reachy_moveit2__msg__AddObstacle
 * )) before or use
 * reachy_moveit2__msg__AddObstacle__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_reachy_moveit2
bool
reachy_moveit2__msg__AddObstacle__init(reachy_moveit2__msg__AddObstacle * msg);

/// Finalize msg/AddObstacle message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_reachy_moveit2
void
reachy_moveit2__msg__AddObstacle__fini(reachy_moveit2__msg__AddObstacle * msg);

/// Create msg/AddObstacle message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * reachy_moveit2__msg__AddObstacle__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_reachy_moveit2
reachy_moveit2__msg__AddObstacle *
reachy_moveit2__msg__AddObstacle__create();

/// Destroy msg/AddObstacle message.
/**
 * It calls
 * reachy_moveit2__msg__AddObstacle__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_reachy_moveit2
void
reachy_moveit2__msg__AddObstacle__destroy(reachy_moveit2__msg__AddObstacle * msg);

/// Check for msg/AddObstacle message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_reachy_moveit2
bool
reachy_moveit2__msg__AddObstacle__are_equal(const reachy_moveit2__msg__AddObstacle * lhs, const reachy_moveit2__msg__AddObstacle * rhs);

/// Copy a msg/AddObstacle message.
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
reachy_moveit2__msg__AddObstacle__copy(
  const reachy_moveit2__msg__AddObstacle * input,
  reachy_moveit2__msg__AddObstacle * output);

/// Initialize array of msg/AddObstacle messages.
/**
 * It allocates the memory for the number of elements and calls
 * reachy_moveit2__msg__AddObstacle__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_reachy_moveit2
bool
reachy_moveit2__msg__AddObstacle__Sequence__init(reachy_moveit2__msg__AddObstacle__Sequence * array, size_t size);

/// Finalize array of msg/AddObstacle messages.
/**
 * It calls
 * reachy_moveit2__msg__AddObstacle__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_reachy_moveit2
void
reachy_moveit2__msg__AddObstacle__Sequence__fini(reachy_moveit2__msg__AddObstacle__Sequence * array);

/// Create array of msg/AddObstacle messages.
/**
 * It allocates the memory for the array and calls
 * reachy_moveit2__msg__AddObstacle__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_reachy_moveit2
reachy_moveit2__msg__AddObstacle__Sequence *
reachy_moveit2__msg__AddObstacle__Sequence__create(size_t size);

/// Destroy array of msg/AddObstacle messages.
/**
 * It calls
 * reachy_moveit2__msg__AddObstacle__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_reachy_moveit2
void
reachy_moveit2__msg__AddObstacle__Sequence__destroy(reachy_moveit2__msg__AddObstacle__Sequence * array);

/// Check for msg/AddObstacle message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_reachy_moveit2
bool
reachy_moveit2__msg__AddObstacle__Sequence__are_equal(const reachy_moveit2__msg__AddObstacle__Sequence * lhs, const reachy_moveit2__msg__AddObstacle__Sequence * rhs);

/// Copy an array of msg/AddObstacle messages.
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
reachy_moveit2__msg__AddObstacle__Sequence__copy(
  const reachy_moveit2__msg__AddObstacle__Sequence * input,
  reachy_moveit2__msg__AddObstacle__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // REACHY_MOVEIT2__MSG__DETAIL__ADD_OBSTACLE__FUNCTIONS_H_
