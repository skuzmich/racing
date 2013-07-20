// Copyright (C) 2013 Kuzmich Svyatoslav <svatoslav1@gmail.com>
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <stdio.h>
#include <assert.h>

#include <vector>
#include <string>

#include "./pacejka.h"

int main() {
  std::vector<float> a = {1.5, -40, 1600, 2600, 8.7, 0.014, -0.24, 1.0, -0.03,
                                 -0.0013, -0.15, -8.5, -0.29, 17.8, -2.4};

  std::vector<float> b = {1.5, -80, 1950, 23.3, 390, 0.05, 0, 0.055, -0.024,
                           0.014, 0.26};

  std::vector<float> c = {2.2, -3.9, -3.9, -1.26, -8.2, 0.025, 0, 0.044,
                               -0.58, 0.18, 0.043, 0.048, -0.0035, -0.18, 0.14,
                                                          -1.029, 0.27, -1.1};

  Pacejka pacejka(a, b, c);
  Pacejka pacejka_cfg_file("test.pcj");


  // Test 1
  pacejka.SetInput(.1/RAD2DEG, 3./RAD2DEG, 0.2, 2000.0);
  pacejka_cfg_file.SetInput(.1/RAD2DEG, 3./RAD2DEG, 0.2, 2000.0);

  float f_x = pacejka.CalculateFx();
  float f_y = pacejka.CalculateFy();
  float m_z = pacejka.CalculateMz();

  assert(f_x == pacejka_cfg_file.CalculateFx());
  assert(f_y == pacejka_cfg_file.CalculateFy());
  assert(m_z == pacejka_cfg_file.CalculateMz());

  assert(abs(f_x - 3443.69) < 0.1);
  assert(abs(f_y - 2363.98) < 0.1);
  assert(abs(m_z - (-21.5475)) < 0.1);

  printf("Test 1 passed.\n");

  // Test 2
  pacejka.SetInput(.1/RAD2DEG, 3./RAD2DEG, 0.2, 0.0);

  f_x = pacejka.CalculateFx();
  f_y = pacejka.CalculateFy();
  m_z = pacejka.CalculateMz();

  assert(abs(f_x - 0) < 0.1);
  assert(abs(f_y - (-2.4)) < 0.1);
  assert(abs(m_z - (-1.1)) < 0.1);

  printf("Test 2 passed.\n");

  // Test 3
  pacejka.SetInput(.1/RAD2DEG, 0./RAD2DEG, 0.2, 2000.0);

  f_x = pacejka.CalculateFx();
  f_y = pacejka.CalculateFy();
  m_z = pacejka.CalculateMz();

  assert(abs(f_x - 3443.69) < 0.1);
  assert(abs(f_y - (-146.693)) < 0.1);
  assert(abs(m_z - 2.98918) < 0.1);

  printf("Test 3 passed.\n");

  return 0;
}
