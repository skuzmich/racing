// Copyright (C) 2011 Horoshenkih Sergey
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "./Graphics.h"

#include <sstream>

#include "./loading_functions.h"



bool Graphics::Initialize(int scr_w, int scr_h) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "Video initialization failed: %s\n", SDL_GetError());
    return false;
  }

  scr_w_ = scr_w;
  scr_h_ = scr_h;

  const SDL_VideoInfo* info = NULL;
  info = SDL_GetVideoInfo();
  int bits_per_pixel = info->vfmt->BitsPerPixel;

  SDL_GL_SetAttribute(SDL_GL_RED_SIZE,            8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,          8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,           8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,          8);

  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,          16);
  SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,         32);

  SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,      8);
  SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,    8);
  SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,     8);
  SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,    8);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  surf_display_ = SDL_SetVideoMode(scr_w, scr_h, bits_per_pixel, SDL_OPENGL);
  if (surf_display_ == NULL) {
    fprintf(stderr, "Video mode set failed: %s\n", SDL_GetError());
    return false;
  }

  SDL_Color colorkey = {0xFF, 0x00, 0xFF, 0};
  back_texture_ = LoadGLTexture("./gfx/Track1.png", &colorkey);
  assert(back_texture_);

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glViewport(0, 0, scr_w, scr_h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(0, scr_w, scr_h, 0, 1, -1);

  glMatrixMode(GL_MODELVIEW);

  glEnable(GL_TEXTURE_2D);

  glLoadIdentity();

  SDL_Surface* icon = SDL_LoadBMP("icon.bmp");
  SDL_WM_SetIcon(icon, NULL);
  SDL_WM_SetCaption("2D Racing", "2D racing");

  TTF_Init();
  font = TTF_OpenFont("ARIAL.TTF", 10);

  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 0);

  return true;
}


Graphics *Graphics::Create(int scr_w, int scr_h) {
  Graphics *ret = new Graphics();
  if (ret->Initialize(scr_w, scr_h))
    return ret;
  delete ret;
  return NULL;
}

bool Graphics::AddSprite(int h, int w, const char *img) {
  SDL_Color colorkey = {0xFF, 0x00, 0xFF, 0};
  GLuint tex = LoadGLTexture(img, &colorkey);

  if (tex) {
    Sprite *newsprite = new Sprite(h, w, tex);
    list_of_sprites_.push_back(newsprite);
    return true;
  } else {
      return false;
  }
}

bool Graphics::SetSpriteCoordinates(int i, float X, float Y, float ang) {
  if (i >= list_of_sprites_.size()) {
    return false;
  } else {
      list_of_sprites_[i]->GetCoordinates(gpi_->gr_x(X), gpi_->gr_y(Y),
                                          gpi_->gr_ang(ang));
      return true;
  }
}
void Graphics::BlitBack() {

  glBindTexture(GL_TEXTURE_2D, back_texture_);
  glColor3f(1, 1, 1);
  glEnable(GL_TEXTURE_2D);

  glBegin(GL_QUADS);
  // Top-left vertex (corner)
  glTexCoord2i(0, 0);
  glVertex2f(gpi_->x0, gpi_->y0);

  // Bottom-left vertex (corner)
  glTexCoord2i(1, 0);
  glVertex2f(gpi_->x1, gpi_->y0);

  // Bottom-right vertex (corner)
  glTexCoord2i(1, 1);
  glVertex2f(gpi_->x1, gpi_->y1);

  // Top-right vertex (corner)
  glTexCoord2i(0, 1);
  glVertex2f(gpi_->x0, gpi_->y1);

  glEnd();
}

void Graphics::BlitSprite(int i) {
    GLint wreal, hreal;
    GLint xpad = 0, ypad = 0;
    int w = static_cast<int>(list_of_sprites_[i]->width() * gpi_->scale_);
    int h = static_cast<int>(list_of_sprites_[i]->height() * gpi_->scale_);
//    printf("%i, %i\n",w,h);

    // TODO(svatoslav1): Clean up this mess and comment
    wreal = static_cast<int>(powf(2.0,
                ceilf(logf(static_cast<float>(w))
                    / logf(2.0f))));

    hreal = static_cast<int>(powf(2.0,
                ceilf(logf(static_cast<float>(h))
                    / logf(2.0f))));

    xpad = (wreal - w) / 2;
    ypad = (hreal - h) / 2;

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glMatrixMode(GL_TEXTURE);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 2 * wreal, 0, 2 * hreal, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glTranslatef(list_of_sprites_[i]->x_coord(),
                 list_of_sprites_[i]->y_coord(),
                 0);

    glRotatef(list_of_sprites_[i]->angle(), 0, 0, 1);

    glBindTexture(GL_TEXTURE_2D, list_of_sprites_[i]->sprite_texture());
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glTexCoord2d(xpad, ypad);
    glVertex2d(-w / 2,
               -h / 2);
    glTexCoord2d(xpad + w, ypad);
    glVertex2d(w / 2,
               -h / 2);
    glTexCoord2d(xpad + w,
                 ypad + h);
    glVertex2d(w / 2,
               h / 2);
    glTexCoord2d(xpad, ypad + h);
    glVertex2d(-w / 2,
                h / 2);
    glEnd();

    glPopMatrix();
    glMatrixMode(GL_TEXTURE);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glDisable(GL_BLEND);
}

void Graphics::Render() {
  static unsigned render_count = 0;
  static unsigned ticks_start = SDL_GetTicks();
  static unsigned fps = 0;

  // TODO(svatosav1): Clean up
  if ( render_count++ > 1000 ) {
    render_count = 0;
    fps = 1000000 / ((SDL_GetTicks() - ticks_start));
    ticks_start = SDL_GetTicks();
  }

  BlitBack();
  for (int i = 0; i < list_of_sprites_.size(); i++) {
    BlitSprite(i);
  }

// See what is wrong
//  glViewport(-list_of_sprites_[0]->x_coord() * 4 + scr_w_ / 2,
//              list_of_sprites_[0]->y_coord() * 4 - scr_h_ * 3 - scr_h_ / 2,
//             scr_w_ * 4,
//             scr_h_ * 4);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  std::ostringstream fps_str;
  fps_str << "fps: " << fps;
  DrawTextGL(1, 1, font, fps_str.str());

//  SDL_GL_SwapBuffers();
}

Graphics::Graphics() {
    surf_display_ = NULL;
    back_surface_ = NULL;
    gpi_ = NULL;
    back_texture_ = 0;
    fullscreen_ = false;
}

Graphics::~Graphics() {
}

bool Graphics::CleanUp() {
  FullscreenOff();  // It's necessary, otherwise you'll have to change
                    // the screen parameters by hand
  SDL_Quit();
  return true;
}

bool Graphics::fullscreen() {
  return fullscreen_;
}

void Graphics::FullscreenOn() {
  if (!fullscreen_) {  // We chould call SDL_WM_ToggleFullScreen() only if
                       // current state of screen is 'not fullscreen'
    fullscreen_ = true;  // Set state of screen to 'fullscreen'
    SDL_WM_ToggleFullScreen(surf_display_);
  }
}

void Graphics::FullscreenOff() {
  if (fullscreen_) {  // We chould call SDL_WM_ToggleFullScreen() only if
                      // current state of screen is 'fullscreen'
    fullscreen_ = false;  // Set state of screen to 'not fullscreen'
    SDL_WM_ToggleFullScreen(surf_display_);
  }
}


bool Graphics::InitGPInterface( GPInterface * gpi) {
    this->gpi_ = gpi;
}
