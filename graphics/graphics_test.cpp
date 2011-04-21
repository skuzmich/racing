#include "Graphics.h"
#include "Event.h"

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
  
  Graphics *gr = Graphics::Create(test_w, test_h);
  assert(gr);
  // Initialization of interface between graphics and physics (GPInterface)
  gr->InitGPInterface(test_w, test_h, test_phys_w, test_phys_h);
  gr->AddSprite(512, 384, 30.0f, 32, 17, "./gfx/car1.png");
  gr->AddSprite(512, 384, 30.0f, 32, 17, "./gfx/car2.png");
  // Variable coordinates of car
  float cX = 20, cY = 15;
  float ang = 0;
  gr->SetSpriteCoordinates(0, cX, cY, ang);
  gr->SetSpriteCoordinates(1, cX+50, cY, ang);
  // 
  Event new_event;
  
 // printf("%d %d\n", gpi.gr_coordinate_x(cX), gpi.gr_coordinate_y(cY));
  while(new_event.running()) {
    new_event.CheckEvents();
    if(new_event.fullscreen()) {
      gr->FullscreenOn();
    } else {
        gr->FullscreenOff();
      }
    gr->Render();
    cX += 0.1;
    cY += 0.1;
    ang += 0.01;
    gr->SetSpriteCoordinates(0, cX, cY, ang);
    gr->SetSpriteCoordinates(1, cX+50, cY, ang);
    SDL_Delay(5);
  }
  gr->CleanUp();
  delete gr;
  return 0;
}
