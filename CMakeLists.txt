#/trunk/

cmake_minimum_required(VERSION 2.6)

project (racing2d)

#include_directories("${PROJECT_BINARY_DIR}")

add_subdirectory (graphics)

# Third Party
add_subdirectory(third_party)

add_subdirectory (physics)
