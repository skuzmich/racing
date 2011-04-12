#/trunk/app

cmake_minimum_required(VERSION 2.6)

set (SOURCES main.cpp)

add_executable (app ${SOURCES})

target_link_libraries(app physics_lib graphics_lib Box2D)
