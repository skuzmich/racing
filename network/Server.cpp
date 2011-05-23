/*
 *  Server.cpp
 *  
 *
 *  Created by Сергей Лега on 07.04.11.
 *  Copyright 2011 МФТИ(ГУ). All rights reserved.
 *
 */

#include "Server.h"
#include "ClientData.h"

#include <unistd.h>
#include <pthread.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

std::map<SockAddr *, ClientData *, ClientCmp> Server::clients_;
std::map<SockAddr *, TcpSock *, ClientCmp> synchro_sockets_;
long long int Server::time_;
struct timeval Server::timeout_;
TcpSock * Server::srv_tcp_;
UdpSock * Server::srv_udp_;
UdpSock * Server::synchro_;

void Server::test() {
  printf("size = %d\n", clients_.size());
}

// Before use set it as nonblocking.
int Server::Recv () {
	if (srv_udp_->GetDescriptor() < 1)
  	return -1;
  
  struct Packet * pos = new struct Packet;
	int received_packages = 0;
  
  int sec = timeout_.tv_sec;
  int usec =  timeout_.tv_usec;
  fd_set recvfds;
  FD_ZERO(&recvfds);
  FD_SET(srv_udp_->GetDescriptor(), &recvfds);
	SockAddr * addr = new SockAddr();
  
	for (int i = 0; i < clients_.size(); i++) {
  	if (select(srv_udp_->GetDescriptor() + 1, &recvfds, NULL, NULL,
               &timeout_) > 0)
      
    	if (srv_udp_->recv(addr, pos) > 0) {
        
        if (clients_.find(addr) != clients_.end()) 
          
          if (pos->type == DELTA) {
            received_packages++;
            if (clients_[addr] == NULL)
              clients_[addr] = new ClientData(addr,
                                              (reinterpret_cast<struct CarPosition *>
                                               (pos->data))->x,
                                              (reinterpret_cast<struct CarPosition *>
                                               (pos->data))->y,
                                              (reinterpret_cast<struct CarPosition *>
                                               (pos->data))->angle);
            else
              clients_[addr]->AddDelta(reinterpret_cast<struct CarPosition *>
                                       (pos->data));
            printf("X = %f\n Y = %f\n", (reinterpret_cast<struct CarPosition *>
                                         (pos->data))->x,
                   (reinterpret_cast<struct CarPosition *>(pos->data))->y);
          }
    	}
    FD_ZERO(&recvfds);
    FD_SET(srv_udp_->GetDescriptor(), &recvfds);
    timeout_.tv_sec = sec;
    timeout_.tv_usec = usec;
  }

  delete pos;
	return received_packages;
}

int Server::Send () {
	if (srv_udp_->GetDescriptor() < 1)
  	return -1;
  
	int send_packages = 0;
  
	for (std::map<SockAddr *, ClientData *, ClientCmp>::iterator iter = clients_.begin();
       iter != clients_.end();
       iter++) {
    
		struct Packet * pos = new struct Packet;
    memcpy(pos->data, (*iter).second->GetPosition(), sizeof(struct CarPosition));
    pos->size = sizeof(struct CarPosition);
    
		if (srv_udp_->send((*iter).first,
                       pos) == sizeof(struct CarPosition))
    	send_packages++;
	}

	return send_packages;
}

Server::Server () {
	Server::my_addr_ = new SockAddr();
  Server::srv_udp_ = new UdpSock();
  Server::synchro_ = new UdpSock();
}

void * ListenToTcp(void * client_addr) {
  
}

Server::Server (short port, int timeout_sec,
                int timeout_microsec, int timeout_total) {
  
	assert((timeout_sec > 0) && (timeout_microsec >= 0) && (timeout_total > 0));
  
	Server::my_addr_ = new SockAddr (port);
	Server::srv_udp_ = new UdpSock();
  srv_udp_->bind(my_addr_);
  timeout_.tv_sec = timeout_sec;
  timeout_.tv_usec = timeout_microsec;
  
	long long int retries = timeout_total / timeout_sec;
  
  fd_set recvfds;
  FD_ZERO(&recvfds);
  FD_SET(srv_udp_->GetDescriptor(), &recvfds);
  
	SockAddr * buf_addr = new SockAddr;
  struct Packet * init_message = new struct Packet;
	struct Packet * accept_message = new struct Packet;
  
	strncpy(accept_message->data, "You're accepted!",
          strlen("You're accepted!"));
  accept_message->size = strlen("You're accepted!");
  
  for (int i = 0; i < retries; i++) {
  	if (select(srv_udp_->GetDescriptor() + 1, &recvfds, NULL, NULL,
               &timeout_) > 0) {

      int recv_len = 0;
    	if (recv_len = srv_udp_->recv(buf_addr, init_message) ==
      		strlen("I want to play!"))
        printf("received data size = %d\n", recv_len);
        
				if (clients_.find(buf_addr) == clients_.end())
	        // strlen("You're acdepted!") == 16.
    	    if (srv_udp_->send(buf_addr, accept_message) == 16)
  	      	clients_[buf_addr] = new ClientData();
      printf("message = %s\n", init_message->data);
		}
    FD_ZERO(&recvfds);
    FD_SET(srv_udp_->GetDescriptor(), &recvfds);
    timeout_.tv_sec = timeout_sec;
    timeout_.tv_usec = timeout_microsec;
  }
}

void * Server::Synhro(void * client) {
  if (client == NULL)
    return (void *)(-1);
  
	SockAddr * client_casted = reinterpret_cast<SockAddr *> (client);
  
  struct Packet * pack_synchro = new struct Packet;
  pack_synchro->type = SYNHRO;
  
  if (clients_.find(client_casted) == clients_.end())
    return (void *)(-1);
  
  const struct CarPosition * client_position = clients_[client_casted]->GetPosition();
  struct Synchro * synchro_data = new struct Synchro;
  synchro_data->x = client_position->x;
  synchro_data->y = client_position->y;
  synchro_data->angle = client_position->angle;
  synchro_data->speed = client_position->speed;
  synchro_data->steer_speed = client_position->steer_speed;
  synchro_data->time = time_;
	memmove(pack_synchro->data, synchro_data, sizeof(struct Synchro));
  
  int synchro_sended = 0;
  int synchro_failed = 0;
  
  while ((synchro_sended + synchro_failed) < 100) {
    if (srv_udp_->send(client_casted, pack_synchro) != sizeof(struct Packet)) {
    	synchro_failed++;
      if (synchro_failed > 50)
        return (void *)(-1);
    } else
      synchro_sended++;
  }
/*
  int synchro_total = synchro_sended + synchro_failed;

  fd_set srv_fdset;
  FD_ZERO(&srv_fdset);
  FD_SET(srv_udp_->GetDescriptor(), &srv_fdset);
  int sec = timeout_.tv_sec;
  int usec = timeout_.tv_usec;

  while (synchro_total > 0) {
    if (select(srv_udp_->GetDescriptor() + 1, &srv_fdset, NULL, NULL, &timeout_) > 0) {
      
    }
  }
*/
  delete pack_synchro;
}

int Server::Synhronize() {
  pthread_t tids[clients_.size()];
  std::map<SockAddr* ,bool, ClientCmp> sinchronized_clients;
  
  int client_num = 0;
	for (std::map<SockAddr *, ClientData *, ClientCmp>::iterator
       client_iter = clients_.begin();
       client_iter != clients_.end();
       client_iter++) {
		pthread_create(&tids[client_num], NULL, &Synhro, reinterpret_cast<void *>
                   ((*client_iter).first));
    sinchronized_clients[((*client_iter).first)] = false;
    client_num++;
	}
  
	int srv_fd = srv_udp_->GetDescriptor();
  fd_set srv_fdset;
  
  char answer_data[] = "Synchronized!";
  size_t answer_len = strlen(answer_data);
  
  FD_ZERO(&srv_fdset);
  FD_SET(srv_fd, &srv_fdset);
  int sec = timeout_.tv_sec;
  int usec = timeout_.tv_usec;

  SockAddr client_addr;
  struct Packet * answer = new struct Packet;
  int shall_cont = clients_.size();
	int iterations = 0;
  
  while (shall_cont > 0) { 
    FD_ZERO(&srv_fdset);
    FD_SET(srv_fd, &srv_fdset);
    
  	if (select(srv_fd + 1, &srv_fdset, NULL, NULL, &timeout_) > 0) {
    	if (srv_udp_->recv(&client_addr, answer) > 0) {
        
      	if (strncmp(answer->data, answer_data, answer_len) == 0 &&
            answer->type == SYNHRO) {
          
          if (clients_.find(&client_addr) != clients_.end()) {
            sinchronized_clients[&client_addr] = true;
            shall_cont--;
            iterations++;
          }
      	} else {
          if (iterations > clients_.size() * 10)
            break;
          continue;
        }
    	}
  	}

    FD_ZERO(&srv_fdset);
    FD_SET(srv_fd, &srv_fdset);
    timeout_.tv_sec = sec;
    timeout_.tv_usec = usec;
  }

  int sinchronized_clients_num = sinchronized_clients.size();

  for (std::map<SockAddr* ,bool, ClientCmp>::iterator client_iter =
       sinchronized_clients.begin();
       client_iter != sinchronized_clients.end();
       client_iter++) {

  	if (sinchronized_clients[(*client_iter).first] == false) {
    	sinchronized_clients_num--;
      Disconnect((*client_iter).first);
    }
  }

  delete answer;
  return sinchronized_clients_num;
}

bool Server::Disconnect(SockAddr * client) {
	for (int i = 0; i < 100; i++) {
  	;//srv_udp_->send()
  }
}
