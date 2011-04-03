cmake_minimum_required(VERSION 2.6)

set (PROJECT racing)

project ($(project))

include_directories("${PROJECT_BINARY_DIR}")

add_subdirectory (graphics)
