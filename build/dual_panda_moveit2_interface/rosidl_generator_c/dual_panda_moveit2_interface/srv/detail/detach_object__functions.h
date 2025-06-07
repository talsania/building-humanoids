// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from dual_panda_moveit2_interface:srv/DetachObject.idl
// generated code does not contain a copyright notice

#ifndef DUAL_PANDA_MOVEIT2_INTERFACE__SRV__DETAIL__DETACH_OBJECT__FUNCTIONS_H_
#define DUAL_PANDA_MOVEIT2_INTERFACE__SRV__DETAIL__DETACH_OBJECT__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "dual_panda_moveit2_interface/msg/rosidl_generator_c__visibility_control.h"

#include "dual_panda_moveit2_interface/srv/detail/detach_object__struct.h"

/// Initialize srv/DetachObject message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * dual_panda_moveit2_interface__srv__DetachObject_Request
 * )) before or use
 * dual_panda_moveit2_interface__srv__DetachObject_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_dual_panda_moveit2_interface
bool
dual_panda_moveit2_interface__srv__DetachObject_Request__init(dual_panda_moveit2_interface__srv__DetachObject_Request * msg);

/// Finalize srv/DetachObject message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_dual_panda_moveit2_interface
void
dual_panda_moveit2_interface__srv__DetachObject_Request__fini(dual_panda_moveit2_interface__srv__DetachObject_Request * msg);

/// Create srv/DetachObject message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * dual_panda_moveit2_interface__srv__DetachObject_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_dual_panda_moveit2_interface
dual_panda_moveit2_interface__srv__DetachObject_Request *
dual_panda_moveit2_interface__srv__DetachObject_Request__create();

/// Destroy srv/DetachObject message.
/**
 * It calls
 * dual_panda_moveit2_interface__srv__DetachObject_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_dual_panda_moveit2_interface
void
dual_panda_moveit2_interface__srv__DetachObject_Request__destroy(dual_panda_moveit2_interface__srv__DetachObject_Request * msg);

/// Check for srv/DetachObject message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_dual_panda_moveit2_interface
bool
dual_panda_moveit2_interface__srv__DetachObject_Request__are_equal(const dual_panda_moveit2_interface__srv__DetachObject_Request * lhs, const dual_panda_moveit2_interface__srv__DetachObject_Request * rhs);

/// Copy a srv/DetachObject message.
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
dual_panda_moveit2_interface__srv__DetachObject_Request__copy(
  const dual_panda_moveit2_interface__srv__DetachObject_Request * input,
  dual_panda_moveit2_interface__srv__DetachObject_Request * output);

/// Initialize array of srv/DetachObject messages.
/**
 * It allocates the memory for the number of elements and calls
 * dual_panda_moveit2_interface__srv__DetachObject_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_dual_panda_moveit2_interface
bool
dual_panda_moveit2_interface__srv__DetachObject_Request__Sequence__init(dual_panda_moveit2_interface__srv__DetachObject_Request__Sequence * array, size_t size);

/// Finalize array of srv/DetachObject messages.
/**
 * It calls
 * dual_panda_moveit2_interface__srv__DetachObject_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_dual_panda_moveit2_interface
void
dual_panda_moveit2_interface__srv__DetachObject_Request__Sequence__fini(dual_panda_moveit2_interface__srv__DetachObject_Request__Sequence * array);

/// Create array of srv/DetachObject messages.
/**
 * It allocates the memory for the array and calls
 * dual_panda_moveit2_interface__srv__DetachObject_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_dual_panda_moveit2_interface
dual_panda_moveit2_interface__srv__DetachObject_Request__Sequence *
dual_panda_moveit2_interface__srv__DetachObject_Request__Sequence__create(size_t size);

/// Destroy array of srv/DetachObject messages.
/**
 * It calls
 * dual_panda_moveit2_interface__srv__DetachObject_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_dual_panda_moveit2_interface
void
dual_panda_moveit2_interface__srv__DetachObject_Request__Sequence__destroy(dual_panda_moveit2_interface__srv__DetachObject_Request__Sequence * array);

/// Check for srv/DetachObject message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_dual_panda_moveit2_interface
bool
dual_panda_moveit2_interface__srv__DetachObject_Request__Sequence__are_equal(const dual_panda_moveit2_interface__srv__DetachObject_Request__Sequence * lhs, const dual_panda_moveit2_interface__srv__DetachObject_Request__Sequence * rhs);

/// Copy an array of srv/DetachObject messages.
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
dual_panda_moveit2_interface__srv__DetachObject_Request__Sequence__copy(
  const dual_panda_moveit2_interface__srv__DetachObject_Request__Sequence * input,
  dual_panda_moveit2_interface__srv__DetachObject_Request__Sequence * output);

/// Initialize srv/DetachObject message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * dual_panda_moveit2_interface__srv__DetachObject_Response
 * )) before or use
 * dual_panda_moveit2_interface__srv__DetachObject_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_dual_panda_moveit2_interface
bool
dual_panda_moveit2_interface__srv__DetachObject_Response__init(dual_panda_moveit2_interface__srv__DetachObject_Response * msg);

/// Finalize srv/DetachObject message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_dual_panda_moveit2_interface
void
dual_panda_moveit2_interface__srv__DetachObject_Response__fini(dual_panda_moveit2_interface__srv__DetachObject_Response * msg);

/// Create srv/DetachObject message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * dual_panda_moveit2_interface__srv__DetachObject_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_dual_panda_moveit2_interface
dual_panda_moveit2_interface__srv__DetachObject_Response *
dual_panda_moveit2_interface__srv__DetachObject_Response__create();

/// Destroy srv/DetachObject message.
/**
 * It calls
 * dual_panda_moveit2_interface__srv__DetachObject_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_dual_panda_moveit2_interface
void
dual_panda_moveit2_interface__srv__DetachObject_Response__destroy(dual_panda_moveit2_interface__srv__DetachObject_Response * msg);

/// Check for srv/DetachObject message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_dual_panda_moveit2_interface
bool
dual_panda_moveit2_interface__srv__DetachObject_Response__are_equal(const dual_panda_moveit2_interface__srv__DetachObject_Response * lhs, const dual_panda_moveit2_interface__srv__DetachObject_Response * rhs);

/// Copy a srv/DetachObject message.
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
dual_panda_moveit2_interface__srv__DetachObject_Response__copy(
  const dual_panda_moveit2_interface__srv__DetachObject_Response * input,
  dual_panda_moveit2_interface__srv__DetachObject_Response * output);

/// Initialize array of srv/DetachObject messages.
/**
 * It allocates the memory for the number of elements and calls
 * dual_panda_moveit2_interface__srv__DetachObject_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_dual_panda_moveit2_interface
bool
dual_panda_moveit2_interface__srv__DetachObject_Response__Sequence__init(dual_panda_moveit2_interface__srv__DetachObject_Response__Sequence * array, size_t size);

/// Finalize array of srv/DetachObject messages.
/**
 * It calls
 * dual_panda_moveit2_interface__srv__DetachObject_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_dual_panda_moveit2_interface
void
dual_panda_moveit2_interface__srv__DetachObject_Response__Sequence__fini(dual_panda_moveit2_interface__srv__DetachObject_Response__Sequence * array);

/// Create array of srv/DetachObject messages.
/**
 * It allocates the memory for the array and calls
 * dual_panda_moveit2_interface__srv__DetachObject_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_dual_panda_moveit2_interface
dual_panda_moveit2_interface__srv__DetachObject_Response__Sequence *
dual_panda_moveit2_interface__srv__DetachObject_Response__Sequence__create(size_t size);

/// Destroy array of srv/DetachObject messages.
/**
 * It calls
 * dual_panda_moveit2_interface__srv__DetachObject_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_dual_panda_moveit2_interface
void
dual_panda_moveit2_interface__srv__DetachObject_Response__Sequence__destroy(dual_panda_moveit2_interface__srv__DetachObject_Response__Sequence * array);

/// Check for srv/DetachObject message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_dual_panda_moveit2_interface
bool
dual_panda_moveit2_interface__srv__DetachObject_Response__Sequence__are_equal(const dual_panda_moveit2_interface__srv__DetachObject_Response__Sequence * lhs, const dual_panda_moveit2_interface__srv__DetachObject_Response__Sequence * rhs);

/// Copy an array of srv/DetachObject messages.
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
dual_panda_moveit2_interface__srv__DetachObject_Response__Sequence__copy(
  const dual_panda_moveit2_interface__srv__DetachObject_Response__Sequence * input,
  dual_panda_moveit2_interface__srv__DetachObject_Response__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // DUAL_PANDA_MOVEIT2_INTERFACE__SRV__DETAIL__DETACH_OBJECT__FUNCTIONS_H_
