/*
 *  Server.h
 *  
 *
 *  Created by Сергей Лега on 07.04.11.
 *  Copyright 2011 МФТИ(ГУ). All rights reserved.
 *
 */

#ifndef SERVER_H
#define SERVER_H

#include <map>

#include <sys/select.h>

#include "Socket.h"
#include "ClientData.h"

class Server {
  private:
    SockAddr * my_addr_;
    Server (Server &orig);

  public:
  	// Колличество клиентов, которым удалось отправить данные о положении.
  	int Send();

    // колличество клиентов, от которых пришли данные.
    int Recv();

		// После создания сервер ждет каждого нового клиента с указанным таймаутом.
    // После создания вызвать Synhronize().
		explicit Server (const char * ip, unsigned port, int timeout_sec,
    		int timeout_microsec, int timeout_total);

		bool SetTimeout (int timeout_sec,
    		int timeout_microsec, int timeout_total);

    Server ();
 
		~Server ();

		// колличество клиентов, с которыми произведена синхронизация.
		int Synhronize();

	protected:
		struct timeval timeout;

		// информация о клиентах.
		std::map<SockAddr *, ClientData *> clients_;

		// сокет.
    UdpSock * my_sock_;
};

#endif // SERVER_H