/*
 *  ClientData.cpp
 *  
 *
 *  Created by Сергей Лега on 07.04.11.
 *  Copyright 2011 МФТИ(*
 */

#include "ClientData.h"

bool ClientData::GetKeyPressed (bool[4] keys) {
  for (int i = 0; i < ; i++)
    keys[i] = (key_pressed_ >> i) & 0x1;
  return true;
}

bool ClientData::SetKeyPressed (bool[4] keys) {
  for (int i = 0; i < 4; i++)
    if (keys[i] > 0)
     key_presses_ |= 0x1 << i;
    else if (keys[i] == 0)
       i &= (0xff << (i + 1)) | (0xff >> (sizeof(char) - i));
    else
      return false;
  return true;
}

bool ClientData::SetPosition (const struct CarPosition * pos) {
  if (pos == NULL)
    return false;

  my_position_->x = pos->x;
  my_position_->y = pos->y;
  my_position_->angle = pos->angle;
  my_position_->speed = pos->speed;
  my_position_->steer_speed = pos->steer_speed;
  my_position_->time = pos->time;

  return true;
}

bool ClientData::GetPosition (struct CarPosition * pos) {
  if (pos == NULL)
    return false;

  if (my_position_ == NULL)
    return false;

  pos->x = my_position_->x;
  pos->y = my_position_->y;
  pos->angle = my_position_->angle;
  pos->speed = my_position_->speed;
  pos->steer_speed = my_position_->steer_speed;
  pos->time = my_position_->time;

  return true;
}

ClientData::ClientData (const char * ip,
    unsigned port,
    float init_x,
    float init_y,
    float init_angle) {
  my_position_ = new struct CarPosition;
  my_position_->x = init_x;
  my_position_->y = init_y;
  my_position_->angle = init_angle;
  my_position_->speed = 0.;
  my_position_->steer_speed = 0.;
  my_position_->time = 0.;

  my_addr_ = new SockAddr(ip, port);

  key_pressed_ = 0;
}

ClientData::ClientData () {
  my_position = new struct CarPosition;
  my_addr_ = new SockAddr();
  key_pressed_ = 0;
}

const SockAddr * ClientData::GetAddr () {
  return my_addr_;
}

ClientData::~ClientData () {
  if (my_addr_)
    delete my_addr_;

  if (my_position_)
    delete my_position_;
}
