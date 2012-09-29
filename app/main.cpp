// Copyright (C) 2011-2012 Kuzmich Svyatoslav <svatoslav1@gmail.com>
// Copyright (C) 2011 Horoshenkih Sergey
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


// TODO(svatoslav1): Use stl insted of stdio.h
#include <stdio.h>

#include "../physics/predecls.h"
#include "../graphics/Graphics.h"
#include "../base/event.h"
#include "./world.h"


int main(int argc, char** argv) {
  // Loading global game settings
  Settings * settings = new Settings("settings.txt");

  // Prepearing graphics part
  Renderer * renderer = new Renderer(settings);

  // Creating world for level.txt and gluing it to renderer
  World * world = new World("level.txt", settings, renderer);

  Event event;  // new_event.running_ is 'true' by default

  // Main game loop
  while (event.running()) {
    // Browse all the events (SDL_Events)
    // In case of quit-event, new_event.running_ sets to 'false'

    Uint32 startTime = SDL_GetTicks();

    event.CheckEvents();

    world->Update(&event);
    world->Render();

    float time = static_cast<float>((SDL_GetTicks() - startTime));

    // FPS - control
//   if ( time > 0 && time < 1000./settings->GetFPS())
//     SDL_Delay(1000./settings->GetFPS() - time);
  }

  delete world;
  delete settings;
  delete renderer;

  return 0;
}
