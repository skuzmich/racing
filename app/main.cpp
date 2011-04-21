#include <stdio.h>

#include "Predecls.h"
#include "Graphics.h"
#include "Event.h"

int main(int argc, char** argv){
  
  Graphics *gr = Graphics::Create(1024, 768);
  assert(gr);
  //bool Running = true;
  
  gr->InitGPInterface(1024, 768, 400, 300);
  gr->AddSprite(0, 0, 0, 32, 17, "./gfx/car1.png");
  //gr->AddSprite(512, 384, 30.0f, 32, 17, "./gfx/car2.png");
    
  // Define the gravity vector.
  b2Vec2 gravity(0.0f, 0.0f);

  // Do we want to let bodies sleep?
  bool doSleep = true;

  // Construct a world object, which will hold and simulate the rigid bodies.
  b2World world(gravity, doSleep);

  float32 timeStep = 1.0f / 60.0f;
  int32 velIterations = 6;
  int32 posIterations = 2;

  Track * track = new Track(&world, "track.txt");
  Car * car = new Car(&world, 300.0f, 300.0f,track);

  int i;
  Event new_event; // new_event.running_ is 'true' by default
  
  while(new_event.running()) {
    // Browse all the events (SDL_Events)
    // In case of quit-event, new_event.running_ sets to 'false'
    new_event.CheckEvents();
    if(new_event.fullscreen()) {
      gr->FullscreenOn();
    } else {
        gr->FullscreenOff();
      }
    // After calling CheckEvents(), new_event.control_keys_state_ sets to actual
    // value according to pressed keys on keyboard
    
    car_control_keys keys;
    
    // Get state of control keys
    keys = new_event.control_keys_state();

    car->SetKeys(keys);
    car->Loop();
    world.Step(timeStep, velIterations, posIterations);
    
    car_coordinates coordinates = car->GetCoordinates();
    gr->SetSpriteCoordinates(0,
                      coordinates.x,
                      coordinates.y,
                      coordinates.angle + 3.1415);
    gr->Render();
  }
  gr->CleanUp();
  delete gr;
  
  delete track;
  delete car;

  return 0;
}
