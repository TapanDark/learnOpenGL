file(GLOB_RECURSE GL_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/oogl/*.hpp")
file(GLOB_RECURSE GL_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

message(STATUS ${GL_HEADERS})

add_library(oogl ${GL_HEADERS} ${GL_SOURCES})
target_link_libraries(oogl PRIVATE glad glm)
# add utils folder to include directory
target_include_directories(oogl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
message(STATUS "Object Oriented GL utils configured!")