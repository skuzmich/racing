#/trunk/graphics

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

set (HEADERS Graphics.h Sprite.h GPInterface.h)

set (
  SOURCES

  Sprite.cpp
  Graphics.cpp
  GPInterface.cpp
)

set (TESTS ${SOURCES} graphics_test.cpp)


if ( NOT SDL_FOUND )
  message ( FATAL_ERROR "SDL not found!" )
endif ( NOT SDL_FOUND )

link_libraries ( ${GRAPHICS_LIBRARYS} )


add_library (graphics_lib ${HEADERS} ${SOURCES})

add_executable (graphics_test ${TESTS})

target_link_libraries(graphics_test base_lib)
