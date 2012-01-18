// Copyright (C) 2011 Kuzmich Svyatoslav <svatoslav1@gmail.com>
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PHYSICS_TRACK_H_
#define PHYSICS_TRACK_H_

#include <string>
#include <vector>

class Wall;
class SandField;

class Track {
 private:
  b2World *world;
  float32 k_restitution;
  b2Body* ground;

 public:
  b2Body *sandfield;
  std::vector<b2Fixture*> sensors_list;

  std::vector<Wall*> walls_list;
  std::vector<SandField*> sandfields_list;

  Track(b2World *m_world, std::string track_path);
};

class Wall {
  public:
    ObjData data;
    Wall(float32 x1, float32 y1, float32 x2, float32 y2, b2Body* m_ground) {
      ground = m_ground;
      b2PolygonShape shape;
      b2FixtureDef sd;
      sd.shape = &shape;
      sd.restitution = 0.4f;

      data.type = IS_WALL;
      data.level = 1;
      sd.userData = reinterpret_cast<void*>(&data);

      shape.SetAsEdge(b2Vec2(x1, y1), b2Vec2(x2, y2));
      ground->CreateFixture(&sd);
    }
  private:
    b2Body* ground;
};

class SandField {
  public:
    ObjData data;
    SandField(b2Vec2 *vertices, int size, Track* input_track) {
      track = input_track;
      b2PolygonShape polygon;
      polygon.Set(vertices, size);

      b2FixtureDef sd;
      sd.filter.groupIndex = -1;
      sd.shape = &polygon;
      data.type = IS_SAND_FIELD;
      data.level = 1;
      sd.userData = reinterpret_cast<void*>(&data);
      sd.isSensor = true;
      track->sensors_list.push_back(track->sandfield->CreateFixture(&sd));
    }
  private:
    Track* track;
};


#endif  // PHYSICS_TRACK_H_
