# set(CMAKE_CXX_STANDARD 11)
add_executable(hello_window hello_window.cpp)
target_link_libraries(hello_window glfw GL)