#/trunk/

cmake_minimum_required(VERSION 2.6)

project (racing2d)

INCLUDE_DIRECTORIES(physics)
INCLUDE_DIRECTORIES(third_party)
INCLUDE_DIRECTORIES(graphics)
INCLUDE_DIRECTORIES(base)
INCLUDE_DIRECTORIES(app)

set (RESOURCES_FILES ${CMAKE_CURRENT_SOURCE_DIR}/build/track.txt)

if(UNIX)
  add_custom_command(OUTPUT ${RESOURCES_FILES} 
    COMMAND echo "Copying resources files..."    	
    COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/resources/*  ${CMAKE_CURRENT_SOURCE_DIR}/build/
  )
endif()	

add_custom_target(track_file ALL DEPENDS ${RESOURCES_FILES}) 

if(UNIX)
  add_definitions(`sdl-config --cflags`)
  set (SDLMAIN_LIBRARY SDLmain)
  set (GL_LIBRARY GL)
else()
    message(FATAL_ERROR "Wrong host system!")
endif()

#adding SLD include directories
add_subdirectory(graphics)
add_subdirectory(base)
add_subdirectory(third_party)
add_subdirectory(physics)
add_subdirectory(app)
