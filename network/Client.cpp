/*
 *  Client.cpp
 *  
 *
 *  Created by Сергей Лега on 22.04.11.
 *  Copyright 2011 МФТИ(ГУ). All rights reserved.
 *
 */

#include <assert.h>
#include <pthread.h>
#include <string.h>

#include "Client.h"

struct DataForSend {
	SockAddr * serv_addr;
  UdpSock * sock;
  int * accepted;
};

// Эта функция в отдельном потоке посылает 100 запросов на соединение к серверу.
void * SendReq(void * serv_data) {
	assert (serv_data != NULL);
	struct DataForSend * casted_serv_data = reinterpret_cast<struct DataForSend *>(serv_data);

	assert (casted_serv_data->sock != NULL);
  assert (casted_serv_data->serv_addr != NULL);
  assert (casted_serv_data->accepted);

  struct Packet msg_to_serv;
  strncpy (msg_to_serv.data, "I want to play!", strlen("I want to play!"));

  int i = 0;
	for (; i < 100; i++) {
  	if (*(casted_serv_data->accepted) == 0)
  	  casted_serv_data->sock->send(casted_serv_data->serv_addr, &msg_to_serv);
  }

  // данное условие означает, что было выполненно 100 запросов, но подтверждения
  // от сервера не последовало.
  if (i == 100 && *(casted_serv_data->accepted) == 0)
    *(casted_serv_data->accepted) == -1;
}

Client::Client (const char * ip, short port, int timeout_sec,
		int timeout_usec) {
	assert((timeout_sec > 0) && (timeout_usec > 0));

	my_addr_ = new SockAddr();
  my_sock_ = new UdpSock();
  my_sock_->bind(my_addr_);

  timeout.tv_sec = timeout_sec;
  timeout.tv_usec = timeout_usec;

	serv_addr_ = new SockAddr(ip, port);

	struct DataForSend data;
  int * accepted = new int;
  (*accepted) = 0;

  data.sock = my_sock_;
  data.serv_addr = serv_addr_;
	data.accepted = accepted;

	pthread_t tid;
  // SendReq запускается в отдельном потоке, в то время как в другом потоке
  // Client::Client слушвет сокет на предмет подтверждающего сообщения от
  // сервера.
	pthread_create(&tid, NULL,  &SendReq, (void *)(&data));

	SockAddr * receiving_for = new SockAddr();
  struct Packet msg_from_srv;

  fd_set recvfds;
  FD_ZERO(&recvfds);
  FD_SET(my_sock_->GetDescriptor(), &recvfds);

	while (select(my_sock_->GetDescriptor() + 1, &recvfds, NULL, NULL,
  		&timeout) > 0) {
  	if ((*accepted) == -1)
    	break;
    my_sock_->recv(receiving_for, &msg_from_srv);

		if (strcmp(receiving_for->GetIP(), ip) && (port == receiving_for->GetPort()))

    	if (strncmp(msg_from_srv.data, "You're accepted",
                  strlen("You're accepted")) == 0) {
      	(*accepted) = 1;
        break;
      }
			else
      	printf("Client: unknown data received!\n");

    else
    	printf("Client: unknown data received!\n");
    FD_ZERO(&recvfds);
    FD_SET(my_sock_->GetDescriptor(), &recvfds);
  }
}

bool Client::Send() {
  struct Packet *pos = new struct Packet;
  pos->type = DELTA;
	memcpy(pos->data, my_data_->GetPosition(), sizeof(struct CarPosition));
  pos->size = sizeof(struct CarPosition);

	if (my_sock_->send(serv_addr_, pos) == sizeof(struct CarPosition))
    return true;
	return false;
}

bool Client::Recv() {
	struct Packet * pos = new struct Packet;
	if (my_sock_->recv(serv_addr_, pos) == sizeof(struct CarPosition)) {

    my_data_->SetPosition(reinterpret_cast<struct CarPosition *> (pos));
    return true;
	}
	return false;
}

bool Client::SetPosition(const struct CarPosition * new_pos) {
	if (new_pos == NULL) {
  	return false;
  }

	my_data_->SetPosition(new_pos);
	return true;
}
