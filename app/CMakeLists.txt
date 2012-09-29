#/trunk/app

cmake_minimum_required(VERSION 2.6)

set (SOURCES main.cpp world.cpp settings.cpp renderer.cpp)

add_executable (app ${SOURCES})

target_link_libraries(app physics_lib graphics_lib base_lib Box2D)
