add_library(camera camera.hpp camera.cpp)
target_link_libraries(camera glm)
target_include_directories(camera PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
message(STATUS "Camera util configured!")