// Copyright (C) 2011 Kuzmich Svyatoslav <svatoslav1@gmail.com>
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <Predecls.h>

Listener::Listener(){
}

void Listener::BeginContact(b2Contact* contact){
  b2Fixture* fixtureA = contact->GetFixtureA();
  b2Fixture* fixtureB = contact->GetFixtureB();
  //  ControlBeginContacts(fixtureA, fixtureB);
}

void Listener::EndContact(b2Contact* contact) {
  b2Fixture* fixtureA = contact->GetFixtureA();
  b2Fixture* fixtureB = contact->GetFixtureB();
  //  ControlEndContacts(fixtureA, fixtureB);
}

void Listener::PostSolve(const b2Contact* contact, const b2ContactImpulse* impulse){
  const b2Fixture* fixtureA = contact->GetFixtureA();
  const b2Fixture* fixtureB = contact->GetFixtureB();
  //  if (impulse->normalImpulses[0] > 60){
  printf("Boom-Boom\t%f\n",impulse->normalImpulses[0]);
  //  }
}

