#/trunk/

cmake_minimum_required(VERSION 2.6)

project (racing2d)

INCLUDE_DIRECTORIES(physics)
INCLUDE_DIRECTORIES(third_party)
INCLUDE_DIRECTORIES(graphics)
INCLUDE_DIRECTORIES(base)


macro(copy_dir srcDir destDir)
    message(STATUS "Configuring directory ${destDir}")
    make_directory(${destDir})

    file(GLOB templateFiles RELATIVE ${srcDir} ${srcDir}/*)
    foreach(templateFile ${templateFiles})
        set(srcTemplatePath ${srcDir}/${templateFile})
        if(NOT IS_DIRECTORY ${srcTemplatePath})
            message(STATUS "Configuring file ${templateFile}")
            configure_file(
                    ${srcTemplatePath}
                    ${destDir}/${templateFile}
                    @ONLY)
        endif(NOT IS_DIRECTORY ${srcTemplatePath})
    endforeach(templateFile)
endmacro(copy_dir)

copy_dir(${CMAKE_CURRENT_SOURCE_DIR}/resources  ${CMAKE_CURRENT_SOURCE_DIR}/build/ )
copy_dir(${CMAKE_CURRENT_SOURCE_DIR}/resources/gfx  ${CMAKE_CURRENT_SOURCE_DIR}/build/gfx )

#adding SLD include directories
add_definitions(`sdl-config --cflags`)

#include_directories("${PROJECT_BINARY_DIR}")

add_subdirectory (graphics)
add_subdirectory (base)

# Third Party
add_subdirectory(third_party)

add_subdirectory (physics)
add_subdirectory (app)
