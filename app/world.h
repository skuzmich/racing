// Copyright (C) 2012 Kuzmich Svyatoslav <svatoslav1@gmail.com>
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef APP_WORLD_H
#define APP_WORLD_H
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
// std::vector<Object *> _objects;
 

 public:
  void Update(Event *event);
  std::vector<Car *> GetCars() { return _cars; }
  void Render();
  World(std::string config_file_path, Settings *settings, Renderer * renderer);
  ~World();
};

#endif /* APP_WORLD_H */
