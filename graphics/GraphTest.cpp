// Copyright (C) 2011 Horoshenkih Sergey
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "CGraphics.h"
#include "event.h"
#include "GPInterface.h"

void SetCoords(int *X, int *Y, float *a){
  static int Xcoord = 100, Ycoord = 100;
  static float Angle = 60;
  Xcoord +=1;
  *X = Xcoord;
  Ycoord +=1;
  *Y = Ycoord;
  Angle +=0.1;
  *a = Angle;
}

int main(int argc, char* argv[]) {
  // Some parameters for testing
  int test_w = 1024;
  int test_h = 768;
  int test_phys_w = 400;
  int test_phys_h = 300;
  
  CGraphics *gr = CGraphics::Create(test_w, test_h);
  assert(gr);
  // Variable coordinates of car
  float cX = 200, cY = 150;
  float ang = 0;
  gr->AddCar(100, 100, 60, "./gfx/car1.png");
  // 
  Event new_event;
  // Initialization of interface between graphics and physics (GPInterface)
  GPInterface gpi;
  gpi.Init(test_w, test_h, test_phys_w, test_phys_h);
  
  gr->SetCoordinates(1,
                    gpi.gr_coordinate_x(cX),
                    gpi.gr_coordinate_y(cY),
                    ang);
                    
 // printf("%d %d\n", gpi.gr_coordinate_x(cX), gpi.gr_coordinate_y(cY));
  while(new_event.running()) {
    new_event.CheckEvents();
    gr->Render();
    SDL_Delay(10);
  }
  
  delete gr;
  return 0;
}
