// Copyright (C) 2011 Kuzmich Svyatoslav <svatoslav1@gmail.com>
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PHYSICS_LIB_PREDECLS_H
#define PHYSICS_LIB_PREDECLS_H

#define IS_CAR_BODY     -1
#define IS_WHEEL        1
#define IS_SAND_FIELD   2
#define IS_WALL         3
#define IS_DYNAMIC_OBJ  4
#define IS_SPECIAL      5

struct ObjData{
    int type;
    int level;
};

struct obj_coordinates{
  float x;
  float y;
  float angle;
};

struct car_control_keys{
  bool left;
  bool right;
  bool up;
  bool down;
};

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Box2D/Box2D.h"
#include "track.h"
#include "car.h"
#include "world.h"
#include "settings.h"
#include "renderer.h"

#endif  //  PHYSICS_LIB_PREDECLS_H
