#ifndef RACING2D_H
#define RACING2D_H

#include <stdio.h>
#include <math.h>
#include "Track.h"
#include "Car.h"
#include "Lib.h"
#include "BeginContacts.h"
#include "EndContacts.h"

class Racing2D : public Test
{
public:
    Racing2D()
    {
        m_world->SetGravity(b2Vec2(0.0f, 0.0f));
        
        track = new Track(m_world, "track.txt");
        car = new Car(m_world, 0.0f, 0.0f,track);
        car1 = new Car(m_world, 2.0f, 2.0f,track);
        printf("End Racing2D!\n");
    }

    void BeginContact(b2Contact* contact){
        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();

     //   for (uint16 i = 0; i < track->sensors_list.size(); i++){
            ControlBeginContacts(fixtureA, fixtureB);
     //       }
            /*
            if ( ((ObjData*)fixtureB->GetUserData())->type == IS_WHEEL )
            if (fixtureA == track->sensors_list[i]){
                    // Should add some other dynamic objects there
                    fixtureB->GetBody()->SetLinearDamping(30.0f);
                    fixtureB->GetBody()->SetAngularDamping(30.0f);
                }

                if ( ((ObjData*)fixtureA->GetUserData())->type == IS_WHEEL ){
                    if (fixtureB == track->sensors_list[i]){
                        fixtureA->GetBody()->SetLinearDamping(30.0f);
                        fixtureA->GetBody()->SetAngularDamping(30.0f);
                    }
                }*/
       // }
    }

    void EndContact(b2Contact* contact) {
    //    printf("End\n");
        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();
     //   for (uint16 i = 0; i < track->sensors_list.size(); i++){
            ControlEndContacts(fixtureA, fixtureB);
     //   }
         /*   if ( ((ObjData*)fixtureB->GetUserData())->type == IS_WHEEL )
                if (fixtureA == track->sensors_list[i]){
                    // Should add some other dynamic objects there
                    fixtureB->GetBody()->SetLinearDamping(1.0f);
                    fixtureB->GetBody()->SetAngularDamping(5.0f);
                }

                if ( ((ObjData*)fixtureA->GetUserData())->type == IS_WHEEL ){
                    if (fixtureB == track->sensors_list[i]){
                        fixtureA->GetBody()->SetLinearDamping(1.0f);
                        fixtureA->GetBody()->SetAngularDamping(5.0f);
                    }
                }
        }*/
    }

    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse){
        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();
//        printf("T1=%i " ,((ObjData*) (fixtureA->GetUserData()))->type);
//        printf("T2=%i\n" ,((ObjData*) (fixtureB->GetUserData()))->type);
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
        return new Racing2D;
    }
    Car* car;
    Car* car1;
    Track *track;
};

#endif /* Racing 2D */
