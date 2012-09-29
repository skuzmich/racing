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
#include <string.h>

#include "Socket.h"
#include "ClientData.h"

struct ClientCmp {
	public:
  	bool operator() (const SockAddr * c1, const SockAddr * c2) const {
      SockAddr * c1_casted = const_cast<SockAddr *>(c1);
      SockAddr * c2_casted = const_cast<SockAddr *>(c2);
    	if (strcmp(c1_casted->GetIP(),c2_casted->GetIP()) == 0)
    		return c1_casted->GetPort() - c2_casted->GetPort();
    	else
      	return strcmp(c1_casted->GetIP(), c2_casted->GetIP());
    };
};

class Server {
public:
  	// Колличество клиентов, которым удалось отправить данные о положении.
  	int Send();

    // колличество клиентов, от которых пришли данные.
    int Recv();

		// После создания сервер ждет каждого нового клиента с указанным таймаутом.
    // После создания вызвать Synhronize().
		Server (const char * ip, short port, int timeout_sec,
            int timeout_microsec, int timeout_total);

		bool SetTimeout (int timeout_sec,
    		int timeout_microsec, int timeout_total);

  Server ();
 
  virtual ~Server () {};

	protected:
  	// true возвращается в случае успеха, false - адрес не найден, либо
    // состояние клиента не детерминированно.
  	bool Disconnect(SockAddr * client);
	  static long long int time_;
  
  	// колличество клиентов, с которыми произведена синхронизация.
  /* 
   * Протокол синхронизации:
   * создаются потоки по колличеству клиентов, в каждом потоке клиенту
   * отправляется 100 запросов SYNHRO с таймаутом по селекту, в случае неудачной
   * синхронизации вызывается Disconnect() для соответствующего клиента.
   */
		int Synhronize();

    // friend class Car;

		// информация о клиентах.
		static std::map<SockAddr *, ClientData *, ClientCmp> clients_;


	private:
		static struct timeval timeout_;
  	static void * Synhro (void * client);

		// сокет.
    static UdpSock * my_sock_;

  	SockAddr * my_addr_;
  	Server (Server &orig);
};

#endif // SERVER_H