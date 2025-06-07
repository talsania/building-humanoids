// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from dual_panda_moveit2_interface:msg/RobotPose.idl
// generated code does not contain a copyright notice

#ifndef DUAL_PANDA_MOVEIT2_INTERFACE__MSG__DETAIL__ROBOT_POSE__STRUCT_HPP_
#define DUAL_PANDA_MOVEIT2_INTERFACE__MSG__DETAIL__ROBOT_POSE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'head'
// Member 'left_pose'
// Member 'right_pose'
#include "geometry_msgs/msg/detail/pose_stamped__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__dual_panda_moveit2_interface__msg__RobotPose __attribute__((deprecated))
#else
# define DEPRECATED__dual_panda_moveit2_interface__msg__RobotPose __declspec(deprecated)
#endif

namespace dual_panda_moveit2_interface
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct RobotPose_
{
  using Type = RobotPose_<ContainerAllocator>;

  explicit RobotPose_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : head(_init),
    left_pose(_init),
    right_pose(_init)
  {
    (void)_init;
  }

  explicit RobotPose_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : head(_alloc, _init),
    left_pose(_alloc, _init),
    right_pose(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _head_type =
    geometry_msgs::msg::PoseStamped_<ContainerAllocator>;
  _head_type head;
  using _left_pose_type =
    geometry_msgs::msg::PoseStamped_<ContainerAllocator>;
  _left_pose_type left_pose;
  using _right_pose_type =
    geometry_msgs::msg::PoseStamped_<ContainerAllocator>;
  _right_pose_type right_pose;

  // setters for named parameter idiom
  Type & set__head(
    const geometry_msgs::msg::PoseStamped_<ContainerAllocator> & _arg)
  {
    this->head = _arg;
    return *this;
  }
  Type & set__left_pose(
    const geometry_msgs::msg::PoseStamped_<ContainerAllocator> & _arg)
  {
    this->left_pose = _arg;
    return *this;
  }
  Type & set__right_pose(
    const geometry_msgs::msg::PoseStamped_<ContainerAllocator> & _arg)
  {
    this->right_pose = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    dual_panda_moveit2_interface::msg::RobotPose_<ContainerAllocator> *;
  using ConstRawPtr =
    const dual_panda_moveit2_interface::msg::RobotPose_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<dual_panda_moveit2_interface::msg::RobotPose_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<dual_panda_moveit2_interface::msg::RobotPose_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      dual_panda_moveit2_interface::msg::RobotPose_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<dual_panda_moveit2_interface::msg::RobotPose_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      dual_panda_moveit2_interface::msg::RobotPose_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<dual_panda_moveit2_interface::msg::RobotPose_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<dual_panda_moveit2_interface::msg::RobotPose_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<dual_panda_moveit2_interface::msg::RobotPose_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__dual_panda_moveit2_interface__msg__RobotPose
    std::shared_ptr<dual_panda_moveit2_interface::msg::RobotPose_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__dual_panda_moveit2_interface__msg__RobotPose
    std::shared_ptr<dual_panda_moveit2_interface::msg::RobotPose_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RobotPose_ & other) const
  {
    if (this->head != other.head) {
      return false;
    }
    if (this->left_pose != other.left_pose) {
      return false;
    }
    if (this->right_pose != other.right_pose) {
      return false;
    }
    return true;
  }
  bool operator!=(const RobotPose_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RobotPose_

// alias to use template instance with default allocator
using RobotPose =
  dual_panda_moveit2_interface::msg::RobotPose_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace dual_panda_moveit2_interface

#endif  // DUAL_PANDA_MOVEIT2_INTERFACE__MSG__DETAIL__ROBOT_POSE__STRUCT_HPP_
