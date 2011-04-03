#include "CGraphics.h"

CCar::CCar() {
  x_coord_ = 0;
  y_coord_ = 0;
  angle_ = 0.0f;
  surf_car_ = NULL;
  car_texture_ = 0;
  height_ = 0;
  width_ = 0;
  initialized = true;
}

CCar::CCar(int X, int Y, float ang, const char *pict) {
  surf_car_ = IMG_Load(pict);
  
  if(surf_car_ == NULL) {
    initialized = false;
  } else {
    
    if(SurfaceToGLTexture(surf_car_, &car_texture_)) {
      x_coord_ = X;
      y_coord_ = Y;
      angle_ = ang;
      height_ = surf_car_->h;
      width_ = surf_car_->w;
      initialized = true;
    } else {
      initialized = false;
    }
    
  }
}

CCar::~CCar(){
  SDL_FreeSurface(surf_car_);
}

void CCar::SetCenter(int X, int Y){
  x_coord_ = X;
  y_coord_ = Y;
}

void CCar::SetAngle(double fi){
  angle_ = fi;
}

int CCar::GetXCoordinate(int X, int Y){
  // I need a big picture to describe these formulas...
  assert(X >= 0);
  assert(Y >= 0);
  assert(X <= 1);
  assert(Y <= 1);

  if((X == 0)&&(Y == 0)){
    return (x_coord_ - (height_/2)*sin(angle_) - (width_/2)*cos(angle_));
  }
  if((X == 0)&&(Y == 1)){
    return (x_coord_ + (height_/2)*sin(angle_) - (width_/2)*cos(angle_));
  }
  if((X == 1)&&(Y == 0)){
    return (x_coord_ - (height_/2)*sin(angle_) + (width_/2)*cos(angle_));
  }
  if((X == 1)&&(Y == 1)){
    return (x_coord_ + (height_/2)*sin(angle_) + (width_/2)*cos(angle_));
  }
}

int CCar::GetYCoordinate(int X, int Y){
  // I need a big picture to describe these formulas...
  assert(X >= 0);
  assert(Y >= 0);
  assert(X <= 1);
  assert(Y <= 1);

  if((X == 0)&&(Y == 0)){
    return (y_coord_ - (height_/2)*cos(angle_) + (width_/2)*sin(angle_));
  }
  if((X == 0)&&(Y == 1)){
    return (y_coord_ + (height_/2)*cos(angle_) + (width_/2)*sin(angle_));
  }
  if((X == 1)&&(Y == 0)){
    return (y_coord_ - (height_/2)*cos(angle_) - (width_/2)*sin(angle_));
  }
  if((X == 1)&&(Y == 1)){
    return (y_coord_ + (height_/2)*cos(angle_) - (width_/2)*sin(angle_));
  }
}
