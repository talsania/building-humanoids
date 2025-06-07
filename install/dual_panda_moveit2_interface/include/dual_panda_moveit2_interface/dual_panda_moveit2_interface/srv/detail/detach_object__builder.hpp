// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from dual_panda_moveit2_interface:srv/DetachObject.idl
// generated code does not contain a copyright notice

#ifndef DUAL_PANDA_MOVEIT2_INTERFACE__SRV__DETAIL__DETACH_OBJECT__BUILDER_HPP_
#define DUAL_PANDA_MOVEIT2_INTERFACE__SRV__DETAIL__DETACH_OBJECT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "dual_panda_moveit2_interface/srv/detail/detach_object__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace dual_panda_moveit2_interface
{

namespace srv
{

namespace builder
{

class Init_DetachObject_Request_id
{
public:
  Init_DetachObject_Request_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::dual_panda_moveit2_interface::srv::DetachObject_Request id(::dual_panda_moveit2_interface::srv::DetachObject_Request::_id_type arg)
  {
    msg_.id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::dual_panda_moveit2_interface::srv::DetachObject_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::dual_panda_moveit2_interface::srv::DetachObject_Request>()
{
  return dual_panda_moveit2_interface::srv::builder::Init_DetachObject_Request_id();
}

}  // namespace dual_panda_moveit2_interface


namespace dual_panda_moveit2_interface
{

namespace srv
{

namespace builder
{

class Init_DetachObject_Response_success
{
public:
  Init_DetachObject_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::dual_panda_moveit2_interface::srv::DetachObject_Response success(::dual_panda_moveit2_interface::srv::DetachObject_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return std::move(msg_);
  }

private:
  ::dual_panda_moveit2_interface::srv::DetachObject_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::dual_panda_moveit2_interface::srv::DetachObject_Response>()
{
  return dual_panda_moveit2_interface::srv::builder::Init_DetachObject_Response_success();
}

}  // namespace dual_panda_moveit2_interface

#endif  // DUAL_PANDA_MOVEIT2_INTERFACE__SRV__DETAIL__DETACH_OBJECT__BUILDER_HPP_
