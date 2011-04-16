#include <stdio.h>

#include "Predecls.h"
#include "CGraphics.h"
#include "Event.h"
#include "GPInterface.h"

int main(int argc, char** argv){
 
  int window_w = 640;
  int window_h = 480;

  CGraphics *gr = CGraphics::Create(window_w, window_h);
  assert(gr);
  //bool Running = true;
  
  gr->AddCar(100, 100, 60, "./gfx/car1.png");
    
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
  Car * car = new Car(&world, 50.0f, 50.0f,track,1000,100, 3.1415 / 6.0);

  int i;
  Event new_event; // new_event.running_ is 'true' by default
  
  GPInterface gpi;
  gpi.Init(window_w, window_h, 400,300);

  while(new_event.running()) {
    // Browse all the events (SDL_Events)
    // In case of quit-event, new_event.running_ sets to 'false'
    new_event.CheckEvents();
    // After calling CheckEvents(), new_event.control_keys_state_ sets to actual
    // value according to pressed keys on keyboard
    
    car_control_keys keys;
    
    // Get state of control keys
    keys = new_event.control_keys_state();

    car->SetKeys(keys);
    car->Loop();
    world.Step(timeStep, velIterations, posIterations);
    
    car_coordinates coordinates = car->GetCoordinates();
    gr->SetCoordinates(1,
                      gpi.gr_coordinate_x(coordinates.x),
                      gpi.gr_coordinate_y(coordinates.y),
                      -coordinates.angle + 3.1415);
    gr->Render();
  }

  delete gr;
  
  delete track;
  delete car;

  return 0;
}
