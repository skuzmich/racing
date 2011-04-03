#include "CGraphics.h"

bool CGraphics::SetCoordinates(int number, int X, int Y, float ang) {
  if(list_of_cars_[number-1]->initialized){
    list_of_cars_[number-1]->SetCenter(X, Y);
    list_of_cars_[number-1]->SetAngle(ang);
    return true;
  } else return false;
}

bool CGraphics::Initialize(int scr_w, int scr_h) {
  
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }
    
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,            8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,          8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,           8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,          8);

    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,          16);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,         32);

    SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,      8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,    8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,     8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,    8);
/*
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  1);

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  2);
 */
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  
    if((surf_display_ = SDL_SetVideoMode(scr_w, scr_h, 32, SDL_OPENGL)) == NULL) {
        return false;
    }

    if((back_surface_ = LoadSurface("./gfx/Track.png")) == NULL) {
        return false;
    }
    SurfaceToGLTexture(back_surface_, &back_texture_);
    glClearColor(0, 0, 0, 0);

    glViewport(0, 0, scr_w, scr_h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, scr_w, scr_h, 0, 1, -1);

    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_TEXTURE_2D);

    glLoadIdentity();
  
  SDL_WM_SetCaption("MIPT racing game","MIPT racing game");
  
}

CGraphics *CGraphics::Create(int scr_w, int scr_h) {
  CGraphics *ret = new CGraphics();
  if (ret->Initialize(scr_w, scr_h))
    return ret;
  delete ret;
  return NULL;
}

int CGraphics::AddCar(int X, int Y, float ang, char *img){
  CCar *temp_car = new CCar(X, Y, ang, img);
  list_of_cars_.push_back(temp_car);
  return list_of_cars_.size();
}

void CGraphics::DrawBack() { // TODO: replace screen-size constant to variables
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    
  glBindTexture( GL_TEXTURE_2D, back_texture_ );
  glColor3f(1,1,1);
  glEnable(GL_TEXTURE_2D);

  glBegin( GL_QUADS );
      // Top-left vertex (corner)
      glTexCoord2i( 0, 0 );
      glVertex2f(0, 0);

      // Bottom-left vertex (corner)
      glTexCoord2i( 1, 0 );
      glVertex2f(640, 0);

      // Bottom-right vertex (corner)
      glTexCoord2i( 1, 1 );
      glVertex2f(640, 480);

      // Top-right vertex (corner)
      glTexCoord2i( 0, 1 );
      glVertex2f(0, 480);
      
  glEnd();
}

void CGraphics::DrawCar(int number) {
  if(list_of_cars_[number-1]->initialized){
    glBindTexture( GL_TEXTURE_2D, list_of_cars_[number-1]->car_texture_ );
    glColor3f(1,1,1);
    glEnable(GL_TEXTURE_2D);

    glBegin( GL_QUADS );
        // Top-left vertex (corner)
        glTexCoord2i( 0, 0 );
        glVertex2f(list_of_cars_[number-1]->GetXCoordinate(0,0),
                  list_of_cars_[number-1]->GetYCoordinate(0,0));

        // Bottom-left vertex (corner)
        glTexCoord2i( 1, 0 );
        glVertex2f(list_of_cars_[number-1]->GetXCoordinate(1,0),
                  list_of_cars_[number-1]->GetYCoordinate(1,0));

        // Bottom-right vertex (corner)
        glTexCoord2i( 1, 1 );
        glVertex2f(list_of_cars_[number-1]->GetXCoordinate(1,1),
                  list_of_cars_[number-1]->GetYCoordinate(1,1));

        // Top-right vertex (corner)
        glTexCoord2i( 0, 1 );
        glVertex2f(list_of_cars_[number-1]->GetXCoordinate(0,1),
                  list_of_cars_[number-1]->GetYCoordinate(0,1));
        
    glEnd();
  }
}

void CGraphics::Render() {
  DrawBack();
  for(int i = 1; i<=list_of_cars_.size(); i++){
    DrawCar(i);
  }
  SDL_GL_SwapBuffers();
}

CGraphics::CGraphics() {
    surf_display_ = NULL;
    back_surface_ = NULL;
    back_texture_ = 0;
}

CGraphics::~CGraphics() {
  SDL_FreeSurface(surf_display_);
  for(int i = 0; i < list_of_cars_.size(); i++){
    delete list_of_cars_[i];
  }
}

bool CGraphics::CleanUp(){
  return true;
}
