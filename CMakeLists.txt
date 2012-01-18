#/trunk/

cmake_minimum_required(VERSION 2.6)

project (racing2d)

INCLUDE_DIRECTORIES(physics)
INCLUDE_DIRECTORIES(third_party)
INCLUDE_DIRECTORIES(graphics)
INCLUDE_DIRECTORIES(base)
INCLUDE_DIRECTORIES(app)

set (RESOURCES_FILES ${CMAKE_CURRENT_SOURCE_DIR}/build/track.txt)

add_custom_command(    	
	OUTPUT ${RESOURCES_FILES} 
	
	COMMAND echo "Copying resources files..."    	
	COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/resources/*  ${CMAKE_CURRENT_SOURCE_DIR}/build/
	
)

add_custom_target(track_file ALL DEPENDS ${RESOURCES_FILES}) 

#adding SLD include directories
add_definitions(`sdl-config --cflags`)

#include_directories("${PROJECT_BINARY_DIR}")

add_subdirectory (graphics)
add_subdirectory (base)

# Third Party
add_subdirectory(third_party)

add_subdirectory (physics)
add_subdirectory (app)
