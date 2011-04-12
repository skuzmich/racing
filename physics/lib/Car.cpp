#include "Predecls.h"

Car::Car(b2World *m_world, float32 x, float32 y,Track *m_track){
  steer_speed = 20;
  horsepowers = 1000;
  steering_angle = 0;
  engine_speed = 0;
  max_steer_angle = 3.1415f / 20.0f;
  world = m_world; 
  track = m_track;
  position = b2Vec2(x,y);

  b2BodyDef car_body_def;
  car_body_def.position.Set(x,y);

  b2Vec2 vertices[8];
  vertices[0] = b2Vec2(-1.5f, -2.4f);
  vertices[1] = b2Vec2(-1.2f, -2.8f);
  vertices[2] = b2Vec2(-0.7f, -3.0f);
  vertices[3] = b2Vec2(0.7f, -3.0f);
  vertices[4] = b2Vec2(1.2f, -2.8f);
  vertices[5] = b2Vec2(1.5f, -2.4f);
  vertices[6] = b2Vec2(1.5f, 2.6f);
  vertices[7] = b2Vec2(-1.5f, 2.6f);

  b2PolygonShape car_poly_shape;
  car_poly_shape.Set(vertices, 8);

  b2FixtureDef sd;
  sd.shape = &car_poly_shape;
  sd.density = 2.0f;

  data.type = IS_CAR_BODY;
  data.level=15;
  sd.userData = (void*) &data;

  car_body_def.type = b2_dynamicBody;
  car_body_def.angularDamping = 5.0f;
  car_body_def.linearDamping = 3.1f;

  body = world->CreateBody(&car_body_def);
  body->CreateFixture(&sd);

  left_wheel = new Wheel(this,x - 1.4f, y - 1.9f, false,track);
  right_wheel = new Wheel(this,x + 1.4f, y - 1.9f, false,track);
  left_rear_wheel = new Wheel(this,x - 1.4f, y + 1.9f, true,track);
  right_rear_wheel = new Wheel(this,x + 1.4f, y + 1.9f, true,track);
}

Car::~Car(){
  delete left_wheel;
  delete right_wheel;
  delete left_rear_wheel;
  delete right_rear_wheel;
}

void Car::Loop(){
  left_wheel->DriftingControl();
  right_wheel->DriftingControl();
  left_rear_wheel->DriftingControl();
  right_rear_wheel->DriftingControl();

  left_wheel->Driving();
  right_wheel->Driving();
}

car_coordinates Car::GetCoordinates(){
  car_coordinates coordinates;
  b2Vec2 b2coordinates = body->GetPosition();
  float32 b2angle = body->GetAngle();
  
  coordinates.x = (float) b2coordinates(0);
  coordinates.y = (float) b2coordinates(1);
  coordinates.angle = (float) b2angle;

  return coordinates;
}

void Car::SetKeys(car_control_keys keys){
  if (keys.left)
    steering_angle = -max_steer_angle;
  
  if (keys.right)
    steering_angle = +max_steer_angle;
  
  if (! (keys.right || keys.left))
    steering_angle = 0;

  if (keys.up)
    engine_speed = horsepowers;
  
  if (keys.down)
    engine_speed = -horsepowers;
  
  if (! (keys.down || keys.up))
    engine_speed = 0;

}

Wheel::Wheel(Car *wheel_car,
    float32 x,
    float32 y, 
    bool is_rear
    ,Track *m_track){
  track = m_track;
  car = wheel_car;
  float32 size_x = 0.2f;
  float32 size_y = 0.5f;
  b2BodyDef bd;
  bd.position.Set(x,y);
  bd.type = b2_dynamicBody;
  bd.angularDamping = 5.0f;
  bd.linearDamping = 0.1f;

  bd.allowSleep = false;
  body = car->world->CreateBody(&bd);
  b2PolygonShape shape;
  shape.SetAsBox(size_x, size_y);
  b2FixtureDef fd;
  fd.shape = &shape;
  fd.density = 1.0f;
  fd.friction = 0.0f;
  data.level = 2;
  data.type = IS_WHEEL;

  fd.userData = (void*) &data;
  body->CreateFixture(&fd);

  if (is_rear){
    b2DistanceJointDef jointDef;
    jointDef.Initialize(car->body, body, body->GetWorldCenter(),body->GetWorldCenter());
    jointDef.collideConnected = true;
    b2DistanceJoint* d_joint = (b2DistanceJoint*) car->world->CreateJoint(&jointDef);
    b2PrismaticJointDef joint_def;
    b2Vec2 worldAxis(0.0f, 0.0f);
    joint_def.Initialize(car->body, body, body->GetWorldCenter(), worldAxis);
    joint_def.enableLimit = true;
//  joint_def.lowerTranslation = -0.0001f;
//  joint_def.upperTranslation = 0.0001f;
    p_joint = (b2PrismaticJoint*) car->world->CreateJoint(&joint_def);
  } else {
    b2RevoluteJointDef joint_def;
    joint_def.Initialize(car->body,body,body->GetWorldCenter());
    joint_def.enableMotor = true;
    joint_def.maxMotorTorque = 100;
    r_joint = (b2RevoluteJoint*) car->world->CreateJoint(&joint_def);
  }
}

void Wheel::DriftingControl(){
  b2Vec2 velocity = body->GetLinearVelocityFromLocalPoint(b2Vec2(0.0f,0.0f));
  float32 angle = body->GetAngle();
  b2Vec2 body_axis = b2Vec2(cos(angle)*0.5,sin(angle)*0.5); 
  b2Vec2 orthogonal_velocity = b2Dot(velocity,body_axis) * body_axis; 
  velocity = velocity - orthogonal_velocity;
  body->SetLinearVelocity(velocity);
}

void Wheel::Driving(){
  float32 angle = body->GetAngle();
  b2Vec2 body_axis = car->engine_speed * b2Vec2(sin(angle),-cos(angle));
  body->ApplyForce(body_axis,body->GetPosition());
  float32 mspeed = car->steering_angle - r_joint->GetJointAngle();
  r_joint->SetMotorSpeed(mspeed * car->steer_speed);
} 

