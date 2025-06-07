// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from dual_panda_moveit2_interface:msg/ObjectSpec.idl
// generated code does not contain a copyright notice

#ifndef DUAL_PANDA_MOVEIT2_INTERFACE__MSG__DETAIL__OBJECT_SPEC__FUNCTIONS_H_
#define DUAL_PANDA_MOVEIT2_INTERFACE__MSG__DETAIL__OBJECT_SPEC__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "dual_panda_moveit2_interface/msg/rosidl_generator_c__visibility_control.h"

#include "dual_panda_moveit2_interface/msg/detail/object_spec__struct.h"

/// Initialize msg/ObjectSpec message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * dual_panda_moveit2_interface__msg__ObjectSpec
 * )) before or use
 * dual_panda_moveit2_interface__msg__ObjectSpec__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_dual_panda_moveit2_interface
bool
dual_panda_moveit2_interface__msg__ObjectSpec__init(dual_panda_moveit2_interface__msg__ObjectSpec * msg);

/// Finalize msg/ObjectSpec message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_dual_panda_moveit2_interface
void
dual_panda_moveit2_interface__msg__ObjectSpec__fini(dual_panda_moveit2_interface__msg__ObjectSpec * msg);

/// Create msg/ObjectSpec message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * dual_panda_moveit2_interface__msg__ObjectSpec__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_dual_panda_moveit2_interface
dual_panda_moveit2_interface__msg__ObjectSpec *
dual_panda_moveit2_interface__msg__ObjectSpec__create();

/// Destroy msg/ObjectSpec message.
/**
 * It calls
 * dual_panda_moveit2_interface__msg__ObjectSpec__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_dual_panda_moveit2_interface
void
dual_panda_moveit2_interface__msg__ObjectSpec__destroy(dual_panda_moveit2_interface__msg__ObjectSpec * msg);

/// Check for msg/ObjectSpec message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_dual_panda_moveit2_interface
bool
dual_panda_moveit2_interface__msg__ObjectSpec__are_equal(const dual_panda_moveit2_interface__msg__ObjectSpec * lhs, const dual_panda_moveit2_interface__msg__ObjectSpec * rhs);

/// Copy a msg/ObjectSpec message.
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
ROSIDL_GENERATOR_C_PUBLIC_dual_panda_moveit2_interface
bool
dual_panda_moveit2_interface__msg__ObjectSpec__copy(
  const dual_panda_moveit2_interface__msg__ObjectSpec * input,
  dual_panda_moveit2_interface__msg__ObjectSpec * output);

/// Initialize array of msg/ObjectSpec messages.
/**
 * It allocates the memory for the number of elements and calls
 * dual_panda_moveit2_interface__msg__ObjectSpec__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_dual_panda_moveit2_interface
bool
dual_panda_moveit2_interface__msg__ObjectSpec__Sequence__init(dual_panda_moveit2_interface__msg__ObjectSpec__Sequence * array, size_t size);

/// Finalize array of msg/ObjectSpec messages.
/**
 * It calls
 * dual_panda_moveit2_interface__msg__ObjectSpec__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_dual_panda_moveit2_interface
void
dual_panda_moveit2_interface__msg__ObjectSpec__Sequence__fini(dual_panda_moveit2_interface__msg__ObjectSpec__Sequence * array);

/// Create array of msg/ObjectSpec messages.
/**
 * It allocates the memory for the array and calls
 * dual_panda_moveit2_interface__msg__ObjectSpec__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_dual_panda_moveit2_interface
dual_panda_moveit2_interface__msg__ObjectSpec__Sequence *
dual_panda_moveit2_interface__msg__ObjectSpec__Sequence__create(size_t size);

/// Destroy array of msg/ObjectSpec messages.
/**
 * It calls
 * dual_panda_moveit2_interface__msg__ObjectSpec__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_dual_panda_moveit2_interface
void
dual_panda_moveit2_interface__msg__ObjectSpec__Sequence__destroy(dual_panda_moveit2_interface__msg__ObjectSpec__Sequence * array);

/// Check for msg/ObjectSpec message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_dual_panda_moveit2_interface
bool
dual_panda_moveit2_interface__msg__ObjectSpec__Sequence__are_equal(const dual_panda_moveit2_interface__msg__ObjectSpec__Sequence * lhs, const dual_panda_moveit2_interface__msg__ObjectSpec__Sequence * rhs);

/// Copy an array of msg/ObjectSpec messages.
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
ROSIDL_GENERATOR_C_PUBLIC_dual_panda_moveit2_interface
bool
dual_panda_moveit2_interface__msg__ObjectSpec__Sequence__copy(
  const dual_panda_moveit2_interface__msg__ObjectSpec__Sequence * input,
  dual_panda_moveit2_interface__msg__ObjectSpec__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // DUAL_PANDA_MOVEIT2_INTERFACE__MSG__DETAIL__OBJECT_SPEC__FUNCTIONS_H_
