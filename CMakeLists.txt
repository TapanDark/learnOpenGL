cmake_minimum_required(VERSION 3.2.0 FATAL_ERROR)

project(opengl_practice C CXX)

# set path where we add our custom cmake modules.
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Next include all of our 3rd party dependencies used in the project...
include(3rdparty_dependencies)
include(utils)

add_subdirectory(basic/hello_window)
add_subdirectory(basic/hello_triangle)
add_subdirectory(basic/3d_world)