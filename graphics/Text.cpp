#include "Text.h"

struct Color
{
    unsigned char R, G, B, A;

    Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : 
        R(r), G(g), B(b), A(a)
    {}
};

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

void DrawTextGL(int left, int top, TTF_Font* font, std::string text)
{
    SDL_Color color = {255, 255, 225, 225};
    SDL_Surface* textSurface;
    textSurface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
    //printf("textSurface = %i, %i", textSurface->w, textSurface->h);
    GLuint Texture = SDLSurfaceToTexture(textSurface);

    DrawRectangle(left, left + textSurface->w, top, top + textSurface->h, Color(255, 255, 255, 255), Texture);

    SDL_FreeSurface(textSurface);
    glDeleteTextures(1, &Texture);
}
