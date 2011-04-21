#ifndef PHYSICS_TEST_RACING_TEST_H
#define PHYSICS_TEST_RACING_TEST_H

#include "Predecls.h"

class RacingTest : public Test
{
public:
    RacingTest()
    {
        m_world->SetGravity(b2Vec2(0.0f, 0.0f));
        
        track = new Track(m_world, "track.txt");
        car = new Car(m_world, 50.0f, 50.0f,track, 2500,10, 3.1415 / 7.0);
        car1 = new Car(m_world, 200.0f, 100.0f,track);
        printf("End RacingTest!\n");
    }

    void BeginContact(b2Contact* contact){
      b2Fixture* fixtureA = contact->GetFixtureA();
      b2Fixture* fixtureB = contact->GetFixtureB();
      ControlBeginContacts(fixtureA, fixtureB);
    }

    void EndContact(b2Contact* contact) {
      b2Fixture* fixtureA = contact->GetFixtureA();
      b2Fixture* fixtureB = contact->GetFixtureB();
      ControlEndContacts(fixtureA, fixtureB);
    }

    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse){
        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();
        if (impulse->normalImpulses[0] > 60){
          //  printf("Boom-Boom\t%f\n",impulse->normalImpulses[0]);
        }
    }

    void MainLoop(){
        static int i = 0;
        car->Loop();
        car1->Loop();
    }

    void Keyboard(unsigned char key)  { 
        switch (key){
            case 'w':
                car->engine_speed = car->horsepowers;
                break;
            case 's':
                car->engine_speed = -car->horsepowers;
                break;
            case 'a':
                car->steering_angle = car->max_steer_angle;
                break;
            case 'd':
                car->steering_angle = -car->max_steer_angle;
                break;
        }
    }

    static Test* Create()
    {
        return new RacingTest;
    }
    Car* car;
    Car* car1;
    Track *track;
};

#endif /* PHYSICS_TEST_RACING_TEST_H */
