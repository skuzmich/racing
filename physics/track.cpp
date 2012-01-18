// Copyright (C) 2011-2012 Kuzmich Svyatoslav <svatoslav1@gmail.com>
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <fstream>
#include <string>
#include <vector>
#include "./predecls.h"
#include "../base/fileparser.h"


Track::Track(b2World *m_world, std::string track_path) {
    k_restitution = 0.4f;
    world = m_world;
    b2BodyDef bd;
    bd.position.Set(0.0f, 0.0f);
    ground = world->CreateBody(&bd);

    std::ifstream fd(track_path.c_str());
    std::vector<float> vec;
    while (!ReadFloatVector(&vec, &fd, 4))
        walls_list.push_back(new Wall(vec[0], vec[1], vec[2], vec[3], ground));

    /*
    // Sandfield Creation
    sandfield= world->CreateBody(&bd);
    int count = 3;
    while (! ReadVector<float>(&vec, &fd, count * 2)){
      printf("Sandfield Created!\n");
      b2Vec2 *vertices = (b2Vec2*) malloc(count * sizeof(b2Vec2));
      for (int i = 0; i < count; i++){
        vertices[i].Set(vec[2*i]+5.5,vec[2*i+1]+5.5);
      }
      sandfields_list.push_back(new SandField(vertices,count,this));
    }
    */
    fd.close();
}
