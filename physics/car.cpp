// Copyright (C) 2011 Kuzmich Svyatoslav <svatoslav1@gmail.com>
// Use of this source code is governed by a Bcar_fixture_def-style license that can be
// found in the LICENSE file.

#include "predecls.h"

Car::Car(b2World *world,
    float32 x,
    float32 y,
    Track *track,
    float32 horsepowers,
    float32 steer_speed,
    float32 max_steer_angle)

  :_steer_speed (steer_speed)
  ,_horsepowers (horsepowers)
  ,_steering_angle (0)
  ,_engine_speed  (0)
  ,_max_steer_angle (max_steer_angle)
  ,_world (world) 
  ,_track (track)
  ,_position (b2Vec2(x,y))
{

  // Creating body
  b2BodyDef car_body_def;
  car_body_def.position.Set(x,y);

  // Creating body shape
  // TODO: make configurable
  b2Vec2 vertices[8];
  vertices[0] = b2Vec2(-3.429f, -5.4864f);
  vertices[1] = b2Vec2(-2.7432f, -6.4008f);
  vertices[2] = b2Vec2(-1.6002f, -6.9723f);
  vertices[3] = b2Vec2(1.6002f, -6.9723f);
  vertices[4] = b2Vec2(2.7432f, -6.4008f);
  vertices[5] = b2Vec2(3.429f, -5.4864f);
  vertices[6] = b2Vec2(3.429f, 5.9436f);
  vertices[7] = b2Vec2(-3.429f, 5.9436f);
   
  b2PolygonShape car_poly_shape;
  car_poly_shape.Set(vertices, 8);

  b2FixtureDef car_fixture_def;
  car_fixture_def.shape = &car_poly_shape;
  car_fixture_def.density = 2.0f;

  _data.type = IS_CAR_BODY;
  _data.level = 15;
  car_fixture_def.userData = (void*) &_data;

  car_body_def.type = b2_dynamicBody;
  
  _body = world->CreateBody(&car_body_def);
  _body->CreateFixture(&car_fixture_def);

  // Creating wheels
  _left_wheel       = new Wheel(this, x - 3.2f, y - 4.343f, false, _track);
  _right_wheel      = new Wheel(this, x + 3.2f, y - 4.343f, false, _track);
  _left_rear_wheel  = new Wheel(this, x - 3.2f, y + 4.343f, true, _track);
  _right_rear_wheel = new Wheel(this, x + 3.2f, y + 4.343f, true, _track);
}

Car::~Car() {
  delete _left_wheel;
  delete _right_wheel;
  delete _left_rear_wheel;
  delete _right_rear_wheel;
}

void Car::Loop() {

  _left_wheel->Handling();
  _right_wheel->Handling();
  _left_rear_wheel->Handling();
  _right_rear_wheel->Handling();
 printf("\n"); 
  _left_wheel->Driving();
  _right_wheel->Driving();

}


car_coordinates Car::GetCoordinates() {
  car_coordinates coordinates;
  b2Vec2 b2coordinates = _body->GetPosition();
  float32 b2angle = _body->GetAngle();
  
  coordinates.x = (float) b2coordinates(0);
  coordinates.y = (float) b2coordinates(1);
  coordinates.angle = (float) b2angle;

  return coordinates;
}

void Car::SetKeys(car_control_keys keys) {
  if (keys.left) {
    float32 velocity = _body->GetLinearVelocity().Length();
    float32 steer_angle = (-1 * ( atan( velocity/18. - 2.))/4.14 + 1./2.)*3.14/5.;
//    printf("Velocity = %6.3f, Steer Angle = %5.3f\n", velocity, steer_angle/3.14);
    _steering_angle = -steer_angle;
  }
 
  if (keys.right) {
    float32 velocity = _body->GetLinearVelocity().Length();
    float32 steer_angle = (-1 * ( atan( velocity/18. - 2.))/4.14 + 1./2. )*3.14/5.;
////    printf("Velocity = %6.3f, Steer Angle = %5.3f\n", velocity, steer_angle/3.14);
    _steering_angle = +steer_angle;
  }
 
  if (! (keys.right || keys.left))
   _steering_angle = 0;

  if (keys.up) 
    _engine_speed = _horsepowers;
  
  if (keys.down) {
    _breaking = 1;
    _engine_speed = -_horsepowers;
  } else {
    _breaking = 0;
  }
  
  if (! (keys.down || keys.up))
    _engine_speed = 0;

}

Wheel::Wheel(Car *car,
    float32 x,
    float32 y, 
    bool is_rear
    ,Track *track){
  _is_rear = is_rear;
  _track = track;
  _car = car;
  
  // Side of the wheel
  // TODO: make it configurable
  float32 size_x = 0.4572f;
  float32 size_y = 1.143f;
  
  b2BodyDef body_def;
  body_def.position.Set(x,y);
  body_def.type = b2_dynamicBody;

  // TODO: make configurable
  body_def.angularDamping = 1.0f;
  body_def.linearDamping = 2.5f;
  body_def.allowSleep = false;
  _body = _car->_world->CreateBody(&body_def);

  b2PolygonShape shape;
  shape.SetAsBox(size_x, size_y);
  b2FixtureDef fixture_def;
  fixture_def.shape = &shape;
  fixture_def.density = 1.0f;
  fixture_def.friction = 0.0f;

  _data.level = 2;
  _data.type = IS_WHEEL;
  fixture_def.userData = (void*) &_data;
  
  _body->CreateFixture(&fixture_def);

    b2RevoluteJointDef joint_def;
    joint_def.Initialize(_car->_body, _body, _body->GetWorldCenter());
   
    if (is_rear) {
      joint_def.enableLimit = true;
      joint_def.upperAngle = joint_def.lowerAngle = 0;
    } else {
      joint_def.enableMotor = true;
      joint_def.maxMotorTorque = 100;
    }

    _r_joint = (b2RevoluteJoint*) _car->_world->CreateJoint(&joint_def);
}

void Wheel::Handling() {

  float32 friction_k = 100.;

  float32 angle = _body->GetAngle();
  b2Vec2 velocity = _body->GetLinearVelocityFromLocalPoint(b2Vec2(0.0f,0.0f));
  b2Vec2 body_axis = b2Vec2(cos(angle),sin(angle));
  b2Vec2 orthogonal_velocity = b2Dot(velocity,body_axis) * body_axis;
  b2Vec2 parallel_velocity = ( velocity - orthogonal_velocity );
  
  float32 kin = velocity.LengthSquared();
  b2Vec2 fric_force = friction_k * orthogonal_velocity;
  b2Vec2 turn_force = ( (fric_force.Length() * orthogonal_velocity.Length() - kin) / parallel_velocity.LengthSquared() ) * parallel_velocity;

  // nan case 
  if ( turn_force.x != turn_force.x ) turn_force.x = 0;
  if ( turn_force.y != turn_force.y ) turn_force.y = 0;

  printf("(%5.3f, %5.3f)", turn_force.x, turn_force.y); 

  _body->ApplyForce( -fric_force , _body->GetPosition());
}

void Wheel::Driving(){
  float32 angle = _body->GetAngle();
  b2Vec2 body_axis = _car->_engine_speed * b2Vec2(sin(angle), -cos(angle));
  _body->ApplyForce(body_axis, _body->GetPosition());
 
  float32 mspeed = _car->_steering_angle - _r_joint->GetJointAngle();
  _r_joint->SetMotorSpeed(mspeed * _car->_steer_speed);
} 

