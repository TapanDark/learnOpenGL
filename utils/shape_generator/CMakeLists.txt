add_library(shape_generator shape_generator.cpp shape_generator.hpp)
target_link_libraries(shape_generator oogl glm glad) 
# add utils folder to include directory
target_include_directories(shape_generator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
message(STATUS "Shape generator configured!")