// Copyright (C) 2011 Horoshenkih Sergey
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "Graphics.h"

/*
#include "event.h"

void SetCoords(int *X, int *Y, float *a){
  static int Xcoord = 100, Ycoord = 100;
  static float Angle = 60;
  Xcoord +=1;
  *X = Xcoord; Ycoord +=1; *Y = Ycoord;
  Angle +=0.1;
  *a = Angle;
}

int main(int argc, char* argv[]) {
  // Some parameters for testing
  int test_w = 800;
  int test_h = 600;
  int test_phys_w = 400;
  int test_phys_h = 300;
  
  Graphics *gr = Graphics::Create(test_w, test_h);
  assert(gr);
  // Initialization of interface between graphics and physics (GPInterface)
  gr->InitGPInterface(test_w, test_h, test_phys_w, test_phys_h);
  gr->AddSprite(32, 17, "./gfx/car1.png");
  gr->AddSprite(32, 17, "./gfx/car2.png");
  // Variable coordinates of car
  float cX = 20, cY = 15;
  float ang = 0;
  gr->SetSpriteCoordinates(0, cX, cY, ang);
  gr->SetSpriteCoordinates(1, cX+50, cY, ang);
  // 
  Event new_event;
  
 // printf("%d %d\n", gpi.gr_coordinate_x(cX), gpi.gr_coordinate_y(cY));
  while(new_event.running()) {
    new_event.CheckEvents();
    if(new_event.fullscreen()) {
      gr->FullscreenOn();
    } else {
        gr->FullscreenOff();
      }
    gr->Render();
    cX += 0.1;
    cY += 0.1;
    ang += 0.01;
    gr->SetSpriteCoordinates(0, cX, cY, ang);
    gr->SetSpriteCoordinates(1, cX+50, cY, ang);
    SDL_Delay(5);
  }
  gr->CleanUp();
  delete gr;
  return 0;
}
*/

#include <string>
#include "SDL.h"
#include "SDL_opengl.h"
#include <SDL_ttf.h>

using namespace std;

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 1024

struct Color
{
    unsigned char R, G, B, A;

    Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : 
        R(r), G(g), B(b), A(a)
    {}
};


void DrawRectangle(int left, int right, int top, int bottom, Color c, GLuint Texture);
void DrawTextGL(int left, int top, TTF_Font* font, const char * text);
GLuint SDLSurfaceToTexture(SDL_Surface* surface);

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_VIDEO);   
    SDL_Surface* screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_OPENGL);
    TTF_Init();

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);
    glEnable(GL_TEXTURE_2D);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Enabling transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

    SDL_Surface* temp = SDL_LoadBMP("New Bitmap Image.bmp");
    GLuint WhiteTexture = SDLSurfaceToTexture(temp);

    TTF_Font* Font;
    Font = TTF_OpenFont("FreeSerif.ttf", 36);
    DrawRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, Color(0, 0, 0, 255), WhiteTexture);
    SDL_GL_SwapBuffers();
    DrawTextGL(300, 300, Font, "graveyard");
    DrawTextGL(600, 600, Font, "graveyard");

    SDL_GL_SwapBuffers();
    system("pause");
    SDL_Quit();
    return 0;
}
