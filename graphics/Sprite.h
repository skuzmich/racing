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

class Sprite { // Base class for sprites
 public:
  Sprite(const char *filename, int width, int height,
        int x_coord = 0, int y_coord = 0, float angle = 0.0);
        // width, height - sizes of image on the screen (now in pixels)
        // x_coord, y_coord, angle - coordinates
  ~Sprite();
  
  void GetCoordinates(int X, int Y, float ang); // Using this method
                                                // sprite gets coordinates

  virtual void Blit(); // Each kind of sprites (car, background, swadow, etc.)
                       // needs own method for blitting
  // Some getters below
  int x_coord() const;
  int y_coord() const;
  float angle() const;
  GLuint sprite_texture() const;
  int width() const;
  int height() const;
  int w_img() const;
  int h_img() const;
  int w_tex() const;
  int h_tex() const;
  
 protected:
  int x_coord_;
  int y_coord_;
  float angle_;

  GLuint sprite_texture_; // Texture of sprite
  
  int width_; // width of sprite on the screen
  int height_; // height of sprite on the screen
  
  int w_img_; // real width of loaded image
  int h_img_; // real height of loaded image
  
  int w_tex_; // width of texture (must be power of two)
  int h_tex_; // height of texture (must be power of two)
};

class SpriteCar : public Sprite {
 public:
  SpriteCar(const char *filename, int width, int height,
        int x_coord = 0, int y_coord = 0, float angle = 0.0);
  void Blit(); // Virtual method from base class
};

class SpriteBack : public Sprite {
 public:
  SpriteBack(const char *filename, int width, int height,
        int x_coord = 0, int y_coord = 0, float angle = 0.0);
  void Blit(); // Virtual method from base class
};
#endif
