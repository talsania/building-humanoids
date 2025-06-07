// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from dual_panda_moveit2_interface:srv/GripperControl.idl
// generated code does not contain a copyright notice

#ifndef DUAL_PANDA_MOVEIT2_INTERFACE__SRV__DETAIL__GRIPPER_CONTROL__BUILDER_HPP_
#define DUAL_PANDA_MOVEIT2_INTERFACE__SRV__DETAIL__GRIPPER_CONTROL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "dual_panda_moveit2_interface/srv/detail/gripper_control__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace dual_panda_moveit2_interface
{

namespace srv
{

namespace builder
{

class Init_GripperControl_Request_open
{
public:
  explicit Init_GripperControl_Request_open(::dual_panda_moveit2_interface::srv::GripperControl_Request & msg)
  : msg_(msg)
  {}
  ::dual_panda_moveit2_interface::srv::GripperControl_Request open(::dual_panda_moveit2_interface::srv::GripperControl_Request::_open_type arg)
  {
    msg_.open = std::move(arg);
    return std::move(msg_);
  }

private:
  ::dual_panda_moveit2_interface::srv::GripperControl_Request msg_;
};

class Init_GripperControl_Request_gripper_name
{
public:
  Init_GripperControl_Request_gripper_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GripperControl_Request_open gripper_name(::dual_panda_moveit2_interface::srv::GripperControl_Request::_gripper_name_type arg)
  {
    msg_.gripper_name = std::move(arg);
    return Init_GripperControl_Request_open(msg_);
  }

private:
  ::dual_panda_moveit2_interface::srv::GripperControl_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::dual_panda_moveit2_interface::srv::GripperControl_Request>()
{
  return dual_panda_moveit2_interface::srv::builder::Init_GripperControl_Request_gripper_name();
}

}  // namespace dual_panda_moveit2_interface


namespace dual_panda_moveit2_interface
{

namespace srv
{

namespace builder
{

class Init_GripperControl_Response_success
{
public:
  Init_GripperControl_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::dual_panda_moveit2_interface::srv::GripperControl_Response success(::dual_panda_moveit2_interface::srv::GripperControl_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return std::move(msg_);
  }

private:
  ::dual_panda_moveit2_interface::srv::GripperControl_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::dual_panda_moveit2_interface::srv::GripperControl_Response>()
{
  return dual_panda_moveit2_interface::srv::builder::Init_GripperControl_Response_success();
}

}  // namespace dual_panda_moveit2_interface

#endif  // DUAL_PANDA_MOVEIT2_INTERFACE__SRV__DETAIL__GRIPPER_CONTROL__BUILDER_HPP_
