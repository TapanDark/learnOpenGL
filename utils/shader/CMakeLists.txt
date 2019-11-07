add_library(shader_utils shader_util.cpp shader_util.hpp)
target_link_libraries(shader_utils glad)
# add utils folder to include directory
target_include_directories(shader_utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
message(status "Shader_utils configured!")