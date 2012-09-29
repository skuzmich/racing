// Copyright (C) 2011-2012 Kuzmich Svyatoslav <svatoslav1@gmail.com>
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <iostream>
#include <fstream>
#include <string>

#include "./predecls.h"
#include "../base/fileparser.h"


Car::Car(b2World *world,
         float32 x,
         float32 y,
         Track *track,
         std::string filename)

  :_world(world),
  _track(track),
  _position(b2Vec2(x, y)) {
  LoadFile(filename);

  // Creating body
  _data.type = IS_CAR_BODY;
  _data.level = 15;

  b2BodyDef car_body_def;
  car_body_def.position.Set(x, y);
  car_body_def.type = b2_dynamicBody;

  b2PolygonShape car_poly_shape;
  car_poly_shape.Set(_vertices, 8);

  b2FixtureDef car_fixture_def;
  car_fixture_def.shape = &car_poly_shape;
  car_fixture_def.density = _density;
  car_fixture_def.friction = _friction;
  car_fixture_def.userData = reinterpret_cast<void*>(&_data);

  _body = world->CreateBody(&car_body_def);
  _body->CreateFixture(&car_fixture_def);

  // Creating wheels
  _left_wheel = new Wheel(this,
                          _l_wheel_point.x + x,
                          _l_wheel_point.y + y,
                          false,
                          _track,
                          _wheel_config_file);

  _right_wheel = new Wheel(this,
                           _r_wheel_point.x + x,
                           _r_wheel_point.y + y,
                           false,
                           _track,
                           _wheel_config_file);

  _left_rear_wheel  = new Wheel(this,
                                _l_rear_wheel_point.x + x,
                                _l_rear_wheel_point.y + y,
                                true,
                                _track,
                                _wheel_config_file);

  _right_rear_wheel = new Wheel(this,
                                _r_rear_wheel_point.x + x,
                                _r_rear_wheel_point.y + y,
                                true,
                                _track,
                                _wheel_config_file);
}

Car::~Car() {
  delete _left_wheel;
  delete _right_wheel;
  delete _left_rear_wheel;
  delete _right_rear_wheel;
}

void Car::LoadFile(std::string filename) {
  std::ifstream fd(filename.c_str());

  _horsepowers = ReadFloat(&fd);
  _steer_speed = ReadFloat(&fd);
  _density  =    ReadFloat(&fd);
  _friction =    ReadFloat(&fd);

  _steer_angle_magic1 = ReadFloat(&fd);
  _steer_angle_magic2 = ReadFloat(&fd);
  _steer_angle_magic3 = ReadFloat(&fd);
  _steer_angle_magic4 = ReadFloat(&fd);

  _l_wheel_point      = Readb2Vec2(&fd);
  _r_wheel_point      = Readb2Vec2(&fd);
  _l_rear_wheel_point = Readb2Vec2(&fd);
  _r_rear_wheel_point = Readb2Vec2(&fd);

  _vertices[0] = Readb2Vec2(&fd);
  _vertices[1] = Readb2Vec2(&fd);
  _vertices[2] = Readb2Vec2(&fd);
  _vertices[3] = Readb2Vec2(&fd);
  _vertices[4] = Readb2Vec2(&fd);
  _vertices[5] = Readb2Vec2(&fd);
  _vertices[6] = Readb2Vec2(&fd);
  _vertices[7] = Readb2Vec2(&fd);

  _wheel_config_file = GetLine(&fd);

  fd.close();
  std::cout << "Wheel Config File: " << _wheel_config_file << std::endl;
}

void Car::Loop() {
  _left_wheel->Handling();
  _right_wheel->Handling();
  _left_rear_wheel->Handling();
  _right_rear_wheel->Handling();

  _left_wheel->Driving();
  _right_wheel->Driving();
}


obj_coordinates Car::GetCoordinates() {
  obj_coordinates coordinates;

  coordinates.x = _body->GetPosition().x;
  coordinates.y = _body->GetPosition().y;
  coordinates.angle = _body->GetAngle();

  return coordinates;
}

void Car::SetKeys(car_control_keys keys) {
  float32 steer_angle;

  if (keys.left || keys.right) {
    float32 velocity = _body->GetLinearVelocity().Length();
    // magic
    steer_angle = _steer_angle_magic1 *
                 atan(velocity/_steer_angle_magic2 - _steer_angle_magic3) +
                 _steer_angle_magic4;
  }

  if (keys.left) {
    _steering_angle = -steer_angle;
  }

  if (keys.right) {
    _steering_angle = +steer_angle;
  }

  if (!(keys.right || keys.left))
    _steering_angle = 0;

  if (keys.up)
    _engine_speed = _horsepowers;

  if (keys.down) {
    _breaking = 1;
    _engine_speed = -_horsepowers;
  } else {
    _breaking = 0;
  }

  if (!(keys.down || keys.up))
    _engine_speed = 0;
}

Wheel::Wheel(Car *car,
             float32 x,
             float32 y,
             bool is_rear,
             Track *track,
             std::string config_file) {
  LoadFile(config_file);
  _is_rear = is_rear;
  _track = track;
  _car = car;

  b2BodyDef body_def;
  body_def.position.Set(x, y);
  body_def.type = b2_dynamicBody;
  body_def.linearDamping = _linear_damping;
  body_def.allowSleep = false;

  _body = _car->_world->CreateBody(&body_def);

  b2PolygonShape shape;
  shape.SetAsBox(_size_x, _size_y);

  b2FixtureDef fixture_def;
  fixture_def.shape = &shape;
  fixture_def.density = _density;
  fixture_def.friction = _friction;

  _data.level = 2;
  _data.type = IS_WHEEL;
  fixture_def.userData = reinterpret_cast<void *>(&_data);

  _body->CreateFixture(&fixture_def);

  b2RevoluteJointDef joint_def;
  joint_def.Initialize(_car->_body, _body, _body->GetWorldCenter());

  if (is_rear) {
    joint_def.enableLimit = true;
    joint_def.upperAngle = joint_def.lowerAngle = 0;
  } else {
    joint_def.enableMotor = true;
    joint_def.maxMotorTorque = _max_motor_torque;
  }

  _r_joint = reinterpret_cast<b2RevoluteJoint*>(
             _car->_world->CreateJoint(&joint_def));
}

void Wheel::LoadFile(std::string filename) {
  std::ifstream fd(filename.c_str());

  _size_x = ReadFloat(&fd);
  _size_y = ReadFloat(&fd);

  _max_motor_torque = ReadFloat(&fd);
  _side_damping     = ReadFloat(&fd);
  _linear_damping   = ReadFloat(&fd);
  _density          = ReadFloat(&fd);
  _friction         = ReadFloat(&fd);

  fd.close();
}

void Wheel::Handling() {
  float32 angle = _body->GetAngle();
  b2Vec2 velocity = _body->GetLinearVelocityFromLocalPoint(b2Vec2(0.0f, 0.0f));
  b2Vec2 body_axis = b2Vec2(cos(angle), sin(angle));

  b2Vec2 orthogonal_velocity = b2Dot(velocity, body_axis) * body_axis;
  b2Vec2 parallel_velocity = (velocity - orthogonal_velocity);

  b2Vec2 fric_force = _side_damping * orthogonal_velocity;
  b2Vec2 turn_force = _linear_damping * parallel_velocity;

  _body->ApplyForce(-fric_force + turn_force, _body->GetPosition());
}

void Wheel::Driving() {
  float32 angle = _body->GetAngle();
  b2Vec2 body_axis = _car->_engine_speed * b2Vec2(sin(angle), -cos(angle));
  _body->ApplyForce(body_axis, _body->GetPosition());

  float32 mspeed = _car->_steering_angle - _r_joint->GetJointAngle();
  _r_joint->SetMotorSpeed(mspeed * _car->_steer_speed);
}

