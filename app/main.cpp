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

  GPInterface * gpi = new GPInterface(settings->GetGraphWidth(),
                            settings->GetGraphHeight(),
                            settings->GetPhysWidth(),
                            settings->GetPhysHeight());
  // Prepearing graphics part
  Renderer * renderer = new Renderer(settings, gpi);

  // Creating world for level.txt and gluing it to renderer
  World * world = new World("level.txt", settings, renderer, gpi);

  Event event;  // new_event.running_ is 'true' by default

  // Main game loop
  while (event.running()) {
    // Browse all the events (SDL_Events)
    // In case of quit-event, new_event.running_ sets to 'false'

    Uint32 startTime = SDL_GetTicks();

    event.CheckEvents();

    world->Update(&event);
    world->Render();
  }

  delete world;
  delete settings;
  delete renderer;

  return 0;
}
