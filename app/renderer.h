// Copyright (C) 2012 Kuzmich Svyatoslav <svatoslav1@gmail.com>
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef APP_RENDERER_H
#define APP_RENDERER_H

class Graphics;
class World;

class Renderer {
 private:
  Graphics *_graphics;
  Settings *_settings;
 public:
  
  Renderer(Settings * settings);
  ~Renderer();
  void Render();
  void SetSpriteCoordinates(int32 num, float32 x, float32 y, float32 al);
  bool AddSprite( int32 w, int32 h, std::string image_path);

  friend class World;
};

#endif
