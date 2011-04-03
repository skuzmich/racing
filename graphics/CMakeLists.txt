set (PROJECT graphics)
set (TEST graphics_test)

Find_Package (SDL REQUIRED)
Find_Package (SDL_image REQUIRED)

set (
  GRAPHICS_LIBRARYS

  ${SDL_LIBRARY}
  ${SDLIMAGE_LIBRARY} 
  SDLmain 
  GL
)

set (HEADERS CGraphics.h)

set (
  SOURCES  

  CCar.cpp
  CGraphics.cpp
  common.cpp
)

set (TESTS ${SOURCES} GraphTest.cpp)


if ( NOT SDL_FOUND )
  message ( FATAL_ERROR "SDL not found!" )
endif ( NOT SDL_FOUND )

link_libraries ( ${GRAPHICS_LIBRARYS} )

#adding SLD include directories
add_definitions(`sdl-config --cflags`)

add_library (${PROJECT} ${HEADERS} ${SOURCES})

add_executable (graphics_test ${TESTS})

target_link_libraries(graphics_test ${PROJECT} )
