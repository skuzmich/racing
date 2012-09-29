// Copyright (C) 2011 Horoshenkih Sergey
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "Sprite.h"

Sprite::Sprite() {
  x_coord_ = 0;
  y_coord_ = 0;
  angle_ = 0.0f;
  surf_sprite_ = NULL;
  sprite_texture_ = 0;
  height_ = 0;
  width_ = 0;
}

Sprite::Sprite( int height, int width, GLuint texture) {
  x_coord_ = 0;
  y_coord_ = 0;
  angle_   = 0;
  surf_sprite_ = NULL;
  sprite_texture_ = texture;
  height_ = height;
  width_ = width;
}

void Sprite::GetCoordinates(int X, int Y, float ang) {
  x_coord_ = X;
  y_coord_ = Y;
  angle_ = ang;
}

int Sprite::height() {
  return height_;
}

int Sprite::width() {
  return width_;
}

int Sprite::x_coord() {
  return x_coord_;
}

int Sprite::y_coord() {
  return y_coord_;
}

float Sprite::angle() {
  return angle_;
}

GLuint Sprite::sprite_texture() {
  return sprite_texture_;
}
