// Copyright (C) 2011 Kuzmich Svyatoslav <svatoslav1@gmail.com>
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "Predecls.h"

void ControlEndContacts(b2Fixture* fixtureA, b2Fixture* fixtureB){
  switch (((ObjData*)fixtureA->GetUserData())->type) {
    case IS_WHEEL:
        switch (((ObjData*)fixtureB->GetUserData())->type) {
            case IS_WHEEL:
                EndWheelAndWheel(fixtureA, fixtureB);
                break;
            case IS_CAR_BODY:
                EndCarBodyAndWheel(fixtureB, fixtureA);
                break;
            case IS_SAND_FIELD:
              //  EndWheelAndSandField(fixtureA, fixtureB);
                break;
            case IS_WALL:
              //  EndWheelAndWall(fixtureA, fixtureB);
                break;
        }
        break;
    case IS_CAR_BODY:
        switch (((ObjData*)fixtureB->GetUserData())->type) {
            case IS_WHEEL:
                EndCarBodyAndWheel(fixtureA, fixtureB);
                break;
            case IS_CAR_BODY:
                EndCarBodyAndCarBody(fixtureA, fixtureB);
                break;
            case IS_SAND_FIELD:
               // EndCarBodyAndSandField(fixtureA, fixtureB);
                break;
            case IS_WALL:
               // EndCarBodyAndWall(fixtureA, fixtureB);
                break;
        }
        break;
    case IS_SAND_FIELD:
        switch (((ObjData*)fixtureB->GetUserData())->type) {
            case IS_WHEEL:
                EndWheelAndSandField(fixtureB, fixtureA);
                break;
            case IS_CAR_BODY:
                EndCarBodyAndSandField(fixtureB, fixtureA);
                break;
            case IS_SAND_FIELD:
                break;
            case IS_WALL:
                    break;
        }
        break;
    case IS_WALL:
        switch (((ObjData*)fixtureB->GetUserData())->type) {
            case IS_WHEEL:
                EndWheelAndWall(fixtureB, fixtureA);
                break;
            case IS_CAR_BODY:
                EndCarBodyAndWall(fixtureB, fixtureA);
                break;
            case IS_SAND_FIELD:
                break;
            case IS_WALL:
                    break;
        }
        break;
    default:
        printf("\n!!!\n!!!\nWe Forgot Add This Body!!!\n!!!\n");
    }
}


void EndWheelAndWheel(b2Fixture* fixtureA, b2Fixture* fixtureB){
//    printf("End Wheel And Wheel\n"); 
}

void EndCarBodyAndCarBody(b2Fixture* fixtureA, b2Fixture* fixtureB){
//    printf("End CarBody And CarBody\n"); 
}

void EndCarBodyAndWheel(b2Fixture* fixtureA, b2Fixture* fixtureB){
//    printf("End CarBody And CarBody\n"); 
}

void EndCarBodyAndWall(b2Fixture* fixtureA, b2Fixture* fixtureB){
//    printf("End CarBody And Wall\n"); 
}

void EndWheelAndWall(b2Fixture* fixtureA, b2Fixture* fixtureB){
//    printf("End Wheel And Wall\n"); 
}

void EndWheelAndSandField(b2Fixture* fixtureA, b2Fixture* fixtureB){
//    printf("End Wheel And SandField\n"); 
    fixtureA->GetBody()->SetLinearDamping(1.0f);
    fixtureA->GetBody()->SetAngularDamping(5.0f);
}

void EndCarBodyAndSandField(b2Fixture* fixtureA, b2Fixture* fixtureB){
//    printf("End CarBody And SandField\n"); 
}
