cmake_minimum_required(VERSION 3.8)
project(jacobian_test)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Pinocchio using CMake module
find_package(pinocchio REQUIRED)

# Find Eigen3
find_package(Eigen3 REQUIRED)

# Create executable
add_executable(test_jacobian_standalone test_jacobian_standalone.cpp)

# Link libraries
target_link_libraries(test_jacobian_standalone 
    pinocchio::pinocchio
    Eigen3::Eigen
)