// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from dual_panda_moveit2_interface:msg/SpawnBatch.idl
// generated code does not contain a copyright notice

#ifndef DUAL_PANDA_MOVEIT2_INTERFACE__MSG__DETAIL__SPAWN_BATCH__BUILDER_HPP_
#define DUAL_PANDA_MOVEIT2_INTERFACE__MSG__DETAIL__SPAWN_BATCH__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "dual_panda_moveit2_interface/msg/detail/spawn_batch__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace dual_panda_moveit2_interface
{

namespace msg
{

namespace builder
{

class Init_SpawnBatch_objects
{
public:
  Init_SpawnBatch_objects()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::dual_panda_moveit2_interface::msg::SpawnBatch objects(::dual_panda_moveit2_interface::msg::SpawnBatch::_objects_type arg)
  {
    msg_.objects = std::move(arg);
    return std::move(msg_);
  }

private:
  ::dual_panda_moveit2_interface::msg::SpawnBatch msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::dual_panda_moveit2_interface::msg::SpawnBatch>()
{
  return dual_panda_moveit2_interface::msg::builder::Init_SpawnBatch_objects();
}

}  // namespace dual_panda_moveit2_interface

#endif  // DUAL_PANDA_MOVEIT2_INTERFACE__MSG__DETAIL__SPAWN_BATCH__BUILDER_HPP_
