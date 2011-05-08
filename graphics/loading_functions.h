// Copyright (C) 2011 Horoshenkih Sergey
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef _LOAD_FUNCTIONS_H_
  #define _LOAD_FUNCTIONS_H_

#include "Graphics.h"

int IsNPOT(int width, int height);

GLuint LoadGLTexture(const char *filename, SDL_Color *colorkey);
#endif
