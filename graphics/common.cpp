#include "CGraphics.h"

SDL_Surface* LoadSurface(char* File) {
  SDL_Surface* Surf_Temp = NULL;
  SDL_Surface* Surf_Return = NULL;

  if((Surf_Temp = IMG_Load(File)) == NULL) {
    return NULL;
  }

  Surf_Return = SDL_DisplayFormatAlpha(Surf_Temp);
  SDL_FreeSurface(Surf_Temp);

  return Surf_Return;
}

bool SurfaceToGLTexture(SDL_Surface* surf, GLuint *tex){
    glGenTextures(1, tex);
    glBindTexture(GL_TEXTURE_2D, *tex);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, surf->w, surf->h,
        0, GL_BGRA, GL_UNSIGNED_BYTE, surf->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    return true;
}
