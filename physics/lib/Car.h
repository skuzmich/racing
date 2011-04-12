#ifndef PHYSICS_LIB_CAR_H
#define PHYSICS_LIB_CAR_H

class Wheel;
class Track;
struct car_coordinates;
struct car_control_keys;

class Car{
  private:
    Wheel *left_wheel;
    Wheel *right_wheel;
    Wheel *left_rear_wheel;
    Wheel *right_rear_wheel;
    b2Body *body;
    b2Vec2 position;
    b2World *world;
    Track *track;
  public:
    ObjData data;
    float32 steering_angle;
    float32 engine_speed;
    float32 horsepowers;
    float32 steer_speed;
    float32 max_steer_angle;
    Car(b2World *m_world, float32 x, float32 y,Track *m_track);
    ~Car();
    void Loop();
    car_coordinates GetCoordinates();
    void SetKeys(car_control_keys keys);
    friend class Wheel;
};

class Wheel{
  private:
    Car* car;
    b2Body *body;
    b2PrismaticJoint* p_joint;
    b2RevoluteJoint* r_joint;
    Track *track;
  public:
    ObjData data;
    Wheel(Car *wheel_car,
        float32 x,
        float32 y, 
        bool is_rear,
        Track *m_track);

    void DriftingControl();
    void Driving();
    friend class Car;
};

#endif /* PHYSICS_LIB_CAR_H */
