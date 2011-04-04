cmake_minimum_required(VERSION 2.6)

set (PROJECT racing)

project ($(project))

set (THIRD_PARTY_DIR third_party)

include_directories("${PROJECT_BINARY_DIR}")

add_subdirectory (graphics)

# Third Party
add_subdirectory(third_party)

add_subdirectory (physics)
