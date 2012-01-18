// opyright (C) 2011-2012 Kuzmich Svyatoslav <svatoslav1@gmail.com>
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PHYSICS_LIB_CAR_H
#define PHYSICS_LIB_CAR_H

class Wheel;
class Track;
struct obj_coordinates;
struct car_control_keys;

class Car {
  private:
    Wheel * _left_wheel;
    Wheel * _right_wheel;
    Wheel * _left_rear_wheel;
    Wheel * _right_rear_wheel;
    
    b2Body * _body;
    b2Vec2 _position;
    b2World *_world;
    Track *_track;
    ObjData _data;

    bool _breaking;
   
    float32 _steering_angle;
    float32 _engine_speed;
    float32 _horsepowers;
    float32 _steer_speed;
    float32 _max_steer_angle;
    
    float32 _density;
    float32 _friction;

    float32 _steer_angle_magic1;
    float32 _steer_angle_magic2;
    float32 _steer_angle_magic3;
    float32 _steer_angle_magic4;

    b2Vec2 _vertices[8];

    b2Vec2 _l_wheel_point;
    b2Vec2 _r_wheel_point;
    b2Vec2 _l_rear_wheel_point;
    b2Vec2 _r_rear_wheel_point;
    std::string _wheel_config_file;

    int32 _sprite_width;
    int32 _sprite_height;
    std::string _image_path;
    
    void LoadFile(std::string filename);

  public:
    
    Car(b2World *world,
        float32 x,
        float32 y,
        Track *track,
        std::string filename);

    ~Car();
    void Loop();
    obj_coordinates GetCoordinates();
    void SetKeys(car_control_keys keys);

    int32 GetSpriteWidth() { return _sprite_width; }
    int32 GetSpriteHeight() { return _sprite_height; }
    std::string GetSpriteImagePath() { return _image_path; }

    friend class Wheel;
};

class Wheel {

  private:
    Car* _car;
    b2Body *_body;
    b2RevoluteJoint* _r_joint;
    Track *_track;
    bool _breaking;
    bool _is_rear;
    ObjData _data;

    float32 _size_x;
    float32 _size_y;

    float32 _max_motor_torque;
    float32 _side_damping;
    float32 _linear_damping;
    float32 _density;
    float32 _friction;
    
    void LoadFile(std::string filename);

  public:   
    Wheel(Car *wheel_car,
        float32 x,
        float32 y, 
        bool is_rear,
        Track *track,
        std::string config_file);
    
    void Handling();
    void Driving();
    friend class Car;
};

#endif /* PHYSICS_LIB_CAR_H */
