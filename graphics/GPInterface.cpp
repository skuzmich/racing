#include "GPInterface.h"

GPInterface::GPInterface() {
  scale_x_ = 1.0;
  scale_y_ = 1.0;
}

GPInterface::~GPInterface() {
}

bool GPInterface::Init(int gr_w, int gr_h, int ph_w, int ph_h) {
  if (ph_w == 0) return false;
  if (ph_h == 0) return false;
  scale_x_ = (float)gr_w/(float)ph_w;
  scale_y_ = (float)gr_h/(float)ph_h;
  return true;
}

// TODO(horoshenkih): do these functions inline (?)
int GPInterface::gr_coordinate_x(float phys_coordinate_x){
  return (int)(phys_coordinate_x*scale_x_);
}

int GPInterface::gr_coordinate_y(float phys_coordinate_y){
  return (int)(phys_coordinate_y*scale_y_);
}
