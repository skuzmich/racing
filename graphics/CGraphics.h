#ifndef _CGRAPHICS_H_
  #define _CGRAPHICS_H_

#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#include <math.h>
#include <assert.h>

class CCar {
  public:
    int x_coord_;
    int y_coord_;
    float angle_;
  
    SDL_Surface *surf_car_;
    GLuint car_texture_;
    int height_;
    int width_;
    
  
    bool initialized;
    CCar();
    CCar(int X, int Y, float ang, const char *pict);
    ~CCar();
        
    void SetCenter(int X, int Y);
    void SetAngle(double fi);
    int GetXCoordinate(int X, int Y);// Returns X-coordinate of vertex (i,j), i,j = {0,1}
    int GetYCoordinate(int X, int Y);// Returns X-coordinate of vertex (i,j), i,j = {0,1}
};


class CGraphics {
  private:
    SDL_Surface *surf_display_;
    SDL_Surface *back_surface_;
    GLuint back_texture_;
    std::vector<class CCar *> list_of_cars_;
  public:
    static CGraphics *Create(int scr_w, int scr_h);
    CGraphics();
    ~CGraphics();
    bool Initialize(int scr_w, int scr_h);
    int AddCar(int X, int Y, float ang, char *img); // returns a number of added car
    bool SetCoordinates(int number, int X, int Y, float ang);
    void DrawBack();
    void DrawCar(int number);
    void Render();
    bool CleanUp();
    
};


SDL_Surface* LoadSurface(char* File);
bool SurfaceToGLTexture(SDL_Surface* surf, GLuint *tex);

#endif
