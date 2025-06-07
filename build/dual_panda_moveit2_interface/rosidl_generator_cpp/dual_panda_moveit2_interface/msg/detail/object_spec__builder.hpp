// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from dual_panda_moveit2_interface:msg/ObjectSpec.idl
// generated code does not contain a copyright notice

#ifndef DUAL_PANDA_MOVEIT2_INTERFACE__MSG__DETAIL__OBJECT_SPEC__BUILDER_HPP_
#define DUAL_PANDA_MOVEIT2_INTERFACE__MSG__DETAIL__OBJECT_SPEC__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "dual_panda_moveit2_interface/msg/detail/object_spec__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace dual_panda_moveit2_interface
{

namespace msg
{

namespace builder
{

class Init_ObjectSpec_pose
{
public:
  explicit Init_ObjectSpec_pose(::dual_panda_moveit2_interface::msg::ObjectSpec & msg)
  : msg_(msg)
  {}
  ::dual_panda_moveit2_interface::msg::ObjectSpec pose(::dual_panda_moveit2_interface::msg::ObjectSpec::_pose_type arg)
  {
    msg_.pose = std::move(arg);
    return std::move(msg_);
  }

private:
  ::dual_panda_moveit2_interface::msg::ObjectSpec msg_;
};

class Init_ObjectSpec_dimensions
{
public:
  explicit Init_ObjectSpec_dimensions(::dual_panda_moveit2_interface::msg::ObjectSpec & msg)
  : msg_(msg)
  {}
  Init_ObjectSpec_pose dimensions(::dual_panda_moveit2_interface::msg::ObjectSpec::_dimensions_type arg)
  {
    msg_.dimensions = std::move(arg);
    return Init_ObjectSpec_pose(msg_);
  }

private:
  ::dual_panda_moveit2_interface::msg::ObjectSpec msg_;
};

class Init_ObjectSpec_type
{
public:
  explicit Init_ObjectSpec_type(::dual_panda_moveit2_interface::msg::ObjectSpec & msg)
  : msg_(msg)
  {}
  Init_ObjectSpec_dimensions type(::dual_panda_moveit2_interface::msg::ObjectSpec::_type_type arg)
  {
    msg_.type = std::move(arg);
    return Init_ObjectSpec_dimensions(msg_);
  }

private:
  ::dual_panda_moveit2_interface::msg::ObjectSpec msg_;
};

class Init_ObjectSpec_id
{
public:
  Init_ObjectSpec_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ObjectSpec_type id(::dual_panda_moveit2_interface::msg::ObjectSpec::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_ObjectSpec_type(msg_);
  }

private:
  ::dual_panda_moveit2_interface::msg::ObjectSpec msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::dual_panda_moveit2_interface::msg::ObjectSpec>()
{
  return dual_panda_moveit2_interface::msg::builder::Init_ObjectSpec_id();
}

}  // namespace dual_panda_moveit2_interface

#endif  // DUAL_PANDA_MOVEIT2_INTERFACE__MSG__DETAIL__OBJECT_SPEC__BUILDER_HPP_
