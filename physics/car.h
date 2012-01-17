// Copyright (C) 2011 Kuzmich Svyatoslav <svatoslav1@gmail.com>
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PHYSICS_LIB_CAR_H
#define PHYSICS_LIB_CAR_H

class Wheel;
class Track;
struct car_coordinates;
struct car_control_keys;

class Car{
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
    b2Vec2 _vertices[8];

    b2Vec2 _l_wheel_point;
    b2Vec2 _r_wheel_point;
    b2Vec2 _l_rear_wheel_point;
    b2Vec2 _r_rear_wheel_point;

  public:
    
    Car(b2World *world,
        float32 x,
        float32 y,
        Track *track,
        float32 horsepowers = 1400,
        float32 steer_speed = 10,
        float32 max_steer_angle = 3.1415 / 5.);

    ~Car();
    void Loop();
    car_coordinates GetCoordinates();
    void SetKeys(car_control_keys keys);
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
    float32 _max_motor_torque;
    float32 _linear_damping;
    float32 _side_damping;
    float32 _density;
    float32 _friction;
    
    float32 _size_x;
    float32 _size_y;
	

  public:   
    Wheel(Car *wheel_car,
        float32 x,
        float32 y, 
        bool is_rear,
        Track *track);
    
    void Handling();
    void Driving();
    friend class Car;
};

#endif /* PHYSICS_LIB_CAR_H */
