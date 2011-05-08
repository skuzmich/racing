// Copyright (C) 2011 Kuzmich Svyatoslav <svatoslav1@gmail.com>
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PHYSICS_LIB_BEGIN_CONTACTS_H
#define PHYSICS_LIB_BEGIN_CONTACTS_H

void ControlBeginContacts(b2Fixture* fixtureA, b2Fixture* fixtureB);
void BeginWheelAndWheel(b2Fixture* fixtureA, b2Fixture* fixtureB);
void BeginCarBodyAndCarBody(b2Fixture* fixtureA, b2Fixture* fixtureB);
void BeginCarBodyAndWheel(b2Fixture* fixtureA, b2Fixture* fixtureB);
void BeginCarBodyAndWall(b2Fixture* fixtureA, b2Fixture* fixtureB);
void BeginWheelAndWall(b2Fixture* fixtureA, b2Fixture* fixtureB);
void BeginWheelAndSandField(b2Fixture* fixtureA, b2Fixture* fixtureB);
void BeginCarBodyAndSandField(b2Fixture* fixtureA, b2Fixture* fixtureB);

#endif /* PHYSICS_LIB_BEGIN_CONTACTS_H */ 
