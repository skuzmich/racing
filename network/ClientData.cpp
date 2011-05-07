/*
 *  ClientData.cpp
 *  
 *
 *  Created by Сергей Лега on 07.04.11.
 *  Copyright 2011 МФТИ(*
 */

#include <assert.h>

#include "ClientData.h"

bool ClientData::GetKeyPressed (std::vector<bool> &keys) {
	assert(keys.size() == 4);
  short pos = 0;
  for (std::vector<bool>::iterator i = keys.begin();
  		i != keys.end(); i++) {
    *i = (key_pressed_ >> pos) & 0x1;
    pos++;
	}
  return true;
}

bool ClientData::SetKeyPressed (std::vector<bool> &keys) {
  assert(keys.size() == 4);
	short pos = 0;
  for (std::vector<bool>::iterator i = keys.begin();
  		i != keys.end();
      i++) {

    if ((*i) > 0)
     key_pressed_ |= 0x1 << pos;
    else if ((*i) == 0)
       key_pressed_ &= (0xff << (pos + 1)) | (0xff >> (sizeof(char) - pos));
    else
      return false;
    pos++;
	}

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

  return true;
}

const struct CarPosition * ClientData::GetPosition () {

	if (my_position_ == NULL)
    return NULL;

	struct CarPosition * pos = new struct CarPosition;
  pos->x = my_position_->x;
  pos->y = my_position_->y;
  pos->angle = my_position_->angle;
  pos->speed = my_position_->speed;
  pos->steer_speed = my_position_->steer_speed;
  //pos->time = my_position_->time;

  return pos;
}

ClientData::ClientData (const SockAddr * m_addr,
    float init_x,
    float init_y,
    float init_angle) {
	assert(m_addr != NULL);
  my_position_ = new struct CarPosition;
  my_position_->x = init_x;
  my_position_->y = init_y;
  my_position_->angle = init_angle;
  my_position_->speed = 0.;
  my_position_->steer_speed = 0.;
  //my_position_->time = 0.;

  my_addr_ = new SockAddr((const_cast<SockAddr *>(m_addr))->GetIP(),
  		(const_cast<SockAddr *>(m_addr))->GetPort());

  key_pressed_ = 0;
}

ClientData::ClientData () {
  my_position_ = new struct CarPosition;
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

bool ClientData::AddDelta (const struct CarPosition * pos) {
	assert(pos);

	if (!my_position_)
  	return false;

	my_position_->x += pos->x;
  my_position_->y += pos->y;
  my_position_->angle += pos->angle;
  my_position_->speed += pos->speed;
  my_position_->steer_speed += pos->steer_speed;
  return true;
}
