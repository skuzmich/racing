#/trunk/graphics

Find_Package (SDL REQUIRED)
Find_Package (SDL_image REQUIRED)
Find_Package (SDL_ttf REQUIRED)

if (NOT SDL_FOUND)
    message (FATAL_ERROR "libsdl not found!")
endif()

if (NOT SDL_FOUND)
    message (FATAL_ERROR "libsdl_image not found!")
endif()

if (NOT SDL_FOUND)
    message (FATAL_ERROR "libsdl_ttf not found!")
endif()

set (GRAPHICS_LIBRARYS
  ${SDL_LIBRARY}
  ${SDLIMAGE_LIBRARY} 
  ${SDLTTF_LIBRARY}
  ${SDLMAIN_LIBRARY}
  ${GL_LIBRARY}
)

set (HEADERS 
  Graphics.h
  Sprite.h
  GPInterface.h
  loading_functions.h
  Text.h)

set (SOURCES
  Sprite.cpp
  Graphics.cpp
  loading_functions.cpp
  GPInterface.cpp
  Text.cpp
)

link_libraries (${GRAPHICS_LIBRARYS})
add_library (graphics_lib ${HEADERS} ${SOURCES})
