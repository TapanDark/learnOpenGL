add_library(window_utils window_utils.cpp window_utils.hpp)
target_link_libraries(window_utils glfw) 
# add utils folder to include directory
target_include_directories(window_utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
message(STATUS "Window_utils configured!")