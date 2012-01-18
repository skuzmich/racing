// Copyright (C) 2012 Kuzmich Svyatoslav <svatoslav1@gmail.com>
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef APP_WORLD_H_
#define APP_WORLD_H_

#include <string>
#include <vector>
#include "./settings.h"
#include "./renderer.h"
#include "../physics/objects.h"

class Settings;
class Event;
class Renderer;

class World {
 private:
  Settings *_settings;
  b2World *_world;
  Track   *_track;
  Renderer *_renderer;
  std::vector<Car *> _cars;
  std::vector<Box *> _boxes;

 public:
  World(std::string config_file_path, Settings *settings, Renderer * renderer);
  ~World();

  // Getting input and calculating physics for next frame
  void Update(Event *event);

  // Renderig all objects in the world ;)
  void Render();

  std::vector<Car *> GetCars() { return _cars; }
};

#endif  // APP_WORLD_H_
