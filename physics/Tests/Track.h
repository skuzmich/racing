#ifndef TRACK_H
#define TRACK_H

#include <stdio.h>
#include "Lib.h"
#include <vector>

class Wall;
class SandField;

class Track{
private:
    b2World *world;
    float32 k_restitution;
    b2Body* ground;
    
public:
    
    b2Body *sandfield;
    std::vector<b2Fixture*> sensors_list;

    std::vector<Wall*> walls_list;
    std::vector<SandField*> sandfields_list;
    
    Track(b2World *m_world, char* track_path );
};

class Wall{
  public:
    ObjData data;
    Wall(float32 x1,float32 y1,float32 x2,float32 y2,b2Body* m_ground){
        ground = m_ground;
        b2PolygonShape shape;
        b2FixtureDef sd;
        sd.shape = &shape;
        sd.restitution = 0.4f;
        
        data.type=IS_WALL;
        data.level=1;
        sd.userData = (void*) &data;

        shape.SetAsEdge(b2Vec2(x1, y1), b2Vec2(x2, y2));
        ground->CreateFixture(&sd);
    }
private:
    b2Body* ground;
};

class SandField{
  public:
    ObjData data;
    SandField(b2Vec2 *vertices, int size, Track* input_track){
        track = input_track;
        b2PolygonShape polygon;
        polygon.Set(vertices, size);

        b2FixtureDef sd;
        sd.filter.groupIndex = -1;
        sd.shape = &polygon;
        data.type = IS_SAND_FIELD;
        data.level = 1;
        sd.userData = (void*) &data;

        sd.isSensor = true;

        track->sensors_list.push_back(track->sandfield->CreateFixture(&sd));
    }
  private:
    Track* track;
};

Track::Track(b2World *m_world, char* track_path){
    k_restitution = 0.4f;
    world = m_world;
    b2BodyDef bd;
    bd.position.Set(0.0f, 0.0f);
    ground = world->CreateBody(&bd);
    sandfield= world->CreateBody(&bd);
    
    std::ifstream myfile (track_path);
    std::vector<float> vec;
    while ( ! GetNextVectorFromFile<float>(&vec,&myfile, 4))
        walls_list.push_back(new Wall(vec[0], vec[1], vec[2],vec[3],ground));
    
    int count = 3;
    while (! GetNextVectorFromFile<float>(&vec,&myfile, count * 2)){
        b2Vec2 *vertices = (b2Vec2*) malloc(count * sizeof(b2Vec2));
        for (int i = 0; i < count; i++){
            vertices[i].Set(vec[2*i],vec[2*i+1]);
            printf("==%f %f\n", vec[2*i], vec[2*i+1]);
        }
        sandfields_list.push_back(new SandField(vertices,count,this));
    }
}

#endif /* TRACK_H */ 