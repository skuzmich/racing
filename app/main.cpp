// Copyright (C) 2011 Kuzmich Svyatoslav <svatoslav1@gmail.com>
// Copyright (C) 2011 Horoshenkih Sergey
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <stdio.h>

#include "Predecls.h"
#include "Graphics.h"
#include "Event.h"

int main(int argc, char** argv){
  
  Graphics *gr = Graphics::Create(800, 600);
  assert(gr);
  //bool Running = true;
  gr->LoadBack("./gfx/Track.png");
  gr->LoadCar(40, 40, "./gfx/car3.png");
  //gr->AddSprite(512, 384, 30.0f, 32, 17, "./gfx/car2.png");
    
  // Define the gravity vector.
  b2Vec2 gravity(0.0f, 0.0f);

  // Do we want to let bodies sleep?
  bool doSleep = true;

  // Construct a world object, which will hold and simulate the rigid bodies.
  b2World world(gravity, doSleep);
  float32 timeStep = 1.0f / 30.0f;
  int32 velIterations = 8;
  int32 posIterations = 3;

  Track * track = new Track(&world, "track.txt");
  Car * car = new Car(&world, 50.0f, 50.0f,track, 4700, 200, 3.1415f / 10.0f);
  Listener *contact_listener = new Listener();
  world.SetContactListener(contact_listener);

  Event new_event; // new_event.running_ is 'true' by default
  
  while(new_event.running()) {
    // Browse all the events (SDL_Events)
    // In case of quit-event, new_event.running_ sets to 'false'
    new_event.CheckEvents();
    if(new_event.fullscreen()) {
      gr->SetFullscreen(true);
    } else {
        gr->SetFullscreen(false);
      }
    // After calling CheckEvents(), new_event.control_keys_state_ sets to actual
    // value according to pressed keys on keyboard
    
    car_control_keys keys;
    
    // Get state of control keys
    keys = new_event.control_keys_state();

    car->SetKeys(keys);
    car->Loop();

    SDL_Delay(10);
    world.SetWarmStarting(1);
    world.SetContinuousPhysics(0);
    world.Step(timeStep, velIterations, posIterations);
    
    car_coordinates coordinates = car->GetCoordinates();
    gr->SetCarCoordinates(0,
                      coordinates.x,
                      coordinates.y,
                      coordinates.angle + 3.14);
    gr->Render();
  }
  gr->CleanUp();
  delete gr;
  
  delete track;
  delete car;

  return 0;
}
