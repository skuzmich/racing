// Copyright (C) 2011 Horoshenkih Sergey
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "Sprite.h"

// Default constructor of Sprite
/*
Sprite::Sprite() {
  x_coord_ = 0;
  y_coord_ = 0;
  angle_ = 0.0f;
  sprite_texture_ = 0;
  height_ = 0;
  width_ = 0;
}
*/
Sprite::~Sprite() {
}

Sprite::Sprite(unsigned int texture_id, float width, float height, int anchor_point,
        float x_coord, float y_coord, float angle) {

  texture_id_ = texture_id;
  x_coord_ = x_coord;
  y_coord_ = y_coord;
  angle_ = angle;
  height_ = height;
  width_ = width;
  anchor_point_ = anchor_point;
  /*
	SDL_Surface *temp, *image;
	GLuint texnum;
	Uint32 key;
	Uint32 rmask, gmask, bmask, amask;
  
  if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
    rmask = 0xff000000; gmask = 0x00ff0000; bmask = 0x0000ff00;	amask = 0x000000ff;
  } else {
      rmask = 0x000000ff;	gmask = 0x0000ff00;	bmask = 0x00ff0000;	amask = 0xff000000;
    }

	if ((temp = (SDL_Surface *) IMG_Load(filename))) {
  // The question is how to get texture with alpha information.
  // I've found solution here:
  // http://osdl.sourceforge.net/main/documentation/rendering/SDL-openGL.html

  // Briefly, it's following: first, load an image having alpha informations
  // normally as such (ex: IMG_Load). Call SDL_SetAlpha( thisSurface, 0, 0 )
  // on this surface. Create another surface, via SDL_CreateRGBSurface, and
  // blit the first surface to this newly created surface.
  
    w_img_ = temp->w;
    h_img_ = temp->h;
    
    // Calculating nearest to image sizes (from top) power-of-two texture sizes
    // (texture must be POT)
		w_tex_ = (int)powf(2.0, ceilf(logf((float)temp->w)/logf(2.0f)));
		h_tex_ = (int)powf(2.0, ceilf(logf((float)temp->h)/logf(2.0f)));
    
    GLint xpad, ypad;
      
		xpad = (w_tex_ - w_img_)/2; // Calculating of "pad" between "imaginary"
		ypad = (h_tex_ - h_img_)/2; // borders of image and texture

    SDL_SetAlpha(temp, 0, 0);
    image = SDL_CreateRGBSurface(SDL_SWSURFACE, w_tex_, h_tex_, 32,
                                 rmask, gmask, bmask, amask);
		SDL_Rect dst = {xpad, ypad, w_img_, h_img_};
		SDL_FillRect(image, NULL, key);
		
      
		SDL_BlitSurface(temp, 0, image, &dst);
		SDL_FreeSurface(temp);
		
		// OpenGL Texture creation
		glGenTextures(1, &texnum);
    glBindTexture(GL_TEXTURE_2D, texnum);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);

		SDL_FreeSurface(image);
		texture_id_ = texnum;
  }	else {
      texture_id_ = 0;
      w_img_ = h_img_ = w_tex_ = h_tex_ = 0;
    }
    */
}

void Sprite::GetCoordinates(float X, float Y, float ang){
  x_coord_ = X;
  y_coord_ = Y;
  angle_ = ang;
}

// Some getters below
float Sprite::width() const {
  return width_;
}

float Sprite::height() const {
  return height_;
}

float Sprite::x_coord() const {
  return x_coord_;
}

float Sprite::y_coord() const {
  return y_coord_;
}

float Sprite::angle() const {
  return angle_;
}

GLuint Sprite::texture_id() const {
  return texture_id_;
}
/*
int Sprite::w_img() const {
  return w_img_;
}

int Sprite::h_img() const {
  return h_img_;
}

int Sprite::w_tex() const {
  return w_tex_;
}

int Sprite::h_tex() const {
  return h_tex_;
}

void Sprite::Blit() {
  // Pure virtual
}

//------------------------------------------------------------------------------
SpriteCar::SpriteCar(const char *filename, int height, int width,
                    int x_coord, int y_coord, float angle) :
                    Sprite(filename, height, width, x_coord, y_coord, angle){
  // All parameters passed to the base class constructor
}

void SpriteCar::Blit() {
  // Calculating of "pads" (texture is POT, but image usually not)
  int xpad = (w_tex_ - w_img_)/2;
	int ypad = (h_tex_ - h_img_)/2;

  // Enable alpha-blending
	glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Setting projection matrix
	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 2*w_tex_, 0, 2*h_tex_, -1, 1);

  // Setting modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
    glLoadIdentity();
    glTranslatef(x_coord_, y_coord_, 0);
    glRotatef((GLfloat)angle_, 0, 0, 1);
    
  // Binding texture
	glBindTexture(GL_TEXTURE_2D, texture_id_);
	glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 1.0f);
		glTexCoord2d(xpad+1, ypad+1);
			glVertex2d(-width_/2, -height_/2);
		glTexCoord2d(xpad + w_img_ - 1, ypad + 1);
			glVertex2d(width_/2, -height_/2);
		glTexCoord2d(xpad + w_img_ - 1, ypad + h_img_ -1);
			glVertex2d(width_/2, height_/2);
		glTexCoord2d(xpad +1, ypad + h_img_-1);
			glVertex2d(-width_/2, height_/2);
	glEnd();
  
	glPopMatrix();
	glMatrixMode(GL_TEXTURE);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glDisable(GL_BLEND);

}
//------------------------------------------------------------------------------
SpriteBack::SpriteBack(const char *filename, int height, int width,
                      int x_coord, int y_coord, float angle) :
                    Sprite(filename, height, width, x_coord, y_coord, angle){
  // All parameters passed to the base class constructor
}

void SpriteBack::Blit() {
  // Calculating of "pads" (texture is POT, but image usually not)
  int xpad = (w_tex_ - w_img_)/2;
	int ypad = (h_tex_ - h_img_)/2;
  
  // Enable alpha-blending
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Setting projection matrix  
	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 2*w_tex_, 0, 2*h_tex_, -1, 1);

  // Setting modelview matrix	
	glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

  // Binding texture
	glBindTexture(GL_TEXTURE_2D, texture_id_);
	glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 1.0f);
		glTexCoord2d(xpad, ypad);
			glVertex2d(0, 0);
		glTexCoord2d(xpad + w_img_, ypad);
			glVertex2d(width_, 0);
		glTexCoord2d(xpad + w_img_, ypad + h_img_);
			glVertex2d(width_, height_);
		glTexCoord2d(xpad, ypad + h_img_);
			glVertex2d(0, height_);
	glEnd();
  
	glPopMatrix();
	glMatrixMode(GL_TEXTURE);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glDisable(GL_BLEND);

}
*/
