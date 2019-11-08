add_library(shader_utils shader_object.cpp shader_object.hpp program_object.cpp program_object.hpp)
target_link_libraries(shader_utils glad glm)
# add utils folder to include directory
target_include_directories(shader_utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
message(STATUS "Shader_utils configured!")