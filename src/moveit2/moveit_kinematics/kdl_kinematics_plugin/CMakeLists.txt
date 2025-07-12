set(MOVEIT_LIB_NAME moveit_kdl_kinematics_plugin)

add_library(${MOVEIT_LIB_NAME} SHARED
  src/kdl_kinematics_plugin.cpp
  src/chainiksolver_vel_mimic_svd.cpp)

ament_target_dependencies(${MOVEIT_LIB_NAME}
  rclcpp
  random_numbers
  pluginlib
  moveit_core
  moveit_msgs
  orocos_kdl
  kdl_parser
  tf2_kdl
  EIGEN3
)

# prevent pluginlib from using boost
target_compile_definitions(${MOVEIT_LIB_NAME} PUBLIC "PLUGINLIB__DISABLE_BOOST_FUNCTIONS")
# Causes the visibility macros to use dllexport rather than dllimport,
# which is appropriate when building the dll but not consuming it.
target_compile_definitions(${MOVEIT_LIB_NAME} PRIVATE "MOVEIT_KDL_KINEMATICS_PLUGIN_BUILDING_DLL")

install(DIRECTORY include/ DESTINATION include)

if(BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)
  find_package(moveit_ros_planning REQUIRED)

  # KDL chain print test executable
  add_executable(test_kdl_chain_print test/test_kdl_chain_print.cpp)
  target_include_directories(test_kdl_chain_print PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
  )
  target_link_libraries(test_kdl_chain_print ${MOVEIT_LIB_NAME})
  ament_target_dependencies(test_kdl_chain_print
    rclcpp
    moveit_core
    moveit_ros_planning
    moveit_msgs
    pluginlib
    orocos_kdl
    kdl_parser
    tf2_kdl
    EIGEN3
    random_numbers
  )

  install(TARGETS test_kdl_chain_print DESTINATION lib/kdl_kinematics_plugin)

endif()
