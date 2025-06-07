// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from reachy_moveit2:msg/AddObstacle.idl
// generated code does not contain a copyright notice

#ifndef REACHY_MOVEIT2__MSG__DETAIL__ADD_OBSTACLE__STRUCT_HPP_
#define REACHY_MOVEIT2__MSG__DETAIL__ADD_OBSTACLE__STRUCT_HPP_

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
// Member 'primitive'
#include "shape_msgs/msg/detail/solid_primitive__struct.hpp"
// Member 'pose'
#include "geometry_msgs/msg/detail/pose_stamped__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__reachy_moveit2__msg__AddObstacle __attribute__((deprecated))
#else
# define DEPRECATED__reachy_moveit2__msg__AddObstacle __declspec(deprecated)
#endif

namespace reachy_moveit2
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct AddObstacle_
{
  using Type = AddObstacle_<ContainerAllocator>;

  explicit AddObstacle_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    primitive(_init),
    pose(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = "";
      this->operation = "";
    }
  }

  explicit AddObstacle_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    id(_alloc),
    operation(_alloc),
    primitive(_alloc, _init),
    pose(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = "";
      this->operation = "";
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _id_type id;
  using _operation_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _operation_type operation;
  using _primitive_type =
    shape_msgs::msg::SolidPrimitive_<ContainerAllocator>;
  _primitive_type primitive;
  using _pose_type =
    geometry_msgs::msg::PoseStamped_<ContainerAllocator>;
  _pose_type pose;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->id = _arg;
    return *this;
  }
  Type & set__operation(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->operation = _arg;
    return *this;
  }
  Type & set__primitive(
    const shape_msgs::msg::SolidPrimitive_<ContainerAllocator> & _arg)
  {
    this->primitive = _arg;
    return *this;
  }
  Type & set__pose(
    const geometry_msgs::msg::PoseStamped_<ContainerAllocator> & _arg)
  {
    this->pose = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    reachy_moveit2::msg::AddObstacle_<ContainerAllocator> *;
  using ConstRawPtr =
    const reachy_moveit2::msg::AddObstacle_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<reachy_moveit2::msg::AddObstacle_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<reachy_moveit2::msg::AddObstacle_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      reachy_moveit2::msg::AddObstacle_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<reachy_moveit2::msg::AddObstacle_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      reachy_moveit2::msg::AddObstacle_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<reachy_moveit2::msg::AddObstacle_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<reachy_moveit2::msg::AddObstacle_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<reachy_moveit2::msg::AddObstacle_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__reachy_moveit2__msg__AddObstacle
    std::shared_ptr<reachy_moveit2::msg::AddObstacle_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__reachy_moveit2__msg__AddObstacle
    std::shared_ptr<reachy_moveit2::msg::AddObstacle_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const AddObstacle_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->id != other.id) {
      return false;
    }
    if (this->operation != other.operation) {
      return false;
    }
    if (this->primitive != other.primitive) {
      return false;
    }
    if (this->pose != other.pose) {
      return false;
    }
    return true;
  }
  bool operator!=(const AddObstacle_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct AddObstacle_

// alias to use template instance with default allocator
using AddObstacle =
  reachy_moveit2::msg::AddObstacle_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace reachy_moveit2

#endif  // REACHY_MOVEIT2__MSG__DETAIL__ADD_OBSTACLE__STRUCT_HPP_
