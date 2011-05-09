// Copyright (C) 2011 Kuzmich Svyatoslav <svatoslav1@gmail.com>
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "Predecls.h"


void ControlBeginContacts(b2Fixture* fixtureA, b2Fixture* fixtureB){
  switch (((ObjData*)fixtureA->GetUserData())->type) {
    case IS_WHEEL:
        switch (((ObjData*)fixtureB->GetUserData())->type) {
            case IS_WHEEL:
                BeginWheelAndWheel(fixtureA, fixtureB);
                break;
            case IS_CAR_BODY:
                BeginCarBodyAndWheel(fixtureB, fixtureA);
                break;
            case IS_SAND_FIELD:
            //    BeginWheelAndSandField(fixtureA, fixtureB);
                break;
            case IS_WALL:
            //    BeginWheelAndWall(fixtureA, fixtureB);
                break;
        }
        break;
    case IS_CAR_BODY:
        switch (((ObjData*)fixtureB->GetUserData())->type) {
            case IS_WHEEL:
                BeginCarBodyAndWheel(fixtureA, fixtureB);
                break;
            case IS_CAR_BODY:
                BeginCarBodyAndCarBody(fixtureA, fixtureB);
                break;
            case IS_SAND_FIELD:
            //    BeginCarBodyAndSandField(fixtureA, fixtureB);
                break;
            case IS_WALL:
            //    BeginCarBodyAndWall(fixtureA, fixtureB);
                break;
        }
        break;
    case IS_SAND_FIELD:
        switch (((ObjData*)fixtureB->GetUserData())->type) {
            case IS_WHEEL:
                BeginWheelAndSandField(fixtureB, fixtureA);
                break;
            case IS_CAR_BODY:
                BeginCarBodyAndSandField(fixtureB, fixtureA);
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
                BeginWheelAndWall(fixtureB, fixtureA);
                break;
            case IS_CAR_BODY:
                BeginCarBodyAndWall(fixtureB, fixtureA);
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


void BeginWheelAndWheel(b2Fixture* fixtureA, b2Fixture* fixtureB){
//    printf("Begin Wheel And Wheel\n"); 
}

void BeginCarBodyAndCarBody(b2Fixture* fixtureA, b2Fixture* fixtureB){
//   printf("Begin CarBody And CarBody\n"); 
}

void BeginCarBodyAndWheel(b2Fixture* fixtureA, b2Fixture* fixtureB){
//    printf("Begin CarBody And CarBody\n"); 
}

void BeginCarBodyAndWall(b2Fixture* fixtureA, b2Fixture* fixtureB){
//    printf("Begin CarBody And Wall\n"); 
}

void BeginWheelAndWall(b2Fixture* fixtureA, b2Fixture* fixtureB){
//    printf("Begin Wheel And Wall\n"); 
}

void BeginWheelAndSandField(b2Fixture* fixtureA, b2Fixture* fixtureB){
    fixtureA->GetBody()->SetLinearDamping(25.0f);
    fixtureA->GetBody()->SetAngularDamping(0.1f);
//    printf("Begin Wheel And SandField\n"); 
}

void BeginCarBodyAndSandField(b2Fixture* fixtureA, b2Fixture* fixtureB){
//    printf("Begin CarBody And SandField\n"); 
}
