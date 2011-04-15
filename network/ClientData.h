/*
 *  ClientData.h
 *  
 *
 *  Created by Сергей Лега on 07.04.11.
 *  Copyright 2011 МФТИ(ГУ). All rights reserved.
 *
 */

#ifndef CLIENTDATA_H
#define	CLIENTDATA_H

#include "Socket.h"

struct CarPosition {
  float x;
  float y;
  float angle;
  float speed;
  float steer_speed;
  float time;
}

class ClientData {
  private:
    ClientData (const ClientData &orign);
    SockAddr * my_addr_;

    // 10000000 - left,
    // 01000000 - right,
    // 00100000 - up,
    // 00010000 - down.
    char key_pressed_;

    struct CarPosition * my_position_; 
    
  public:
    bool SetPosition (const struct CarPosition * pos);
    bool GetPosition (struct CarPosition * pos);

  	const SockAddr * GetAddr ();

    // [0] - left,
    // [1] - right,
    // [2] - up,
    // [3] - down.
  	bool GetKeyPressed (std::vector<bool> * keys);
    bool SetKeyPressey (std::vector<bool> * keys);

    explicit ClientData (const char * ip,
        unsigned port,
        float init_x,
        float init_y);
    ClientData ();
		virtual ~ClientData ();
}

#endif // CLIENTDATA_H
