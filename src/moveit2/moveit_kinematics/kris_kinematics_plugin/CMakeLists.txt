cmake_minimum_required(VERSION 3.8)
project(kris_kinematics_plugin)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(moveit_core REQUIRED)
find_package(moveit_msgs REQUIRED)
find_package(pluginlib REQUIRED)
find_package(tf2_kdl REQUIRED)
find_package(tf2_eigen REQUIRED)
find_package(eigen3_cmake_module REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(random_numbers REQUIRED)

# Find pinocchio using CMake module
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} /opt/ros/humble/lib/x86_64-linux-gnu/cmake)
find_package(pinocchio REQUIRED)

set(MOVEIT_LIB_NAME moveit_kris_kinematics_plugin)

add_library(${MOVEIT_LIB_NAME} SHARED
  src/kris_kinematics_plugin.cpp
)

ament_target_dependencies(${MOVEIT_LIB_NAME}
  rclcpp
  moveit_core
  moveit_msgs
  pluginlib
  tf2_kdl
  tf2_eigen
  Eigen3
  random_numbers
)

# Link pinocchio using CMake target
target_link_libraries(${MOVEIT_LIB_NAME} pinocchio::pinocchio)

target_include_directories(${MOVEIT_LIB_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

# prevent pluginlib from using boost
target_compile_definitions(${MOVEIT_LIB_NAME} PUBLIC "PLUGINLIB__DISABLE_BOOST_FUNCTIONS")

install(TARGETS ${MOVEIT_LIB_NAME}
  EXPORT ${MOVEIT_LIB_NAME}Targets
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install(DIRECTORY include/
  DESTINATION include
)

install(FILES kris_kinematics_plugin_description.xml
  DESTINATION share/${PROJECT_NAME}
)

# Tests
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  find_package(ament_cmake_gtest REQUIRED)
  
  # Standard linting
  ament_lint_auto_find_test_dependencies()
  
  # Unit tests
  ament_add_gtest(test_kris_kinematics
    test/test_kris_kinematics.cpp
  )
  
  if(TARGET test_kris_kinematics)
    target_link_libraries(test_kris_kinematics ${MOVEIT_LIB_NAME})
    ament_target_dependencies(test_kris_kinematics
      rclcpp
      moveit_core
      moveit_ros_planning
    )
  endif()
endif()

ament_export_targets(${MOVEIT_LIB_NAME}Targets HAS_LIBRARY_TARGET)
ament_export_dependencies(
  rclcpp
  moveit_core
  moveit_msgs
  pluginlib
  tf2_kdl
  tf2_eigen
  Eigen3
  random_numbers
)

ament_package()