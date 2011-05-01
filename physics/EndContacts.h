#ifndef PHYSICS_LIB_END_CONTACTS_H
#define PHYSICS_LIB_END_CONTACTS_H

void ControlEndContacts(b2Fixture* fixtureA, b2Fixture* fixtureB);
void EndWheelAndWheel(b2Fixture* fixtureA, b2Fixture* fixtureB);
void EndCarBodyAndCarBody(b2Fixture* fixtureA, b2Fixture* fixtureB);
void EndCarBodyAndWheel(b2Fixture* fixtureA, b2Fixture* fixtureB);
void EndCarBodyAndWall(b2Fixture* fixtureA, b2Fixture* fixtureB);
void EndWheelAndWall(b2Fixture* fixtureA, b2Fixture* fixtureB);
void EndWheelAndSandField(b2Fixture* fixtureA, b2Fixture* fixtureB);
void EndCarBodyAndSandField(b2Fixture* fixtureA, b2Fixture* fixtureB);

#endif /* PHYSICS_LIB_END_CONTACTS_H */ 
