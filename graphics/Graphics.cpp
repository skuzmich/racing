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

  tex_manager_ = new TextureManager();
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
  glViewport(0, 0, scr_w, scr_h);
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, 400/*scr_w*/, 300/*scr_h*/, 0, 1, -1); // according to
                                                            // physics coordinates

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

bool Graphics::LoadCar(float h, float w, const char *img){
  unsigned int tex_id = tex_manager_->LoadTexture(img);
  Sprite *tmp = new Sprite(tex_id, w, h, 1);
  if(tmp) {
    list_of_cars_.push_back(tmp);
    return true;
  } else {
      delete tmp;
      return false;
    }
}

bool Graphics::LoadBack(const char *img){
  unsigned int tex_id = tex_manager_->LoadTexture(img);
  Sprite *tmp = new Sprite(tex_id, surf_display_->w, surf_display_->h, 0);
  if(tmp) {
    list_of_backs_.push_back(tmp);
    return true;
  } else {
      delete tmp;
      return false;
    }
}

bool Graphics::SetCarCoordinates(int i, float X, float Y, float ang){
  if(i>=list_of_cars_.size()) {
    return false;
  } else {
      list_of_cars_[i]->GetCoordinates(X, Y, ang);
      return true;
  }
}

void Graphics::BlitTexture(unsigned int tex_id, float x, float y, float angle,
                            int anchor, float x_size, float y_size) {
  //printf("Blitting texture with ID %d\n", tex_id);
  int w_img = tex_manager_->GetImageWidthByID(tex_id);
  int w_tex = tex_manager_->GetTextureWidthByID(tex_id);
  int h_img = tex_manager_->GetImageHeightByID(tex_id);
  int h_tex = tex_manager_->GetTextureHeightByID(tex_id);
  GLuint texture = tex_manager_->GetTextureByID(tex_id);
  
  //printf("Parameters of sprite:\n x = %f\n y = %f\n", x,y);
  //printf("Parameters of texture:\n w_img = %d\n h_img = %d\n texture = %d\n w_tex = %d\n h_tex = %d\n", w_img, h_img, texture, w_tex, h_tex);
  // Enable alpha-blending
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Setting texture matrix  
	glMatrixMode(GL_TEXTURE);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 2*(float)w_tex/(float)w_img, 0, 2*(float)h_tex/(float)h_img, -1, 1);

  // Setting projection matrix
  /*
  glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 1, 1, 0, 1, -1);
    */
    
  // Setting modelview matrix	
	glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(x, y, 0);
    glRotatef((GLfloat)angle*180/3.14, 0, 0, 1);
   
  // Binding texture according to anchor point
	glBindTexture(GL_TEXTURE_2D, texture);
  if(anchor == 0) { // ZERO
    glBegin(GL_QUADS);
      glColor3f(1.0f, 1.0f, 1.0f);
      glTexCoord2d(0, 0);
        glVertex2d(0, 0);
      glTexCoord2d(1, 0);
        glVertex2d(x_size, 0);
      glTexCoord2d(1, 1);
        glVertex2d(x_size, y_size);
      glTexCoord2d(0, 1);
        glVertex2d(0, y_size);
    glEnd();
  } else { // CENTER
    glBegin(GL_QUADS);
      glColor3f(1.0f, 1.0f, 1.0f);
      glTexCoord2d(0, 0);
        glVertex2d(-x_size/2, -y_size/2);
      glTexCoord2d(1, 0);
        glVertex2d(x_size/2, -y_size/2);
      glTexCoord2d(1, 1);
        glVertex2d(x_size/2, y_size/2);
      glTexCoord2d(0, 1);
        glVertex2d(-x_size/2, y_size/2);
    glEnd();
  }
	glPopMatrix();
	glPopMatrix();
	glMatrixMode(GL_TEXTURE);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glDisable(GL_BLEND);
}
void Graphics::Render() {
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  std::vector<class Sprite *>::iterator i = list_of_backs_.begin();
  BlitTexture((*i)->texture_id(), 0.0, 0.0, 0.0, 0, 400, 300);
  
  for (i = list_of_cars_.begin(); i !=  list_of_cars_.end(); i++) {
    BlitTexture((*i)->texture_id(), (*i)->x_coord(), (*i)->y_coord(),
                (*i)->angle(), 1, (*i)->width(), (*i)->height());
  }
  SDL_GL_SwapBuffers();
  
}

Graphics::Graphics() {
    surf_display_ = NULL;
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
  tex_manager_->DeleteAllTextures();
  delete tex_manager_;
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
