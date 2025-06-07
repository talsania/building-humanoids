// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from dual_panda_moveit2_interface:srv/DetachObject.idl
// generated code does not contain a copyright notice

#ifndef DUAL_PANDA_MOVEIT2_INTERFACE__SRV__DETAIL__DETACH_OBJECT__STRUCT_HPP_
#define DUAL_PANDA_MOVEIT2_INTERFACE__SRV__DETAIL__DETACH_OBJECT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__dual_panda_moveit2_interface__srv__DetachObject_Request __attribute__((deprecated))
#else
# define DEPRECATED__dual_panda_moveit2_interface__srv__DetachObject_Request __declspec(deprecated)
#endif

namespace dual_panda_moveit2_interface
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct DetachObject_Request_
{
  using Type = DetachObject_Request_<ContainerAllocator>;

  explicit DetachObject_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = "";
    }
  }

  explicit DetachObject_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : id(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = "";
    }
  }

  // field types and members
  using _id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _id_type id;

  // setters for named parameter idiom
  Type & set__id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->id = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    dual_panda_moveit2_interface::srv::DetachObject_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const dual_panda_moveit2_interface::srv::DetachObject_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<dual_panda_moveit2_interface::srv::DetachObject_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<dual_panda_moveit2_interface::srv::DetachObject_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      dual_panda_moveit2_interface::srv::DetachObject_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<dual_panda_moveit2_interface::srv::DetachObject_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      dual_panda_moveit2_interface::srv::DetachObject_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<dual_panda_moveit2_interface::srv::DetachObject_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<dual_panda_moveit2_interface::srv::DetachObject_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<dual_panda_moveit2_interface::srv::DetachObject_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__dual_panda_moveit2_interface__srv__DetachObject_Request
    std::shared_ptr<dual_panda_moveit2_interface::srv::DetachObject_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__dual_panda_moveit2_interface__srv__DetachObject_Request
    std::shared_ptr<dual_panda_moveit2_interface::srv::DetachObject_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DetachObject_Request_ & other) const
  {
    if (this->id != other.id) {
      return false;
    }
    return true;
  }
  bool operator!=(const DetachObject_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DetachObject_Request_

// alias to use template instance with default allocator
using DetachObject_Request =
  dual_panda_moveit2_interface::srv::DetachObject_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace dual_panda_moveit2_interface


#ifndef _WIN32
# define DEPRECATED__dual_panda_moveit2_interface__srv__DetachObject_Response __attribute__((deprecated))
#else
# define DEPRECATED__dual_panda_moveit2_interface__srv__DetachObject_Response __declspec(deprecated)
#endif

namespace dual_panda_moveit2_interface
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct DetachObject_Response_
{
  using Type = DetachObject_Response_<ContainerAllocator>;

  explicit DetachObject_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
    }
  }

  explicit DetachObject_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    dual_panda_moveit2_interface::srv::DetachObject_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const dual_panda_moveit2_interface::srv::DetachObject_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<dual_panda_moveit2_interface::srv::DetachObject_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<dual_panda_moveit2_interface::srv::DetachObject_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      dual_panda_moveit2_interface::srv::DetachObject_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<dual_panda_moveit2_interface::srv::DetachObject_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      dual_panda_moveit2_interface::srv::DetachObject_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<dual_panda_moveit2_interface::srv::DetachObject_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<dual_panda_moveit2_interface::srv::DetachObject_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<dual_panda_moveit2_interface::srv::DetachObject_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__dual_panda_moveit2_interface__srv__DetachObject_Response
    std::shared_ptr<dual_panda_moveit2_interface::srv::DetachObject_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__dual_panda_moveit2_interface__srv__DetachObject_Response
    std::shared_ptr<dual_panda_moveit2_interface::srv::DetachObject_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DetachObject_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    return true;
  }
  bool operator!=(const DetachObject_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DetachObject_Response_

// alias to use template instance with default allocator
using DetachObject_Response =
  dual_panda_moveit2_interface::srv::DetachObject_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace dual_panda_moveit2_interface

namespace dual_panda_moveit2_interface
{

namespace srv
{

struct DetachObject
{
  using Request = dual_panda_moveit2_interface::srv::DetachObject_Request;
  using Response = dual_panda_moveit2_interface::srv::DetachObject_Response;
};

}  // namespace srv

}  // namespace dual_panda_moveit2_interface

#endif  // DUAL_PANDA_MOVEIT2_INTERFACE__SRV__DETAIL__DETACH_OBJECT__STRUCT_HPP_
