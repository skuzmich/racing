// Copyright (C) 2013 Kuzmich Svyatoslav <svatoslav1@gmail.com>
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <math.h>
#include <stdio.h>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "./pacejka.h"
#include "../base/fileparser.h"


/**
 *  If rhs is close to zero return big constant value
 */
inline float SafeDoubleDiv(float lhs, float rhs) {
  if (abs(rhs) < EPSILON)
    return 99999999;
  return lhs / rhs;
}

/**
 * Loads magic coefficients from config file.
 * Config file consist of 3 lines:
 * a0 a1 ... a13 a14
 * b0 b1 ... b9 b10
 * c0 c1 ... c16 c17
 */
Pacejka::Pacejka(std::string config_file_path)
  : camber_(.0),
    slip_angle_(.0),
    slip_ratio_(.0),
    f_z_(.0) {
  std::ifstream fd(config_file_path.c_str());

  ReadFloatVector(&a_, &fd, 15);
  ReadFloatVector(&b_, &fd, 11);
  ReadFloatVector(&c_, &fd, 18);

  std::cout << "a[] = ";
  for (float i: a_) std::cout << i << ", ";
  std::cout << std::endl;

  std::cout << "b[] = ";
  for (float i: b_) std::cout << i << ", ";
  std::cout << std::endl;

  std::cout << "b[] = ";
  for (float i: b_) std::cout << i << ", ";
  std::cout << std::endl;

  fd.close();
}


Pacejka::Pacejka(std::vector<float> a,  // a0..14
                 std::vector<float> b,  // b0..b10
                 std::vector<float> c)  // c0..c17
  : a_(a),
    b_(b),
    c_(c),
    camber_(.0),
    slip_angle_(.0),
    slip_ratio_(.0),
    f_z_(.0) {
}

/**
 * Setting input parameters and converting them to pacejka units
 */
void Pacejka::SetInput(float camber,
               float slip_angle,
               float slip_ratio,
               float f_z) {
  camber_ = camber * RAD2DEG;
  slip_angle_ = slip_angle * RAD2DEG;
  slip_ratio_ = slip_ratio;
  f_z_ = f_z / 1000.;
}

/**
 * Calculates longitudinal force Fx
 */

float Pacejka::CalculateFx() const {
  float C = b_[0];
  float u_p = b_[1]*f_z_ + b_[2];
  float D = u_p * f_z_;
  float B = SafeDoubleDiv((b_[3]*f_z_*f_z_ + b_[4]*f_z_) * expf(-b_[5]*f_z_),
                            C*D);

  float E = b_[6]*f_z_*f_z_ + b_[7]*f_z_ + b_[8];
  float s_h = b_[9]*f_z_ + b_[10];
  return D * sin(C * atan(B*(1. - E)*(slip_ratio_*100. + s_h)
         + E*atan(B*(slip_ratio_*100 + s_h))));
}

/**
 * Calculates lateral force Fy
 */
float Pacejka::CalculateFy() const {
  float C = a_[0];
  float u_p = a_[1]*f_z_ + a_[2];
  float D = u_p*f_z_;
  float E = a_[6]*f_z_ + a_[7];

  float lateral_stiffness = a_[3]*sin(2*atan(SafeDoubleDiv(f_z_, a_[4]))) *
                             (1 - a_[5]*abs(camber_));

  float B = SafeDoubleDiv(lateral_stiffness, (C*D));
  float s_h = a_[8]*camber_ + a_[9]*f_z_ + a_[10];
  float s_v = (a_[11]*f_z_ + a_[12])*camber_*f_z_ + a_[13]*f_z_ + a_[14];
  return D*sin(C*atan(B*(1. - E)*(slip_angle_ + s_h) +
            E*atan(B*(slip_angle_ + s_h)))) + s_v;
}

/**
 *  Calculates aligning moment Mz
 */
float Pacejka::CalculateMz() const {
  float f_z_squared = f_z_*f_z_;
  float C = c_[0];
  float D = c_[1]*f_z_squared + c_[2]*f_z_;
  float E = (c_[7]*f_z_squared + c_[8]*f_z_ + c_[9])*(1 - c_[10]*abs(camber_));
  float B = SafeDoubleDiv((c_[3]*f_z_squared + c_[4]*f_z_) *
             (1 - c_[6]*abs(camber_)) * exp(-c_[5]*f_z_), (C*D));

  float s_h = c_[11]*camber_ + c_[12]*f_z_ + c_[13];
  float s_v = (c_[14]*f_z_squared + c_[15]*f_z_)*camber_ +
                c_[16]*f_z_ + c_[17];
  return D*sin(C*atan(B*(1.0f - E)*(slip_angle_ + s_h) +
        E*atan(B*(slip_angle_ + s_h)))) + s_v;
}
