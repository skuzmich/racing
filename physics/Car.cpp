#include "Predecls.h"

Car::Car(b2World *m_world,
         float32 x,
         float32 y,
         Track *m_track,
         float32 new_horsepowers,
         float32 new_steer_speed,
         float32 new_max_steer_angle){

  // Initializing start values
  steer_speed = new_steer_speed;
  horsepowers = new_horsepowers;
  steering_angle = 0;
  engine_speed = 0;
  max_steer_angle = new_max_steer_angle;
  world = m_world; 
  track = m_track;
  position = b2Vec2(x,y);

  // Creating body
  b2BodyDef car_body_def;
  car_body_def.position.Set(x,y);

  // Creating body shape
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

  b2FixtureDef sd;
  sd.shape = &car_poly_shape;
  sd.density = 2.0f;

  data.type = IS_CAR_BODY;
  data.level=15;
  sd.userData = (void*) &data;

  car_body_def.type = b2_dynamicBody;
  
  body = world->CreateBody(&car_body_def);
  body->CreateFixture(&sd);

  // Creating wheels
  left_wheel = new Wheel(this,x - 3.2f, y - 4.343f, false,track);
  right_wheel = new Wheel(this,x + 3.2f, y - 4.343f, false,track);
  left_rear_wheel = new Wheel(this,x - 3.2f, y + 4.343f, true,track);
  right_rear_wheel = new Wheel(this,x + 3.2f, y + 4.343f, true,track);
}

Car::~Car(){
  delete left_wheel;
  delete right_wheel;
  delete left_rear_wheel;
  delete right_rear_wheel;
}

void Car::Loop(){
  left_wheel->Handling();
  right_wheel->Handling();
  left_rear_wheel->Handling();
  right_rear_wheel->Handling();
  
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
  
  if (keys.down){
    breaking = 1;
    engine_speed = -horsepowers;
  } else {
    breaking = 0;
  }
  
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
  float32 size_x = 0.4572f;
  float32 size_y = 1.143f;
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

void Wheel::Handling(){
  breaking = car->breaking;

  if (breaking){
    body->SetLinearDamping(15.5f);
  } else {
    body->SetLinearDamping(5.5f);
  }

  b2Vec2 velocity = body->GetLinearVelocityFromLocalPoint(b2Vec2(0.0f,0.0f));
  float32 angle = body->GetAngle();
  b2Vec2 body_axis = b2Vec2(5*cos(angle),5*sin(angle));
  b2Vec2 orthogonal_velocity = b2Dot(velocity,body_axis) * body_axis;
  
  velocity = velocity - orthogonal_velocity;
  body->ApplyForce(b2Vec2(0.0f,0.0f) - orthogonal_velocity,body->GetPosition());
}

void Wheel::Driving(){
  float32 angle = body->GetAngle();
  b2Vec2 body_axis = car->engine_speed * b2Vec2(sin(angle),-cos(angle));
  body->ApplyForce(body_axis,body->GetPosition());
  float32 mspeed = car->steering_angle - r_joint->GetJointAngle();
  r_joint->SetMotorSpeed(mspeed * car->steer_speed);
} 

