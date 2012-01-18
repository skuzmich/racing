// Copyright (C) 2012 Kuzmich Svyatoslav <svatoslav1@gmail.com>
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <iostream>
#include <fstream>
#include <string>

#include "./predecls.h"
#include "./objects.h"
#include "../base/fileparser.h"

Box::Box(b2World* world,
         float32 x,
         float32 y,
         std::string config_file_path) {
  std::ifstream fd(config_file_path.c_str());
  float32 width  = ReadFloat(&fd);
  float32 height = ReadFloat(&fd);
  float32 linear_damping = ReadFloat(&fd);
  float32 angular_damping = ReadFloat(&fd);
  fd.close();

  b2BodyDef body_def;
  body_def.position.Set(x, y);
  body_def.type = b2_dynamicBody;
  body_def.linearDamping = linear_damping;
  body_def.angularDamping = angular_damping;

  _body = world->CreateBody(&body_def);

  b2PolygonShape shape;
  shape.SetAsBox(width, height);

  b2FixtureDef fixture_def;
  fixture_def.shape = &shape;
  fixture_def.density = 0.1;
  fixture_def.friction = 0.1;

  _body->CreateFixture(&fixture_def);
}

obj_coordinates Box::GetCoordinates() {
  obj_coordinates coordinates;

  coordinates.x = _body->GetPosition().x;
  coordinates.y = _body->GetPosition().y;
  coordinates.angle = _body->GetAngle();

  return coordinates;
}
