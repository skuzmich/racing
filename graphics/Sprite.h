// Copyright (C) 2011 Horoshenkih Sergey
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#include <math.h>
#include <assert.h>

class Sprite {
 public:
  Sprite();
  Sprite( int height, int width, GLuint texture);
  ~Sprite();
  void GetCoordinates(int X, int Y, float ang);
  int height();
  int width();
  int x_coord();
  int y_coord();
  float angle();
  GLuint sprite_texture();
 private:
  int x_coord_;
  int y_coord_;
  float angle_;
  
  SDL_Surface *surf_sprite_;
  GLuint sprite_texture_;
  int height_;
  int width_;

};

#endif
