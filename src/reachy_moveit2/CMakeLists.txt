cmake_minimum_required(VERSION 3.5)
project(reachy_moveit2)

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(shape_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(moveit_ros_planning_interface REQUIRED)

# Generate custom messages
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/RobotControlCommand.msg"
  "msg/AddObstacle.msg"
  "msg/ExecuteRequest.msg"
  DEPENDENCIES std_msgs sensor_msgs geometry_msgs shape_msgs
)

include_directories(include)

# Build the node executable
add_executable(reachy_sdk src/reachy_sdk.cpp)
ament_target_dependencies(reachy_sdk
  rclcpp
  std_msgs
  sensor_msgs
  geometry_msgs
  shape_msgs
  moveit_ros_planning_interface
)

# Make the custom message interfaces available to your executable
rosidl_target_interfaces(reachy_sdk ${PROJECT_NAME} "rosidl_typesupport_cpp")

install(TARGETS reachy_sdk
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}/
)

ament_package()
