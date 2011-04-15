/*
 *  Server.cpp
 *  
 *
 *  Created by Сергей Лега on 07.04.11.
 *  Copyright 2011 МФТИ(ГУ). All rights reserved.
 *
 */

#include "Server.h"

// Before use set it as nonblocking.
int Server::Recv () {
	if (my_addr_->GetDescriptor() < 1)
  	return -1;

	struct CarPosition pos;
	int received_packages = 0;

  fd_set recvfds;
  FD_ZERO(&recvfds);
  FD_SET(my_sock_->GetDescriptor(), &recvfds);
	SockAddr * addr = new SockAddr();

	for (int i = 0; i < clients_.size(); i++) {
  	if (select(my_sock_->GetDescriptor() + 1,
    		&recvfds,
      	NULL,
      	NULL,
        &timeout) > 0))

    	if (my_sock_->recv(addr,
    			&pos,
        	sizeof(struct CarPosition)) > 0) {
        if (clients_.find(addr) != clients_.end()) {
      		received_packages++;
          clients_[addr] = pos;
        }
    	}
  }

	return received_packages;
}

int Server:Send () {
	if (my_addr_->GetDescriptor() < 1)
  	return -1;

	int sended_packages = 0;

	for (std::mapmap<ClientData *, SockAddr *>::iterator iter = clients_.begin();
  		iter != clients_.end();
    	iter++) {

		if (my_sock_->send((*iter).second->GetAddr(),
    		(*iter).first->GetPosition(),
        sizeof(struct CarPosition)) > 0)
    	sended_packages++;
	}

	return sended_packages;
}

Server::Server (const char * ip, unsigned port, int timeout_sec,
    		int timeout_microsec, int timeout_total) {

	assert((timeout_sec > 0) && (timeout_microsec > 0) && (timeout_total > 0));

	my_addr_ = new SockAddr (ip, port);
  my_sock_ = new UdpSock();
  my_sock_->bind(my_addr_);
  timeout.tv_sec = timeout_sec;
  timeout.tv_usec = timeout_microsec;

	long long int retries = timeout_total / timeout_sec;

  fd_set recvfds;
  FD_ZERO(&recvfds);
  FD_SET(my_sock_->GetDescriptor(), &recvfds);

	SockAddr buf_addr;
  char init_message[30];
  for (int i = 0; i< retries; i++) {
  	if (select(my_sock_->GetDescriptor() + 1; &recvfds, NULL, NULL,
    		&timeout) > 0) {
    	if (my_sock_->recv(&buf_addr, init_message, sizeof(char) * 30) ==
      		sizeof(char) * strlen("I want to play!")) {
        clients_[&buf_addr] = new ClientData();
    	}
		}
  }
}
