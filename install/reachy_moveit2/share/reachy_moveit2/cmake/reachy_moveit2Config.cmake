# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_reachy_moveit2_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED reachy_moveit2_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(reachy_moveit2_FOUND FALSE)
  elseif(NOT reachy_moveit2_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(reachy_moveit2_FOUND FALSE)
  endif()
  return()
endif()
set(_reachy_moveit2_CONFIG_INCLUDED TRUE)

# output package information
if(NOT reachy_moveit2_FIND_QUIETLY)
  message(STATUS "Found reachy_moveit2: 0.0.1 (${reachy_moveit2_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'reachy_moveit2' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${reachy_moveit2_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(reachy_moveit2_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "rosidl_cmake-extras.cmake;ament_cmake_export_dependencies-extras.cmake;ament_cmake_export_include_directories-extras.cmake;ament_cmake_export_libraries-extras.cmake;ament_cmake_export_targets-extras.cmake;rosidl_cmake_export_typesupport_targets-extras.cmake;rosidl_cmake_export_typesupport_libraries-extras.cmake")
foreach(_extra ${_extras})
  include("${reachy_moveit2_DIR}/${_extra}")
endforeach()
