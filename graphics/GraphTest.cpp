#include "CGraphics.h"

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
  CGraphics *gr = CGraphics::Create(640, 480);
  assert(gr);
  int cX, cY;
  float ang;
  bool Running;
  gr->AddCar(100, 100, 60, "./gfx/car1.png");
  gr->AddCar(150, 150, 60, "./gfx/car2.png");
  SDL_Event Event;

  while(Running) {
    while(SDL_PollEvent(&Event)) {
      if(Event.type == SDL_QUIT) Running = false;
    }
    SetCoords(&cX, &cY, &ang);
    gr->SetCoordinates(1, cX, cY, ang);
    gr->SetCoordinates(2, cX+50, cY+50, ang);
    gr->Render();
    SDL_Delay(10);
  }
  
  delete gr;
  return 0;
}
