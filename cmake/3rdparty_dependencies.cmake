# These are the 3rd party dependencies we are building from source.
set(LOGL_BUILD_3RDPARTY_SOURCE_DIR ${CMAKE_SOURCE_DIR}/3rdparty/src)

###############################################################################
# GLFW
###############################################################################
set(GLFW_VERSION "3_3_0")
add_subdirectory(${LOGL_BUILD_3RDPARTY_SOURCE_DIR}/glfw/${GLFW_VERSION})