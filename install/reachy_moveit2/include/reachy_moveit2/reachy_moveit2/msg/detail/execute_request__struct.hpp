// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from reachy_moveit2:msg/ExecuteRequest.idl
// generated code does not contain a copyright notice

#ifndef REACHY_MOVEIT2__MSG__DETAIL__EXECUTE_REQUEST__STRUCT_HPP_
#define REACHY_MOVEIT2__MSG__DETAIL__EXECUTE_REQUEST__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__reachy_moveit2__msg__ExecuteRequest __attribute__((deprecated))
#else
# define DEPRECATED__reachy_moveit2__msg__ExecuteRequest __declspec(deprecated)
#endif

namespace reachy_moveit2
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ExecuteRequest_
{
  using Type = ExecuteRequest_<ContainerAllocator>;

  explicit ExecuteRequest_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->command = "";
    }
  }

  explicit ExecuteRequest_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    command(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->command = "";
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _command_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _command_type command;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__command(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->command = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    reachy_moveit2::msg::ExecuteRequest_<ContainerAllocator> *;
  using ConstRawPtr =
    const reachy_moveit2::msg::ExecuteRequest_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<reachy_moveit2::msg::ExecuteRequest_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<reachy_moveit2::msg::ExecuteRequest_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      reachy_moveit2::msg::ExecuteRequest_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<reachy_moveit2::msg::ExecuteRequest_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      reachy_moveit2::msg::ExecuteRequest_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<reachy_moveit2::msg::ExecuteRequest_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<reachy_moveit2::msg::ExecuteRequest_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<reachy_moveit2::msg::ExecuteRequest_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__reachy_moveit2__msg__ExecuteRequest
    std::shared_ptr<reachy_moveit2::msg::ExecuteRequest_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__reachy_moveit2__msg__ExecuteRequest
    std::shared_ptr<reachy_moveit2::msg::ExecuteRequest_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ExecuteRequest_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->command != other.command) {
      return false;
    }
    return true;
  }
  bool operator!=(const ExecuteRequest_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ExecuteRequest_

// alias to use template instance with default allocator
using ExecuteRequest =
  reachy_moveit2::msg::ExecuteRequest_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace reachy_moveit2

#endif  // REACHY_MOVEIT2__MSG__DETAIL__EXECUTE_REQUEST__STRUCT_HPP_
