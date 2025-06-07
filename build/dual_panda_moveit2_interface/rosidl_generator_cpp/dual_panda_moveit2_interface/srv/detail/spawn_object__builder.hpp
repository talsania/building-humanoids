// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from dual_panda_moveit2_interface:srv/SpawnObject.idl
// generated code does not contain a copyright notice

#ifndef DUAL_PANDA_MOVEIT2_INTERFACE__SRV__DETAIL__SPAWN_OBJECT__BUILDER_HPP_
#define DUAL_PANDA_MOVEIT2_INTERFACE__SRV__DETAIL__SPAWN_OBJECT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "dual_panda_moveit2_interface/srv/detail/spawn_object__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace dual_panda_moveit2_interface
{

namespace srv
{

namespace builder
{

class Init_SpawnObject_Request_objects
{
public:
  Init_SpawnObject_Request_objects()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::dual_panda_moveit2_interface::srv::SpawnObject_Request objects(::dual_panda_moveit2_interface::srv::SpawnObject_Request::_objects_type arg)
  {
    msg_.objects = std::move(arg);
    return std::move(msg_);
  }

private:
  ::dual_panda_moveit2_interface::srv::SpawnObject_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::dual_panda_moveit2_interface::srv::SpawnObject_Request>()
{
  return dual_panda_moveit2_interface::srv::builder::Init_SpawnObject_Request_objects();
}

}  // namespace dual_panda_moveit2_interface


namespace dual_panda_moveit2_interface
{

namespace srv
{

namespace builder
{

class Init_SpawnObject_Response_current_objects
{
public:
  explicit Init_SpawnObject_Response_current_objects(::dual_panda_moveit2_interface::srv::SpawnObject_Response & msg)
  : msg_(msg)
  {}
  ::dual_panda_moveit2_interface::srv::SpawnObject_Response current_objects(::dual_panda_moveit2_interface::srv::SpawnObject_Response::_current_objects_type arg)
  {
    msg_.current_objects = std::move(arg);
    return std::move(msg_);
  }

private:
  ::dual_panda_moveit2_interface::srv::SpawnObject_Response msg_;
};

class Init_SpawnObject_Response_success
{
public:
  Init_SpawnObject_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SpawnObject_Response_current_objects success(::dual_panda_moveit2_interface::srv::SpawnObject_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_SpawnObject_Response_current_objects(msg_);
  }

private:
  ::dual_panda_moveit2_interface::srv::SpawnObject_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::dual_panda_moveit2_interface::srv::SpawnObject_Response>()
{
  return dual_panda_moveit2_interface::srv::builder::Init_SpawnObject_Response_success();
}

}  // namespace dual_panda_moveit2_interface

#endif  // DUAL_PANDA_MOVEIT2_INTERFACE__SRV__DETAIL__SPAWN_OBJECT__BUILDER_HPP_
