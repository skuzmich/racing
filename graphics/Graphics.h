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
    SDL_Surface *back_surface_;
    GPInterface *gpi_;
    GLuint back_texture_;
    std::vector<class Sprite *> list_of_sprites_;
    bool fullscreen_;
  public:
    static Graphics *Create(int scr_w, int scr_h);
    Graphics();
    ~Graphics();
    bool Initialize(int scr_w, int scr_h);
    bool InitGPInterface(int gr_w, int gr_h, int ph_w, int ph_h);
    bool AddSprite(int X, int Y, float ang, int h, int w, const char *img);
    bool SetSpriteCoordinates(int i /*number of sprite in list*/,
                              float X, float Y, float ang);
    void BlitBack();
    void BlitSprite(int i);
    void Render();
    bool fullscreen();
    bool CleanUp();
    void FullscreenOn();
    void FullscreenOff();
};

#endif
