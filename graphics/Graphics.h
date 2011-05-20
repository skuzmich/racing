// Copyright (C) 2011 Horoshenkih Sergey
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef _GRAPHICS_H_
  #define _GRAPHICS_H_

#include "Sprite.h"
#include "TextureManager.h"

#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#include <GL/gl.h>

#include <math.h>
#include <assert.h>

class Graphics {
  private:
    SDL_Surface *surf_display_;
    TextureManager *tex_manager_;
    std::vector<class Sprite *> list_of_cars_;
    std::vector<class Sprite *> list_of_backs_;
    bool fullscreen_;

  public:
    static Graphics *Create(int scr_w, int scr_h);
    Graphics();
    ~Graphics();
    bool Initialize(int scr_w, int scr_h);
    bool LoadCar(float h, float w, const char *img);
    bool LoadBack(const char *img);
    bool SetCarCoordinates(int i /*number of car in list*/,
                              float X, float Y, float ang);
    bool fullscreen();
    void SetFullscreen(bool f);
    void BlitTexture(unsigned int tex_id, float x, float y, float angle,
                    int anchor, float x_size, float y_size);
    void Render();
    bool CleanUp();
};

#endif
