#/trunk/

cmake_minimum_required(VERSION 2.6)

project (racing2d)

INCLUDE_DIRECTORIES(physics/lib)
INCLUDE_DIRECTORIES(third_party)
INCLUDE_DIRECTORIES(graphics)
INCLUDE_DIRECTORIES(base)

#adding SLD include directories
add_definitions(`sdl-config --cflags`)

#include_directories("${PROJECT_BINARY_DIR}")

add_subdirectory (graphics)

# Third Party
add_subdirectory(third_party)

add_subdirectory (physics)
add_subdirectory (app)
