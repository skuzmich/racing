#include <cstdlib> // For some useful functions such as atexit :)
#include "SDL.h" // main SDL header
 
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define true 1
#define false 0 //You might have to declaire True and False.
#define COLORKEY 255, 0, 255 //Your Transparent colour
 
SDL_Surface *screen; //This pointer will reference the backbuffer
 
//I have set the flag SDL_SWSURFACE for a window :)
int InitVideo(Uint32 flags = SDL_DOUBLEBUF | SDL_SWSURFACE) {
  // Load SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
    return false;
  }
  atexit(SDL_Quit); // Clean it up nicely :)
 
  // fullscreen can be toggled at run time :) any you might want to change the flags with params?
  //set the main screen to SCREEN_WIDTHxSCREEN_HEIGHT with a colour depth of 16:
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16, flags);
  if (screen == NULL) {
    fprintf(stderr, "Unable to set video mode: %s\n", SDL_GetError());
    return false;
  }
  return true;
}
 
 
int SDL_main_init() {
  int res = 0; //Results
  if (InitVideo() == false) return 1;
  //SDL_Flip(screen); //Refresh the screen
  //SDL_Delay(6500); //Wait a bit :)
 
  return 0;
}
