#include "Predecls.h"

Car::Car(b2World *m_world,
         float32 x,
         float32 y,
         Track *m_track,
         float32 new_horsepowers,
         float32 new_steer_speed,
         float32 new_max_steer_angle){
  steer_speed = new_steer_speed;
  horsepowers = new_horsepowers;
  steering_angle = 0;
  engine_speed = 0;
  max_steer_angle = new_max_steer_angle;
  world = m_world; 
  track = m_track;
  position = b2Vec2(x,y);

  b2BodyDef car_body_def;
  car_body_def.position.Set(x,y);

  b2Vec2 vertices[8];
  
  /*
  vertices[0] = b2Vec2(-1.5f, -2.4f);
  vertices[1] = b2Vec2(-1.2f, -2.8f);
  vertices[2] = b2Vec2(-0.7f, -3.0f);
  vertices[3] = b2Vec2(0.7f, -3.0f);
  vertices[4] = b2Vec2(1.2f, -2.8f);
  vertices[5] = b2Vec2(1.5f, -2.4f);
  vertices[6] = b2Vec2(1.5f, 2.6f);
  vertices[7] = b2Vec2(-1.5f, 2.6f);
  */
  
  vertices[0] = b2Vec2(-1.5f * 2.286, -2.4f*2.286);
  vertices[1] = b2Vec2(-1.2f*2.286, -2.8f*2.286);
  vertices[2] = b2Vec2(-0.7f*2.286, -3.05*2.286);
  vertices[3] = b2Vec2(0.7f*2.286, -3.0f*2.286);
  vertices[4] = b2Vec2(1.2f*2.286, -2.8f*2.286);
  vertices[5] = b2Vec2(1.5f*2.286, -2.4f*2.286);
  vertices[6] = b2Vec2(1.5f*2.286, 2.6f*2.286);
  vertices[7] = b2Vec2(-1.5f*2.286, 2.6f*2.286);
   
  b2PolygonShape car_poly_shape;
  car_poly_shape.Set(vertices, 8);

  b2FixtureDef sd;
  sd.shape = &car_poly_shape;
  sd.density = 2.0f;

  data.type = IS_CAR_BODY;
  data.level=15;
  sd.userData = (void*) &data;

  car_body_def.type = b2_dynamicBody;
  // car_body_def.angularDamping = 1.1f;
  // car_body_def.linearDamping = 1.1f;

  body = world->CreateBody(&car_body_def);
  body->CreateFixture(&sd);

  left_wheel = new Wheel(this,x - 1.4f*2.286, y - 1.9f*2.286, false,track);
  right_wheel = new Wheel(this,x + 1.4f*2.286, y - 1.9f*2.286, false,track);
  left_rear_wheel = new Wheel(this,x - 1.4f*2.286, y + 1.9f*2.286, true,track);
  right_rear_wheel = new Wheel(this,x + 1.4f*2.286, y + 1.9f*2.286, true,track);
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
    engine_speed = +horsepowers;
  
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
  rear = is_rear;
  track = m_track;
  car = wheel_car;
  float32 size_x = 0.2f*2.286;
  float32 size_y = 0.5f*2.286;
  b2BodyDef bd;
  bd.position.Set(x,y);
  bd.type = b2_dynamicBody;
  bd.angularDamping = 2.0f;
  bd.linearDamping = 5.5f;

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

    b2RevoluteJointDef joint_def;
    joint_def.Initialize(car->body,body,body->GetWorldCenter());
   
    if (is_rear){
    joint_def.enableLimit = true;
    joint_def.upperAngle = joint_def.lowerAngle = 0;
    
    } else {
    joint_def.enableMotor = true;
    joint_def.maxMotorTorque = 100;
    }

    r_joint = (b2RevoluteJoint*) car->world->CreateJoint(&joint_def);
}

void Wheel::DriftingControl(){
  b2Vec2 velocity = body->GetLinearVelocityFromLocalPoint(b2Vec2(0.0f,0.0f));
  float32 angle = body->GetAngle();
  b2Vec2 body_axis = b2Vec2(7*cos(angle),7*sin(angle));
  b2Vec2 orthogonal_velocity = b2Dot(velocity,body_axis) * body_axis; 
  velocity = velocity - orthogonal_velocity;
  //body->SetLinearVelocity(velocity);
  body->ApplyForce(b2Vec2(0.0f,0.0f) - orthogonal_velocity,body->GetPosition());
}

void Wheel::Driving(){
  float32 angle = body->GetAngle();
  b2Vec2 body_axis = car->engine_speed * b2Vec2(sin(angle),-cos(angle));
  body->ApplyForce(body_axis,body->GetPosition());
  float32 mspeed = car->steering_angle - r_joint->GetJointAngle();
  r_joint->SetMotorSpeed(mspeed * car->steer_speed);
} 

