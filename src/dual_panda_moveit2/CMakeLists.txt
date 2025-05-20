cmake_minimum_required(VERSION 3.8)
project(dual_panda_moveit2)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(moveit_ros_planning_interface REQUIRED)
find_package(moveit_task_constructor_core REQUIRED)
find_package(moveit_visual_tools REQUIRED)
find_package(moveit_core REQUIRED)
find_package(rclcpp REQUIRED)
find_package(dynamixel_sdk_custom_interfaces REQUIRED)
find_package(dual_panda_moveit2_interface REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)


# Collect all source files in the src/ directory
file(GLOB SRC_FILES "src/*.cpp")

# Loop over each source file and create a separate executable
foreach(SRC_FILE ${SRC_FILES})
  get_filename_component(EXEC_NAME ${SRC_FILE} NAME_WE)  # Extract filename without extension
  add_executable(${EXEC_NAME} ${SRC_FILE})
  target_include_directories(${EXEC_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)
  target_compile_features(${EXEC_NAME} PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
  ament_target_dependencies(${EXEC_NAME}
    moveit_ros_planning_interface
    moveit_task_constructor_core
    moveit_visual_tools
    moveit_core
    rclcpp
    dynamixel_sdk_custom_interfaces
    dual_panda_moveit2_interface
    tf2
    tf2_ros
    tf2_geometry_msgs
  )
  install(TARGETS ${EXEC_NAME}
    DESTINATION lib/${PROJECT_NAME})
endforeach()

install(DIRECTORY launch DESTINATION share/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()