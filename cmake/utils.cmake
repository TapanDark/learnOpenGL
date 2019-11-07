# Macro to get all subdirectories inside a directory
MACRO(SUBDIRLIST result target)
  FILE(GLOB children RELATIVE ${CMAKE_SOURCE_DIR} ${target}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${child})
      FILE(GLOB cmakeLists "${child}/CMakeLists.txt")
        if(cmakeLists)
          LIST(APPEND dirlist ${child})
        endif()
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

# Popluate all the directories inside our utils folder that have a CMakeLists.txt
SUBDIRLIST(SUBDIRS ${CMAKE_SOURCE_DIR}/utils)
# Run Cmake for each utility
foreach(subdirectory IN LISTS SUBDIRS)
    message("${subdirectory}")
    add_subdirectory(${subdirectory})
endforeach()