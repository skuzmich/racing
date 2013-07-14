// Copyright (C) 2012 Kuzmich Svyatoslav <svatoslav1@gmail.com>
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef APP_RENDERER_H_
#define APP_RENDERER_H_

#include <string>
#include "./settings.h"
#include "../graphics/GPInterface.h"

class Graphics;
class Settings;
class World;

// Interface for SDL engine
class Renderer {
 private:
  Graphics *_graphics;
  Settings *_settings;

 public:
  explicit Renderer(Settings * settings, GPInterface * gpi);
  ~Renderer();
  void Render();
  void SetSpriteCoordinates(int32 num, float32 x, float32 y, float32 al);
  bool AddSprite(int32 w, int32 h, std::string image_path);

  friend class World;
};

#endif  // APP_RENDERER_H_
