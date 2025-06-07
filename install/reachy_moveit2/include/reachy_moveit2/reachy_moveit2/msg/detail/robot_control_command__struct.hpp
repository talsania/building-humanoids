// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from reachy_moveit2:msg/RobotControlCommand.idl
// generated code does not contain a copyright notice

#ifndef REACHY_MOVEIT2__MSG__DETAIL__ROBOT_CONTROL_COMMAND__STRUCT_HPP_
#define REACHY_MOVEIT2__MSG__DETAIL__ROBOT_CONTROL_COMMAND__STRUCT_HPP_

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
// Member 'joint_state'
#include "sensor_msgs/msg/detail/joint_state__struct.hpp"
// Member 'cartesian_target'
#include "geometry_msgs/msg/detail/pose_stamped__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__reachy_moveit2__msg__RobotControlCommand __attribute__((deprecated))
#else
# define DEPRECATED__reachy_moveit2__msg__RobotControlCommand __declspec(deprecated)
#endif

namespace reachy_moveit2
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct RobotControlCommand_
{
  using Type = RobotControlCommand_<ContainerAllocator>;

  explicit RobotControlCommand_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    joint_state(_init),
    cartesian_target(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mode = "";
    }
  }

  explicit RobotControlCommand_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    mode(_alloc),
    joint_state(_alloc, _init),
    cartesian_target(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mode = "";
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _mode_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _mode_type mode;
  using _joint_state_type =
    sensor_msgs::msg::JointState_<ContainerAllocator>;
  _joint_state_type joint_state;
  using _cartesian_target_type =
    geometry_msgs::msg::PoseStamped_<ContainerAllocator>;
  _cartesian_target_type cartesian_target;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__mode(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->mode = _arg;
    return *this;
  }
  Type & set__joint_state(
    const sensor_msgs::msg::JointState_<ContainerAllocator> & _arg)
  {
    this->joint_state = _arg;
    return *this;
  }
  Type & set__cartesian_target(
    const geometry_msgs::msg::PoseStamped_<ContainerAllocator> & _arg)
  {
    this->cartesian_target = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    reachy_moveit2::msg::RobotControlCommand_<ContainerAllocator> *;
  using ConstRawPtr =
    const reachy_moveit2::msg::RobotControlCommand_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<reachy_moveit2::msg::RobotControlCommand_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<reachy_moveit2::msg::RobotControlCommand_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      reachy_moveit2::msg::RobotControlCommand_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<reachy_moveit2::msg::RobotControlCommand_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      reachy_moveit2::msg::RobotControlCommand_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<reachy_moveit2::msg::RobotControlCommand_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<reachy_moveit2::msg::RobotControlCommand_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<reachy_moveit2::msg::RobotControlCommand_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__reachy_moveit2__msg__RobotControlCommand
    std::shared_ptr<reachy_moveit2::msg::RobotControlCommand_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__reachy_moveit2__msg__RobotControlCommand
    std::shared_ptr<reachy_moveit2::msg::RobotControlCommand_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RobotControlCommand_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->mode != other.mode) {
      return false;
    }
    if (this->joint_state != other.joint_state) {
      return false;
    }
    if (this->cartesian_target != other.cartesian_target) {
      return false;
    }
    return true;
  }
  bool operator!=(const RobotControlCommand_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RobotControlCommand_

// alias to use template instance with default allocator
using RobotControlCommand =
  reachy_moveit2::msg::RobotControlCommand_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace reachy_moveit2

#endif  // REACHY_MOVEIT2__MSG__DETAIL__ROBOT_CONTROL_COMMAND__STRUCT_HPP_
