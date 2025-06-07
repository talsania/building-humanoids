// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from reachy_moveit2:msg/AddObstacle.idl
// generated code does not contain a copyright notice

#ifndef REACHY_MOVEIT2__MSG__DETAIL__ADD_OBSTACLE__BUILDER_HPP_
#define REACHY_MOVEIT2__MSG__DETAIL__ADD_OBSTACLE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "reachy_moveit2/msg/detail/add_obstacle__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace reachy_moveit2
{

namespace msg
{

namespace builder
{

class Init_AddObstacle_pose
{
public:
  explicit Init_AddObstacle_pose(::reachy_moveit2::msg::AddObstacle & msg)
  : msg_(msg)
  {}
  ::reachy_moveit2::msg::AddObstacle pose(::reachy_moveit2::msg::AddObstacle::_pose_type arg)
  {
    msg_.pose = std::move(arg);
    return std::move(msg_);
  }

private:
  ::reachy_moveit2::msg::AddObstacle msg_;
};

class Init_AddObstacle_primitive
{
public:
  explicit Init_AddObstacle_primitive(::reachy_moveit2::msg::AddObstacle & msg)
  : msg_(msg)
  {}
  Init_AddObstacle_pose primitive(::reachy_moveit2::msg::AddObstacle::_primitive_type arg)
  {
    msg_.primitive = std::move(arg);
    return Init_AddObstacle_pose(msg_);
  }

private:
  ::reachy_moveit2::msg::AddObstacle msg_;
};

class Init_AddObstacle_operation
{
public:
  explicit Init_AddObstacle_operation(::reachy_moveit2::msg::AddObstacle & msg)
  : msg_(msg)
  {}
  Init_AddObstacle_primitive operation(::reachy_moveit2::msg::AddObstacle::_operation_type arg)
  {
    msg_.operation = std::move(arg);
    return Init_AddObstacle_primitive(msg_);
  }

private:
  ::reachy_moveit2::msg::AddObstacle msg_;
};

class Init_AddObstacle_id
{
public:
  explicit Init_AddObstacle_id(::reachy_moveit2::msg::AddObstacle & msg)
  : msg_(msg)
  {}
  Init_AddObstacle_operation id(::reachy_moveit2::msg::AddObstacle::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_AddObstacle_operation(msg_);
  }

private:
  ::reachy_moveit2::msg::AddObstacle msg_;
};

class Init_AddObstacle_header
{
public:
  Init_AddObstacle_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_AddObstacle_id header(::reachy_moveit2::msg::AddObstacle::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_AddObstacle_id(msg_);
  }

private:
  ::reachy_moveit2::msg::AddObstacle msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::reachy_moveit2::msg::AddObstacle>()
{
  return reachy_moveit2::msg::builder::Init_AddObstacle_header();
}

}  // namespace reachy_moveit2

#endif  // REACHY_MOVEIT2__MSG__DETAIL__ADD_OBSTACLE__BUILDER_HPP_
