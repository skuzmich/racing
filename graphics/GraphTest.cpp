// Copyright (C) 2011 Horoshenkih Sergey
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
/*
#include "CGraphics.h"
#include "event.h"
#include "GPInterface.h"

void SetCoords(int *X, int *Y, float *a){
  static int Xcoord = 100, Ycoord = 100;
  static float Angle = 60;
  Xcoord +=1;
  *X = Xcoord;
  Ycoord +=1;
  *Y = Ycoord;
  Angle +=0.1;
  *a = Angle;
}

int main(int argc, char* argv[]) {
  // Some parameters for testing
  int test_w = 1024;
  int test_h = 768;
  int test_phys_w = 400;
  int test_phys_h = 300;
  
  CGraphics *gr = CGraphics::Create(test_w, test_h);
  assert(gr);
  // Variable coordinates of car
  float cX = 200, cY = 150;
  float ang = 0;
  gr->AddCar(100, 100, 60, "./gfx/car1.png");
  // 
  Event new_event;
  // Initialization of interface between graphics and physics (GPInterface)
  GPInterface gpi;
  gpi.Init(test_w, test_h, test_phys_w, test_phys_h);
  
  gr->SetCoordinates(1,
                    gpi.gr_coordinate_x(cX),
                    gpi.gr_coordinate_y(cY),
                    ang);
                    
 // printf("%d %d\n", gpi.gr_coordinate_x(cX), gpi.gr_coordinate_y(cY));
  while(new_event.running()) {
    new_event.CheckEvents();
    gr->Render();
    SDL_Delay(10);
  }
  
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
void DrawTextGL(int left, int top, TTF_Font* font, string text);
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

void DrawRectangle(int left, int right, int top, int bottom, Color c, GLuint Texture)
{
    glBindTexture(GL_TEXTURE_2D, Texture);

    glColor4f(c.R/255.0f, c.G/255.0f, c.B/255.0f, c.A/255.0f);

    glBegin(GL_QUADS);

    //Top-left vertex (corner) 
    glTexCoord2i(0, 0);
    glVertex2f(GLfloat(left), GLfloat(top));

    //Top-right vertex (corner)
    glTexCoord2i(1, 0);
    glVertex2f(GLfloat(right), GLfloat(top));

    //Bottom-right vertex (corner)
    glTexCoord2i(1, 1);
    glVertex2f(GLfloat(right), GLfloat(bottom));

    //Bottom-left vertex (corner)
    glTexCoord2i(0, 1);
    glVertex2f(GLfloat(left), GLfloat(bottom));

    glEnd();
}

void DrawTextGL(int left, int top, TTF_Font* font, string text)
{
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface* textSurface;
    textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
    GLuint Texture = SDLSurfaceToTexture(textSurface);

    DrawRectangle(left, left + 260, top, top + 80, Color(255, 255, 255, 255), Texture);

    SDL_FreeSurface(textSurface);
    glDeleteTextures(1, &Texture);
}

GLuint SDLSurfaceToTexture(SDL_Surface* surface)
{
    GLuint texture;
    GLint nOfColors;
    GLenum texture_format;

    // get the number of channels in the SDL surface
    nOfColors = surface->format->BytesPerPixel;

    if (nOfColors == 4)     // contains an alpha channel
    {
        if (surface->format->Rmask == 0x000000ff)
            texture_format = GL_RGBA;
        else
            texture_format = GL_BGRA;
    } 
    else if (nOfColors == 3)
    {
        if (surface->format->Rmask == 0x000000ff)
            texture_format = GL_RGB;
        else
            texture_format = GL_BGR;
    }
    else
    {
        printf("Picture with less than 24-bit color depth detected.\n");
        return 0;
    }

    // Have OpenGL generate a texture object handle for us
    glGenTextures(1, &texture);

    // Bind the texture object
    glBindTexture(GL_TEXTURE_2D, texture); 

    // Set the texture's stretching properties
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Edit the texture object's image data using the information SDL_Surface gives us
    glTexImage2D(GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
    texture_format, GL_UNSIGNED_BYTE, surface->pixels);

    // Bind the texture to which subsequent calls refer to
    glBindTexture(GL_TEXTURE_2D, texture);

    return texture;
}
