// Copyright (C) 2011 Horoshenkih Sergey
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "Graphics.h"
#include "Event.h"

int main(int argc, char* argv[]) {
  // Some parameters for testing
  int test_w = 800;
  int test_h = 600;
  Graphics *gr = Graphics::Create(test_w, test_h);
  assert(gr);
  gr->LoadBack("./gfx/Track2.png");
  gr->LoadCar(100, 100, "./gfx/car3.png");
  // Variable coordinates of car
  //float cX = 200, cY = 150;
  float ang = 0.0;
  
  Event new_event;
  
  while(new_event.running()) {
    new_event.CheckEvents();
    if(new_event.fullscreen()) {
      gr->SetFullscreen(true);
    } else {
        gr->SetFullscreen(false);
      }
    gr->SetCarCoordinates(0, 200, 150, ang);
    gr->Render();
    ang += 0.01;
   
    SDL_Delay(5);
  }
  gr->CleanUp();
  delete gr;
  return 0;
}
