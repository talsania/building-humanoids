// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from dual_panda_moveit2_interface:msg/SpawnBatch.idl
// generated code does not contain a copyright notice

#ifndef DUAL_PANDA_MOVEIT2_INTERFACE__MSG__DETAIL__SPAWN_BATCH__STRUCT_HPP_
#define DUAL_PANDA_MOVEIT2_INTERFACE__MSG__DETAIL__SPAWN_BATCH__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'objects'
#include "dual_panda_moveit2_interface/msg/detail/object_spec__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__dual_panda_moveit2_interface__msg__SpawnBatch __attribute__((deprecated))
#else
# define DEPRECATED__dual_panda_moveit2_interface__msg__SpawnBatch __declspec(deprecated)
#endif

namespace dual_panda_moveit2_interface
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SpawnBatch_
{
  using Type = SpawnBatch_<ContainerAllocator>;

  explicit SpawnBatch_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit SpawnBatch_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _objects_type =
    std::vector<dual_panda_moveit2_interface::msg::ObjectSpec_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<dual_panda_moveit2_interface::msg::ObjectSpec_<ContainerAllocator>>>;
  _objects_type objects;

  // setters for named parameter idiom
  Type & set__objects(
    const std::vector<dual_panda_moveit2_interface::msg::ObjectSpec_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<dual_panda_moveit2_interface::msg::ObjectSpec_<ContainerAllocator>>> & _arg)
  {
    this->objects = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    dual_panda_moveit2_interface::msg::SpawnBatch_<ContainerAllocator> *;
  using ConstRawPtr =
    const dual_panda_moveit2_interface::msg::SpawnBatch_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<dual_panda_moveit2_interface::msg::SpawnBatch_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<dual_panda_moveit2_interface::msg::SpawnBatch_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      dual_panda_moveit2_interface::msg::SpawnBatch_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<dual_panda_moveit2_interface::msg::SpawnBatch_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      dual_panda_moveit2_interface::msg::SpawnBatch_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<dual_panda_moveit2_interface::msg::SpawnBatch_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<dual_panda_moveit2_interface::msg::SpawnBatch_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<dual_panda_moveit2_interface::msg::SpawnBatch_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__dual_panda_moveit2_interface__msg__SpawnBatch
    std::shared_ptr<dual_panda_moveit2_interface::msg::SpawnBatch_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__dual_panda_moveit2_interface__msg__SpawnBatch
    std::shared_ptr<dual_panda_moveit2_interface::msg::SpawnBatch_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SpawnBatch_ & other) const
  {
    if (this->objects != other.objects) {
      return false;
    }
    return true;
  }
  bool operator!=(const SpawnBatch_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SpawnBatch_

// alias to use template instance with default allocator
using SpawnBatch =
  dual_panda_moveit2_interface::msg::SpawnBatch_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace dual_panda_moveit2_interface

#endif  // DUAL_PANDA_MOVEIT2_INTERFACE__MSG__DETAIL__SPAWN_BATCH__STRUCT_HPP_
