// Copyright (C) 2011 Kuzmich Svyatoslav
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GRAPHICS_TEXT_H_
#define GRAPHICS_TEXT_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h>
#include <string>
#include "Graphics.h"

void DrawTextGL(int left, int top, TTF_Font* font, std::string text);

#endif
