#ifndef _LOAD_FUNCTIONS_H_
  #define _LOAD_FUNCTIONS_H_

#include "Graphics.h"

int IsNPOT(int width, int height);

GLuint LoadGLTexture(const char *filename, SDL_Color *colorkey);
#endif
