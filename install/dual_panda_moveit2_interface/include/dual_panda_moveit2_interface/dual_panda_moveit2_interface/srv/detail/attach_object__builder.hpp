// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from dual_panda_moveit2_interface:srv/AttachObject.idl
// generated code does not contain a copyright notice

#ifndef DUAL_PANDA_MOVEIT2_INTERFACE__SRV__DETAIL__ATTACH_OBJECT__BUILDER_HPP_
#define DUAL_PANDA_MOVEIT2_INTERFACE__SRV__DETAIL__ATTACH_OBJECT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "dual_panda_moveit2_interface/srv/detail/attach_object__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace dual_panda_moveit2_interface
{

namespace srv
{

namespace builder
{

class Init_AttachObject_Request_link
{
public:
  explicit Init_AttachObject_Request_link(::dual_panda_moveit2_interface::srv::AttachObject_Request & msg)
  : msg_(msg)
  {}
  ::dual_panda_moveit2_interface::srv::AttachObject_Request link(::dual_panda_moveit2_interface::srv::AttachObject_Request::_link_type arg)
  {
    msg_.link = std::move(arg);
    return std::move(msg_);
  }

private:
  ::dual_panda_moveit2_interface::srv::AttachObject_Request msg_;
};

class Init_AttachObject_Request_id
{
public:
  Init_AttachObject_Request_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_AttachObject_Request_link id(::dual_panda_moveit2_interface::srv::AttachObject_Request::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_AttachObject_Request_link(msg_);
  }

private:
  ::dual_panda_moveit2_interface::srv::AttachObject_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::dual_panda_moveit2_interface::srv::AttachObject_Request>()
{
  return dual_panda_moveit2_interface::srv::builder::Init_AttachObject_Request_id();
}

}  // namespace dual_panda_moveit2_interface


namespace dual_panda_moveit2_interface
{

namespace srv
{

namespace builder
{

class Init_AttachObject_Response_success
{
public:
  Init_AttachObject_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::dual_panda_moveit2_interface::srv::AttachObject_Response success(::dual_panda_moveit2_interface::srv::AttachObject_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return std::move(msg_);
  }

private:
  ::dual_panda_moveit2_interface::srv::AttachObject_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::dual_panda_moveit2_interface::srv::AttachObject_Response>()
{
  return dual_panda_moveit2_interface::srv::builder::Init_AttachObject_Response_success();
}

}  // namespace dual_panda_moveit2_interface

#endif  // DUAL_PANDA_MOVEIT2_INTERFACE__SRV__DETAIL__ATTACH_OBJECT__BUILDER_HPP_
