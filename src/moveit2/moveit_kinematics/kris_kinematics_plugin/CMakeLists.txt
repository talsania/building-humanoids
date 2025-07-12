# CMakeLists.txt

cmake_minimum_required(VERSION 3.16)
project(kris_kinematics_plugin VERSION 1.0.0 LANGUAGES CXX)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(random_numbers REQUIRED)
find_package(pluginlib REQUIRED)
find_package(moveit_core REQUIRED)
find_package(moveit_msgs REQUIRED)
find_package(tf2_kdl REQUIRED)
find_package(tf2_eigen REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(pinocchio REQUIRED)
find_package(hpp-fcl REQUIRED)        # ← Added

set(MOVEIT_LIB_NAME moveit_kris_kinematics_plugin)

add_library(${MOVEIT_LIB_NAME} SHARED
  src/kris_kinematics_plugin.cpp
)

ament_target_dependencies(${MOVEIT_LIB_NAME}
  rclcpp
  random_numbers
  pluginlib
  moveit_core
  moveit_msgs
  tf2_kdl
  tf2_eigen
  Eigen3
  pinocchio
  hpp-fcl                            # ← Added
)

# Link Pinocchio and HPP-FCL
target_link_libraries(${MOVEIT_LIB_NAME}
  pinocchio::pinocchio
  ${hpp-fcl_LIBRARIES}               # ← Ensures -lhpp-fcl
)

# prevent pluginlib from using boost
target_compile_definitions(${MOVEIT_LIB_NAME} PUBLIC
  "PLUGINLIB__DISABLE_BOOST_FUNCTIONS"
)
target_compile_definitions(${MOVEIT_LIB_NAME} PRIVATE
  "MOVEIT_KRIS_KINEMATICS_PLUGIN_BUILDING_DLL"
)

install(
  TARGETS ${MOVEIT_LIB_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)
install(DIRECTORY include/ DESTINATION include)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  find_package(ament_cmake_gtest REQUIRED)
  find_package(moveit_ros_planning REQUIRED)

  ament_lint_auto_find_test_dependencies()

  ament_add_gtest(test_simple_chain test/test_simple_chain.cpp)
  target_include_directories(test_simple_chain PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
  )
  target_link_libraries(test_simple_chain 
    ${MOVEIT_LIB_NAME}
    moveit_kdl_kinematics_plugin
  )
  ament_target_dependencies(test_simple_chain
    rclcpp
    moveit_core
    moveit_ros_planning
    moveit_msgs
    pluginlib
    tf2_kdl
    tf2_eigen
    Eigen3
    random_numbers
  )

endif()


ament_package()
