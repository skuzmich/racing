#/trunk/graphics

set (TEST graphics_test)

Find_Package (SDL REQUIRED)
Find_Package (SDL_image REQUIRED)
Find_Package (SDL_ttf REQUIRED)

set (
  GRAPHICS_LIBRARYS

  ${SDL_LIBRARY}
  ${SDLIMAGE_LIBRARY} 
  SDL_ttf 
  ${SDLMAIN_LIBRARY}
  ${GL_LIBRARY}
)

set (HEADERS Graphics.h Sprite.h GPInterface.h loading_functions.h Text.h)

set (
  SOURCES

  Sprite.cpp
  Graphics.cpp
  loading_functions.cpp
  GPInterface.cpp
  Text.cpp
)

set (TESTS ${SOURCES} graphics_test.cpp)

if(UNIX)
    if ( NOT SDL_FOUND )
        message ( FATAL_ERROR "SDL not found!" )
    endif ( NOT SDL_FOUND )
endif(UNIX)

link_libraries ( ${GRAPHICS_LIBRARYS} )


add_library (graphics_lib ${HEADERS} ${SOURCES})

add_executable (graphics_test ${TESTS})

target_link_libraries(graphics_test base_lib)
