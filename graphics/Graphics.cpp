// Copyright (C) 2011 Horoshenkih Sergey
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "Graphics.h"

bool Graphics::Initialize(int scr_w, int scr_h) {

  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "Video initialization failed: %s\n", SDL_GetError());
    return false;
  }
  
  const SDL_VideoInfo* info = NULL;
  info = SDL_GetVideoInfo();
  int bits_per_pixel = info->vfmt->BitsPerPixel;
  
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  
  if((surf_display_ = SDL_SetVideoMode(scr_w, scr_h, bits_per_pixel, SDL_OPENGL))
    == NULL) {
    fprintf(stderr, "Video mode set failed: %s\n", SDL_GetError());
    return false;
  }

  
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glViewport(0, 0, scr_w, scr_h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(0, scr_w, scr_h, 0, 1, -1);

  glMatrixMode(GL_MODELVIEW);

  glEnable(GL_TEXTURE_2D);

  glLoadIdentity();
  
  SDL_WM_SetCaption("MIPT racing game","MIPT racing game");
  return true;
}

Graphics *Graphics::Create(int scr_w, int scr_h) {
  Graphics *ret = new Graphics();
  if (ret->Initialize(scr_w, scr_h))
    return ret;
  delete ret;
  return NULL;
}

bool Graphics::LoadCar(int h, int w, const char *img){
  SpriteCar *tmp = new SpriteCar(img, w, h);
  if(tmp) {
    list_of_cars_.push_back(tmp);
    return true;
  } else {
      delete tmp;
      return false;
    }
}

bool Graphics::LoadBack(const char *img){
  SpriteBack *tmp = new SpriteBack(img, surf_display_->w, surf_display_->h);
  if(tmp) {
    list_of_backs_.push_back(tmp);
    
    return true;
  } else {
      delete tmp;
      return false;
    }
}

bool Graphics::SetCarCoordinates(int i, float X, float Y, float ang){
  assert(gpi_);
  if(i>=list_of_cars_.size()) {
    return false;
  } else {
      list_of_cars_[i]->GetCoordinates(gpi_->gr_x(X), gpi_->gr_y(Y),
                                          gpi_->gr_ang(ang));
      return true;
  }
}

void Graphics::Render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  std::vector<class SpriteBack *>::iterator i = list_of_backs_.begin();
  (*i)->Blit();
  
  for (int i = 0; i < list_of_cars_.size(); i++) {
    list_of_cars_[i]->Blit();
  }
  SDL_GL_SwapBuffers();
}

Graphics::Graphics() {
    surf_display_ = NULL;
    gpi_ = NULL;
    fullscreen_ = false;
}

Graphics::~Graphics() {
}

bool Graphics::CleanUp() {
  SetFullscreen(false); // It's necessary, otherwise you'll have to change the screen
                   // parameters after exit by hand
  for(unsigned int i = 0; i < list_of_cars_.size(); i++) {
    if (list_of_cars_[i]) {
      delete list_of_cars_[i];
    }
  }
  for(unsigned int i = 0; i < list_of_backs_.size(); i++) {
    if (list_of_backs_[i]) {
      delete list_of_backs_[i];
    }
  }
  
  if (surf_display_) {
    SDL_FreeSurface(surf_display_);
  }

  if (gpi_) {
    delete gpi_;
  }
  SDL_Quit();
  return true;
}

bool Graphics::fullscreen() {
  return fullscreen_;
}

void Graphics::SetFullscreen(bool f) {
  if((f&&fullscreen_) || (!f&&!fullscreen_)) { // "XOR"
    fullscreen_ = !fullscreen_;
    SDL_WM_ToggleFullScreen(surf_display_);
  }
}

bool Graphics::InitGPInterface(int gr_w, int gr_h, int ph_w, int ph_h){
  GPInterface *tmp = new GPInterface();
  if (tmp) {
    if (tmp->Init(gr_w, gr_h, ph_w, ph_h)) {
      gpi_ = tmp;
      return true;
    }
  }
  delete tmp;
  return false;
}
