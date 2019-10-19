cmake_minimum_required(VERSION 3.0.2 FATAL_ERROR)

project(opengl_practive C CXX)

# set path where we add our custom cmake modules.
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Next include all of our 3rd party dependencies used in the project...
include(3rdparty_dependencies)

add_subdirectory(basic/hello_window)