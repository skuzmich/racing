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
    add_custom_command(    	
        OUTPUT ${RESOURCES_FILES} 

        COMMAND echo "Copying resources files..."    	
        COMMAND cp -r ${CMAKE_CURRENT_SOURCE_DIR}/resources/*  ${CMAKE_CURRENT_SOURCE_DIR}/build/
    )
endif()	

add_custom_target(track_file ALL DEPENDS ${RESOURCES_FILES}) 

#adding SLD include directories
if(UNIX)
    add_definitions(`sdl-config --cflags`)
    set (SDLMAIN_LIBRARY SDLmain)
    set (GL_LIBRARY GL)

elseif(WIN32)
    set (SDLIMAGE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/SDL/SDL_image-1.2.10/include)
    set (SDLIMAGE_LIBRARY     ${CMAKE_CURRENT_SOURCE_DIR}/third_party/SDL/SDL_image-1.2.10/lib/SDL_image.lib)
    set (SDLMAIN_LIBRARY      ${CMAKE_CURRENT_SOURCE_DIR}/third_party/SDL/SDL-1.2.14/lib/SDLmain.lib)
    set (SDL_INCLUDE_LIBRARY  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/SDL/SDL-1.2.14/include)
    set (SDL_LIBRARY_TEMP     ${CMAKE_CURRENT_SOURCE_DIR}/third_party/SDL/SDL-1.2.14/lib/SDL.lib)
    set (GL_LIBRARY opengl32.lib )

    INCLUDE_DIRECTORIES(${SDLIMAGE_INCLUDE_DIR})
    INCLUDE_DIRECTORIES(${SDL_INCLUDE_LIBRARY})
else()
    # Something wrong
endif()

#include_directories("${PROJECT_BINARY_DIR}")

add_subdirectory (graphics)
add_subdirectory (base)

# Third Party
add_subdirectory(third_party)

add_subdirectory (physics)
add_subdirectory (app)
