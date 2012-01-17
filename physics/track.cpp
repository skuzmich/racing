// Copyright (C) 2011-2012 Kuzmich Svyatoslav <svatoslav1@gmail.com>
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "predecls.h"
#include "fileparser.h"


Track::Track(b2World *m_world, const char* track_path) {
    k_restitution = 0.4f;
    world = m_world;
    b2BodyDef bd;
    bd.position.Set(0.0f, 0.0f);
    ground = world->CreateBody(&bd);
//    sandfield= world->CreateBody(&bd);
    
    std::ifstream myfile(track_path);
    std::vector<float> vec;
    while ( ! GetNextVectorFromFile<float>(&vec,&myfile, 4))
        walls_list.push_back(new Wall(vec[0]-5.5, vec[1]-5.5, vec[2]-5.5, vec[3]-5.5, ground));
    
    /*
    // Sandfield Creation
    int count = 3;
    while (! GetNextVectorFromFile<float>(&vec,&myfile, count * 2)){
      printf("Sandfield Created!\n");
      b2Vec2 *vertices = (b2Vec2*) malloc(count * sizeof(b2Vec2));
      for (int i = 0; i < count; i++){
        vertices[i].Set(vec[2*i]+5.5,vec[2*i+1]+5.5);
      }
      sandfields_list.push_back(new SandField(vertices,count,this));
    }
    */
}
