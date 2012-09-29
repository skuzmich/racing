// Copyright (C) 2012 Kuzmich Svyatoslav <svatoslav1@gmail.com>
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <string>
#include <iostream>
#include <fstream>

#include "../physics/predecls.h"
#include "../base/fileparser.h"
#include "./world.h"
#include "../base/event.h"
#include "../graphics/Graphics.h"

World::World(std::string config_file_path,
             Settings * settings,
             Renderer * renderer) {
  _renderer = renderer;
  _settings = settings;

  // Opening config file
  std::ifstream fd(config_file_path.c_str());

  b2Vec2 gravity = Readb2Vec2(&fd);

  // TODO(svatoslav1): Make configurable;
  bool do_sleep  = true;

  // Creating Box2D world
  _world = new b2World(gravity, true);

  std::string track_config_path = GetLine(&fd);
  std::string track_image_path  = GetLine(&fd);

  std::cout << "Track config path: " << track_config_path << std::endl;
  std::cout << "Track image  path: " << track_image_path  << std::endl;

  // Track consist of static objects like walls
  _track = new Track(_world, track_config_path);

  int number_of_cars = ReadInt(&fd);
  std::cout << "Number of cars: " << number_of_cars << std::endl;

  // Creating cars in the world
  for (int i = 0; i < number_of_cars; i++) {
    std::string car_config_path = GetLine(&fd);
    std::string car_image_path = GetLine(&fd);

    int32 sprite_width = ReadInt(&fd);
    int32 sprite_height = ReadInt(&fd);

    std::cout << "  Car config path: " << car_config_path << std::endl;
    std::cout << "  Car image  path: " << car_image_path  << std::endl;
    std::cout << "  Car sprite size: " << sprite_width << ":"
              << sprite_height  << std::endl;
    _renderer->AddSprite(sprite_width, sprite_height, car_image_path);

    b2Vec2 pos = Readb2Vec2(&fd);
    _cars.push_back(new Car(_world, pos.x, pos.y, _track, car_config_path));
  }

  int number_of_boxes = ReadInt(&fd);
  std::cout << "Number of boxes: " << number_of_boxes << std::endl;

  // Creating cars in the world
  for (int i = 0; i < number_of_boxes; i++) {
    std::string box_config_path = GetLine(&fd);
    std::string box_image_path = GetLine(&fd);

    int32 sprite_width = ReadInt(&fd);
    int32 sprite_height = ReadInt(&fd);

    std::cout << "  Box config path: " << box_config_path << std::endl;
    std::cout << "  Box image  path: " << box_image_path  << std::endl;
    std::cout << "  Box sprite size: " << sprite_width << ":"
              << sprite_height  << std::endl;

    _renderer->AddSprite(sprite_width, sprite_height, box_image_path);

    b2Vec2 pos = Readb2Vec2(&fd);
    _boxes.push_back(new Box(_world, pos.x, pos.y, box_config_path));

    std::cout << " All Boxes: Created! " << std::endl;
  }

  fd.close();
}

World::~World() {
  delete _world;
  delete _track;
}

void World::Update(Event *event) {
  if (event->fullscreen()) {
    _renderer->_graphics->FullscreenOn();
  } else {
    _renderer->_graphics->FullscreenOff();
  }

  // Finding pressed keys and applying it to all the cars
  for (int i = 0; i < _cars.size(); i++) {
    car_control_keys keys = event->ControlKeysState();
    _cars[i]->SetKeys(keys);
    _cars[i]->Loop();
  }

  // Box2D step ( calculating physics )
  _world->Step(_settings->GetTimeStep(),
               _settings->GetVelIterations(),
               _settings->GetPosIterations());
}

void World::Render() {
  for (int i = 0; i < _cars.size(); i++) {
    obj_coordinates coordinates = _cars[i]->GetCoordinates();
    _renderer->SetSpriteCoordinates(i,
                      coordinates.x,
                      coordinates.y,
                      coordinates.angle + 3.14);
  }

  for (int i = _cars.size(); i < _cars.size() + _boxes.size(); i++) {
    obj_coordinates coordinates = _boxes[i - _cars.size()]->GetCoordinates();

    _renderer->SetSpriteCoordinates(i,
                      coordinates.x,
                      coordinates.y,
                      coordinates.angle + 3.14);
  }
  _renderer->Render();
}
