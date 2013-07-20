// Copyright (C) 2013 Kuzmich Svyatoslav <svatoslav1@gmail.com>
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Formulas from G. Genta's book, pages 63 and 77
//
// Thanks to Racer reference page
// http://www.racer.nl/reference/pacejka.htm

#ifndef PHYSICS_PACEJKA_H_
#define PHYSICS_PACEJKA_H_

#include <string>
#include <vector>

#define RAD2DEG (360./(2.*3.14159265))
#define EPSILON 0.000000001

class Pacejka {
 private:
  // Input parametrs
  float camber_;      // Angle between wheel and normal to surface (degrees)
  float slip_angle_;  // Angle between direction and velocity (degrees)
  float slip_ratio_;  // Spin velocity divided by linear velocity
  float f_z_;         // Normal force (kN)

  // Magic coefficients for calculating:
  std::vector<float> a_;  // a0..14  Fx longitudinal force
  std::vector<float> b_;  // b0..b10 Fy lateral force
  std::vector<float> c_;  // c0..c17 Mz aligning moment

 public:

  /**
   * Loads magic coefficients from config file.
   * Config file consist of 3 lines:
   * a0 a1 ... a13 a14
   * b0 b1 ... b9 b10
   * c0 c1 ... c16 c17
   */
  explicit Pacejka(std::string config_file);

  Pacejka(std::vector<float> a,
          std::vector<float> b,
          std::vector<float> c);

  void SetInput(float camber,      // Radians
                float slip_angle,  // Radians
                float slip_ratio,  // Ratio
                float f_z);        // Newtons

  float CalculateFx() const;
  float CalculateFy() const;
  float CalculateMz() const;
};

#endif  // PHYSICS_PACEJKA_H_
