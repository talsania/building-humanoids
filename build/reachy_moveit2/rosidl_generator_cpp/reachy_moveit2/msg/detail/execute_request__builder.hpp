// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from reachy_moveit2:msg/ExecuteRequest.idl
// generated code does not contain a copyright notice

#ifndef REACHY_MOVEIT2__MSG__DETAIL__EXECUTE_REQUEST__BUILDER_HPP_
#define REACHY_MOVEIT2__MSG__DETAIL__EXECUTE_REQUEST__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "reachy_moveit2/msg/detail/execute_request__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace reachy_moveit2
{

namespace msg
{

namespace builder
{

class Init_ExecuteRequest_command
{
public:
  explicit Init_ExecuteRequest_command(::reachy_moveit2::msg::ExecuteRequest & msg)
  : msg_(msg)
  {}
  ::reachy_moveit2::msg::ExecuteRequest command(::reachy_moveit2::msg::ExecuteRequest::_command_type arg)
  {
    msg_.command = std::move(arg);
    return std::move(msg_);
  }

private:
  ::reachy_moveit2::msg::ExecuteRequest msg_;
};

class Init_ExecuteRequest_header
{
public:
  Init_ExecuteRequest_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExecuteRequest_command header(::reachy_moveit2::msg::ExecuteRequest::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_ExecuteRequest_command(msg_);
  }

private:
  ::reachy_moveit2::msg::ExecuteRequest msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::reachy_moveit2::msg::ExecuteRequest>()
{
  return reachy_moveit2::msg::builder::Init_ExecuteRequest_header();
}

}  // namespace reachy_moveit2

#endif  // REACHY_MOVEIT2__MSG__DETAIL__EXECUTE_REQUEST__BUILDER_HPP_
