// Copyright (C) 2011-2012 Kuzmich Svyatoslav <svatoslav1@gmail.com>
// Copyright (C) 2011 Horoshenkih Sergey
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


// TODO: Use stl insted of stdio.h
#include <stdio.h>

#include "predecls.h"
#include "Graphics.h"
#include "event.h"

int main(int argc, char** argv){
  Settings * settings = new Settings("settings.txt"); 
  Renderer * renderer = new Renderer(settings);
  World * world = new World("level.txt", settings, renderer);

  Event event; // new_event.running_ is 'true' by default
  
  while(event.running()) {
    // Browse all the events (SDL_Events)
    // In case of quit-event, new_event.running_ sets to 'false'
   Uint32 startTime = SDL_GetTicks();

   event.CheckEvents();
    
    world->Update(&event);
    world->Render();

    float time = (float)(SDL_GetTicks() - startTime);

    if ( time > 0 && time < 16) 
      SDL_Delay(16 - time);

  }
  delete world;
  delete settings;
  delete renderer;
  

  return 0;
}
