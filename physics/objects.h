// Copyright (C) 2012 Kuzmich Svyatoslav <svatoslav1@gmail.com>
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PHYSICS_OBJECTS_H_
#define PHYSICS_OBJECTS_H_

#include <string>
#include "./predecls.h"

class Box {
 private:
  b2Body *_body;
 public:
  Box(b2World *world,
      float32 x,
      float32 y,
      std::string config_file_path);

  ~Box() {}
  obj_coordinates GetCoordinates();
};

#endif  // PHYSICS_OBJECTS_H_
