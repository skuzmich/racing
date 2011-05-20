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

class Sprite { // Class for sprites
 public:
  Sprite(unsigned int texture_id, float width, float height, int anchor_point,
        float x_coord = 0, float y_coord = 0, float angle = 0.0);
        // width, height - sizes of image on the screen (now in pixels)
        // x_coord, y_coord, angle - coordinates
  ~Sprite();
  
  void GetCoordinates(float X, float Y, float ang); // Using this method
                                                // sprite gets coordinates

  // Some getters below
  float x_coord() const;
  float y_coord() const;
  float angle() const;
  unsigned int texture_id() const;
  float width() const;
  float height() const;
  int anchor_point();
  
 private:
  float x_coord_;
  float y_coord_;
  float angle_;
  int anchor_point_; // "ZERO" (0) or "CENTER"(1)

  unsigned int texture_id_; // TextureID of sprite in the Texture manager
  
  float width_; // width of sprite on the screen
  float height_; // height of sprite on the screen
};

#endif
