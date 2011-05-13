// Copyright (C) 2011 Horoshenkih Sergey
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef _GRAPHICS_H_
  #define _GRAPHICS_H_

#include "Sprite.h"
#include "GPInterface.h"

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
    GPInterface *gpi_;
    std::vector<class SpriteCar *> list_of_cars_;
    std::vector<class SpriteBack *> list_of_backs_;
    bool fullscreen_;

  public:
    static Graphics *Create(int scr_w, int scr_h);
    Graphics();
    ~Graphics();
    bool Initialize(int scr_w, int scr_h);
    bool InitGPInterface(int gr_w, int gr_h, int ph_w, int ph_h);
    bool LoadCar(int h, int w, const char *img);
    bool LoadBack(const char *img);
    bool SetCarCoordinates(int i /*number of car in list*/,
                              float X, float Y, float ang);
    bool fullscreen();
    void SetFullscreen(bool f);
    void Render();
    bool CleanUp();
};

#endif
