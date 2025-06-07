// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from dual_panda_moveit2_interface:srv/GripperControl.idl
// generated code does not contain a copyright notice

#ifndef DUAL_PANDA_MOVEIT2_INTERFACE__SRV__DETAIL__GRIPPER_CONTROL__STRUCT_HPP_
#define DUAL_PANDA_MOVEIT2_INTERFACE__SRV__DETAIL__GRIPPER_CONTROL__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__dual_panda_moveit2_interface__srv__GripperControl_Request __attribute__((deprecated))
#else
# define DEPRECATED__dual_panda_moveit2_interface__srv__GripperControl_Request __declspec(deprecated)
#endif

namespace dual_panda_moveit2_interface
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GripperControl_Request_
{
  using Type = GripperControl_Request_<ContainerAllocator>;

  explicit GripperControl_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->gripper_name = "";
      this->open = false;
    }
  }

  explicit GripperControl_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : gripper_name(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->gripper_name = "";
      this->open = false;
    }
  }

  // field types and members
  using _gripper_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _gripper_name_type gripper_name;
  using _open_type =
    bool;
  _open_type open;

  // setters for named parameter idiom
  Type & set__gripper_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->gripper_name = _arg;
    return *this;
  }
  Type & set__open(
    const bool & _arg)
  {
    this->open = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    dual_panda_moveit2_interface::srv::GripperControl_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const dual_panda_moveit2_interface::srv::GripperControl_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<dual_panda_moveit2_interface::srv::GripperControl_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<dual_panda_moveit2_interface::srv::GripperControl_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      dual_panda_moveit2_interface::srv::GripperControl_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<dual_panda_moveit2_interface::srv::GripperControl_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      dual_panda_moveit2_interface::srv::GripperControl_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<dual_panda_moveit2_interface::srv::GripperControl_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<dual_panda_moveit2_interface::srv::GripperControl_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<dual_panda_moveit2_interface::srv::GripperControl_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__dual_panda_moveit2_interface__srv__GripperControl_Request
    std::shared_ptr<dual_panda_moveit2_interface::srv::GripperControl_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__dual_panda_moveit2_interface__srv__GripperControl_Request
    std::shared_ptr<dual_panda_moveit2_interface::srv::GripperControl_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GripperControl_Request_ & other) const
  {
    if (this->gripper_name != other.gripper_name) {
      return false;
    }
    if (this->open != other.open) {
      return false;
    }
    return true;
  }
  bool operator!=(const GripperControl_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GripperControl_Request_

// alias to use template instance with default allocator
using GripperControl_Request =
  dual_panda_moveit2_interface::srv::GripperControl_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace dual_panda_moveit2_interface


#ifndef _WIN32
# define DEPRECATED__dual_panda_moveit2_interface__srv__GripperControl_Response __attribute__((deprecated))
#else
# define DEPRECATED__dual_panda_moveit2_interface__srv__GripperControl_Response __declspec(deprecated)
#endif

namespace dual_panda_moveit2_interface
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GripperControl_Response_
{
  using Type = GripperControl_Response_<ContainerAllocator>;

  explicit GripperControl_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
    }
  }

  explicit GripperControl_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    dual_panda_moveit2_interface::srv::GripperControl_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const dual_panda_moveit2_interface::srv::GripperControl_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<dual_panda_moveit2_interface::srv::GripperControl_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<dual_panda_moveit2_interface::srv::GripperControl_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      dual_panda_moveit2_interface::srv::GripperControl_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<dual_panda_moveit2_interface::srv::GripperControl_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      dual_panda_moveit2_interface::srv::GripperControl_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<dual_panda_moveit2_interface::srv::GripperControl_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<dual_panda_moveit2_interface::srv::GripperControl_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<dual_panda_moveit2_interface::srv::GripperControl_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__dual_panda_moveit2_interface__srv__GripperControl_Response
    std::shared_ptr<dual_panda_moveit2_interface::srv::GripperControl_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__dual_panda_moveit2_interface__srv__GripperControl_Response
    std::shared_ptr<dual_panda_moveit2_interface::srv::GripperControl_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GripperControl_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    return true;
  }
  bool operator!=(const GripperControl_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GripperControl_Response_

// alias to use template instance with default allocator
using GripperControl_Response =
  dual_panda_moveit2_interface::srv::GripperControl_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace dual_panda_moveit2_interface

namespace dual_panda_moveit2_interface
{

namespace srv
{

struct GripperControl
{
  using Request = dual_panda_moveit2_interface::srv::GripperControl_Request;
  using Response = dual_panda_moveit2_interface::srv::GripperControl_Response;
};

}  // namespace srv

}  // namespace dual_panda_moveit2_interface

#endif  // DUAL_PANDA_MOVEIT2_INTERFACE__SRV__DETAIL__GRIPPER_CONTROL__STRUCT_HPP_
