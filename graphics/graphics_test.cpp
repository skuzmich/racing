// Copyright (C) 2011 Horoshenkih Sergey
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "Graphics.h"
#include "event.h"

int main(int argc, char* argv[]) {
  // Some parameters for testing
  int test_w = 400;
  int test_h = 300;
  int test_phys_w = 400;
  int test_phys_h = 300;
  
  Graphics *gr = Graphics::Create(test_w, test_h);
  assert(gr);
  // Initialization of interface between graphics and physics (GPInterface)
  gr->InitGPInterface(test_w, test_h, test_phys_w, test_phys_h);
  gr->LoadBack("./gfx/Track2.png");
  gr->LoadCar(200, 200, "./gfx/car3.png");
  // Variable coordinates of car
  float cX = 200, cY = 150;
  float ang = 0.0;
  gr->SetCarCoordinates(0, cX, cY, ang);
  Event new_event;
  
  while(new_event.running()) {
    new_event.CheckEvents();
    if(new_event.fullscreen()) {
      gr->SetFullscreen(true);
    } else {
        gr->SetFullscreen(false);
      }
    gr->Render();
    ang += 0.01;
    gr->SetCarCoordinates(0, cX, cY, ang);
    
    SDL_Delay(5);
  }
  gr->CleanUp();
  delete gr;
  return 0;
}
