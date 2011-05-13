// Copyright (C) 2011 Horoshenkih Sergey
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "GPInterface.h"
#include <stdio.h>

GPInterface::GPInterface() {
  scale_x_ = 1.0;
  scale_y_ = 1.0;
}

GPInterface::~GPInterface() {
  //printf("In GPInterface::GPInterface()\n");
}

bool GPInterface::Init(int gr_w, int gr_h, int ph_w, int ph_h) {
  if (ph_w == 0) return false;
  if (ph_h == 0) return false;
  scale_x_ = (float)gr_w/(float)ph_w;
  scale_y_ = (float)gr_h/(float)ph_h;
  return true;
}

// TODO(horoshenkih): do these functions inline (?)
int GPInterface::gr_x(float phys_x){
  return (int)(phys_x*scale_x_ + 0.5);
}

int GPInterface::gr_y(float phys_y){
  return (int)(phys_y*scale_y_+ 0.5);
}

float GPInterface::gr_ang(float phys_ang){
  return phys_ang*180/3.1415;
}
