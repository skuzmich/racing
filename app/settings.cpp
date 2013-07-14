// Copyright (C) 2012 Kuzmich Svyatoslav <svatoslav1@gmail.com>
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <string>
#include <iostream>
#include <fstream>

#include "../base/fileparser.h"
#include "./settings.h"

Settings::Settings(std::string config_file_path) {
  std::ifstream fd(config_file_path.c_str());

  _time_step       = ReadFloat(&fd);
  _vel_iterations  = ReadInt(&fd);
  _pos_iterations  = ReadInt(&fd);
  _fps             = ReadFloat(&fd);

  _graph_width     = ReadInt(&fd);
  _graph_height    = ReadInt(&fd);
  _phys_width      = ReadInt(&fd);
  _phys_height     = ReadInt(&fd);
  _debug_draw      = ReadInt(&fd);
  _graphics_draw   = ReadInt(&fd);

  std::cout << "Global Settings: \n";
  std::cout << "Time Step: " << _time_step << std::endl;
  std::cout << "Vel Iterations: " << _vel_iterations << std::endl;
  std::cout << "Pos Iterations: " << _pos_iterations << std::endl;
  std::cout << "FPS: " << _fps << std::endl;

  std::cout << "Graphics Width : " << _graph_width  << std::endl;
  std::cout << "Graphics Height: " << _graph_height << std::endl;
  std::cout << "Physics Height : " << _phys_width   << std::endl;
  std::cout << "Physics Height : " << _phys_height  << std::endl;
  std::cout << "Debug Draw     : " << _debug_draw   << std::endl;
  std::cout << "Graphics Draw  : " << _graphics_draw<< std::endl;

  std::cout << std::endl;

  fd.close();
}
