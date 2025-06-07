// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from dual_panda_moveit2_interface:srv/SpawnObject.idl
// generated code does not contain a copyright notice

#ifndef DUAL_PANDA_MOVEIT2_INTERFACE__SRV__DETAIL__SPAWN_OBJECT__STRUCT_HPP_
#define DUAL_PANDA_MOVEIT2_INTERFACE__SRV__DETAIL__SPAWN_OBJECT__STRUCT_HPP_

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
# define DEPRECATED__dual_panda_moveit2_interface__srv__SpawnObject_Request __attribute__((deprecated))
#else
# define DEPRECATED__dual_panda_moveit2_interface__srv__SpawnObject_Request __declspec(deprecated)
#endif

namespace dual_panda_moveit2_interface
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SpawnObject_Request_
{
  using Type = SpawnObject_Request_<ContainerAllocator>;

  explicit SpawnObject_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit SpawnObject_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    dual_panda_moveit2_interface::srv::SpawnObject_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const dual_panda_moveit2_interface::srv::SpawnObject_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<dual_panda_moveit2_interface::srv::SpawnObject_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<dual_panda_moveit2_interface::srv::SpawnObject_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      dual_panda_moveit2_interface::srv::SpawnObject_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<dual_panda_moveit2_interface::srv::SpawnObject_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      dual_panda_moveit2_interface::srv::SpawnObject_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<dual_panda_moveit2_interface::srv::SpawnObject_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<dual_panda_moveit2_interface::srv::SpawnObject_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<dual_panda_moveit2_interface::srv::SpawnObject_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__dual_panda_moveit2_interface__srv__SpawnObject_Request
    std::shared_ptr<dual_panda_moveit2_interface::srv::SpawnObject_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__dual_panda_moveit2_interface__srv__SpawnObject_Request
    std::shared_ptr<dual_panda_moveit2_interface::srv::SpawnObject_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SpawnObject_Request_ & other) const
  {
    if (this->objects != other.objects) {
      return false;
    }
    return true;
  }
  bool operator!=(const SpawnObject_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SpawnObject_Request_

// alias to use template instance with default allocator
using SpawnObject_Request =
  dual_panda_moveit2_interface::srv::SpawnObject_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace dual_panda_moveit2_interface


// Include directives for member types
// Member 'current_objects'
// already included above
// #include "dual_panda_moveit2_interface/msg/detail/object_spec__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__dual_panda_moveit2_interface__srv__SpawnObject_Response __attribute__((deprecated))
#else
# define DEPRECATED__dual_panda_moveit2_interface__srv__SpawnObject_Response __declspec(deprecated)
#endif

namespace dual_panda_moveit2_interface
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SpawnObject_Response_
{
  using Type = SpawnObject_Response_<ContainerAllocator>;

  explicit SpawnObject_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
    }
  }

  explicit SpawnObject_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _current_objects_type =
    std::vector<dual_panda_moveit2_interface::msg::ObjectSpec_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<dual_panda_moveit2_interface::msg::ObjectSpec_<ContainerAllocator>>>;
  _current_objects_type current_objects;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__current_objects(
    const std::vector<dual_panda_moveit2_interface::msg::ObjectSpec_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<dual_panda_moveit2_interface::msg::ObjectSpec_<ContainerAllocator>>> & _arg)
  {
    this->current_objects = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    dual_panda_moveit2_interface::srv::SpawnObject_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const dual_panda_moveit2_interface::srv::SpawnObject_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<dual_panda_moveit2_interface::srv::SpawnObject_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<dual_panda_moveit2_interface::srv::SpawnObject_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      dual_panda_moveit2_interface::srv::SpawnObject_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<dual_panda_moveit2_interface::srv::SpawnObject_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      dual_panda_moveit2_interface::srv::SpawnObject_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<dual_panda_moveit2_interface::srv::SpawnObject_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<dual_panda_moveit2_interface::srv::SpawnObject_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<dual_panda_moveit2_interface::srv::SpawnObject_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__dual_panda_moveit2_interface__srv__SpawnObject_Response
    std::shared_ptr<dual_panda_moveit2_interface::srv::SpawnObject_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__dual_panda_moveit2_interface__srv__SpawnObject_Response
    std::shared_ptr<dual_panda_moveit2_interface::srv::SpawnObject_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SpawnObject_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->current_objects != other.current_objects) {
      return false;
    }
    return true;
  }
  bool operator!=(const SpawnObject_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SpawnObject_Response_

// alias to use template instance with default allocator
using SpawnObject_Response =
  dual_panda_moveit2_interface::srv::SpawnObject_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace dual_panda_moveit2_interface

namespace dual_panda_moveit2_interface
{

namespace srv
{

struct SpawnObject
{
  using Request = dual_panda_moveit2_interface::srv::SpawnObject_Request;
  using Response = dual_panda_moveit2_interface::srv::SpawnObject_Response;
};

}  // namespace srv

}  // namespace dual_panda_moveit2_interface

#endif  // DUAL_PANDA_MOVEIT2_INTERFACE__SRV__DETAIL__SPAWN_OBJECT__STRUCT_HPP_
