// Copyright (C) 2011 Horoshenkih Sergey
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "./GPInterface.h"

GPInterface::GPInterface() {
  scale_ = 1.0;
  x0 = y0 = 0.0;
}

GPInterface::~GPInterface() {
}

GPInterface::GPInterface(int gr_w, int gr_h, int ph_w, int ph_h) {
  float gr_w_f =  static_cast<float>(gr_w);
  float gr_h_f =  static_cast<float>(gr_h);
  float ph_w_f =  static_cast<float>(ph_w);
  float ph_h_f =  static_cast<float>(ph_h);

  float aspect_gr = gr_w_f / gr_h_f;
  float aspect_ph = ph_w_f / ph_h_f;

  if (aspect_gr >= aspect_ph) {
      scale_ = gr_h_f / ph_h_f;
      y0 = 0;
      x0 = static_cast<int>((gr_w_f - ph_w_f * scale_) / 2);
  } else {
      scale_ = gr_w_f / ph_w_f;
      x0 = 0;
      y0 = static_cast<int>((gr_h_f - ph_h_f * scale_) / 2);
  }
  x1 = gr_w - x0;
  y1 = gr_h - y0;
}

// TODO(horoshenkih): do these functions inline (?)
int GPInterface::gr_x(float phys_x) {
  return static_cast<int>(phys_x * scale_) + x0;
}

int GPInterface::gr_y(float phys_y) {
  return static_cast<int>(phys_y * scale_) + y0;
}

float GPInterface::gr_ang(float phys_ang) {
  return phys_ang * 180 / 3.1415;
}
