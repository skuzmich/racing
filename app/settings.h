// Copyright (C) 2012 Kuzmich Svyatoslav <svatoslav1@gmail.com>
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef APP_SETTINGS_H_
#define APP_SETTINGS_H_

#include <string>

/* Structure of global game settings */
class Settings {
 private:
  float32 _time_step;
  int32 _vel_iterations;
  int32 _pos_iterations;
  float32 _fps;

  int32 _graph_width;
  int32 _graph_height;
  int32 _phys_width;
  int32 _phys_height;

 public:
  float32 GetTimeStep() { return _time_step; }
  int32 GetVelIterations() { return _vel_iterations; }
  int32 GetPosIterations() { return _pos_iterations; }
  float32 GetFPS() { return _fps; }

  int32 GetGraphWidth()  { return _graph_width ; }
  int32 GetGraphHeight() { return _graph_height; }
  int32 GetPhysWidth()   { return _phys_width  ; }
  int32 GetPhysHeight()  { return _phys_height ; }

  explicit Settings(std::string config_file_path);
  ~Settings() {}
};

#endif  // APP_SETTINGS_H_
