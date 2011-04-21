#include "Sprite.h"

Sprite::Sprite() {
  x_coord_ = 0;
  y_coord_ = 0;
  angle_ = 0.0f;
  surf_sprite_ = NULL;
  sprite_texture_ = 0;
  height_ = 0;
  width_ = 0;
}

Sprite::Sprite(int x_coord, int y_coord, float angle,
               int height, int width, GLuint texture) {
  x_coord_ = x_coord;
  y_coord_ = y_coord;
  angle_ = angle;
  surf_sprite_ = NULL;
  sprite_texture_ = texture;
  height_ = height;
  width_ = width;
}

void Sprite::GetCoordinates(int X, int Y, float ang){
  x_coord_ = X;
  y_coord_ = Y;
  angle_ = ang;
}

int Sprite::height() {
  return height_;
}

int Sprite::width() {
  return width_;
}

int Sprite::x_coord() {
  return x_coord_;
}

int Sprite::y_coord() {
  return y_coord_;
}

float Sprite::angle() {
  return angle_;
}

GLuint Sprite::sprite_texture() {
  return sprite_texture_;
}
