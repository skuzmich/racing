set (PROJECT graphics)
set (TEST graphics_test)


set (
  GRAPHICS_LIBRARYS

  ${SDL_LIBRARY}
  ${SDLIMAGE_LIBRARY} 
  SDLmain 
  GL
)

#======= GRAPHICS LIBRIARY =========  
project (${PROJECT})
set (HEADERS CGraphics.h)

set (
  SOURCES  

  CCar.cpp
  CGraphics.cpp
  common.cpp
)

set (TESTS GraphTest.cpp)

Find_Package (SDL REQUIRED)
Find_Package (SDL_image REQUIRED)

if ( NOT SDL_FOUND )
  message ( FATAL_ERROR "SDL not found!" )
endif ( NOT SDL_FOUND )

link_libraries ( ${GRAPHICS_LIBRARYS} )

#adding SLD include directories
add_definitions(`sdl-config --cflags`)

add_library (${PROJECT} ${HEADERS} ${SOURCES})

add_executable (${TEST} ${HEADERS} ${TESTS})

target_link_libraries(${TEST} ${GRAPHICS_LIBRARYS} graphics)
