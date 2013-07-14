// Copyright (C) 2012 Kuzmich Svyatoslav <svatoslav1@gmail.com>
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <string>

#include "../physics/predecls.h"
#include "../graphics/Graphics.h"
#include "./renderer.h"

Renderer::Renderer(Settings *settings, GPInterface *gpi) {
  _settings = settings;
  _graphics = Graphics::Create(settings->GetGraphWidth(),
                               settings->GetGraphHeight());

  assert(_graphics);

  _graphics->InitGPInterface( gpi);

}

bool Renderer::AddSprite(int32 w, int32 h, std::string image_path) {
  return _graphics->AddSprite(w, h, image_path.c_str());
}

void Renderer::Render() {
  _graphics->Render();
}

void Renderer::SetSpriteCoordinates(int32 num,
                                    float32 x,
                                    float32 y,
                                    float32 al) {
  _graphics->SetSpriteCoordinates(num, x, y, al);
}

Renderer::~Renderer() {
  delete _graphics;
}
