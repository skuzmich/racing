// Copyright (C) 2011 Kuzmich Svyatoslav <svatoslav1@gmail.com>
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PHYSICS_PREDECLS_H_
#define PHYSICS_PREDECLS_H_

#define IS_CAR_BODY     -1
#define IS_WHEEL        1
#define IS_SAND_FIELD   2
#define IS_WALL         3
#define IS_DYNAMIC_OBJ  4
#define IS_SPECIAL      5

#include "Box2D/Box2D.h"

struct ObjData {
    int type;
    int level;
};

struct obj_coordinates {
  float32 x;
  float32 y;
  float32 angle;
};

struct car_control_keys {
  bool left;
  bool right;
  bool up;
  bool down;
};

#include "./track.h"
#include "./car.h"

#endif  // PHYSICS_PREDECLS_H_
