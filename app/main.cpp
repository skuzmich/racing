#include <stdio.h>

#include "Predecls.h"
#include "CGraphics.h"

int main(int argc, char** argv){
  
  CGraphics *gr = CGraphics::Create(640, 480);
  assert(gr);
  bool Running = true;
  gr->AddCar(100, 100, 60, "./gfx/car1.png");
//gr->AddCar(150, 150, 60, "./gfx/car2.png");
  SDL_Event Event;
  
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
  while(Running) {
    while(SDL_PollEvent(&Event)) {
      if(Event.type == SDL_QUIT) Running = false;
    }
    car_control_keys keys;

    // Some test's
    if (i < 400){
      keys.up = true;
    keys.left = false;
      i++;
      printf ("i = %i \n", i);
    } else {
      if (i % 2) keys.up = false;

      keys.left = true;
    }
    keys.down = false;
    keys.right = false;

    car->SetKeys(keys);
    car->Loop();
    world.Step(timeStep, velIterations, posIterations);
    
    car_coordinates coordinates = car->GetCoordinates();
    gr->SetCoordinates(1,
                      coordinates.x,
                      coordinates.y,
                      coordinates.angle + 3.1415);
    gr->Render();
  }

  delete gr;
  
  delete track;
  delete car;

  return 0;
}
