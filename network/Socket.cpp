/* 
 * File:   Socket.h
 * Author: destructor
 *
 * Created on 13 март 2011 ã., 0:29
 */

#include <assert.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#include <iostream>
#include <string>
#include <cstring>

#include "Socket.h"

SockExept::SockExept (const char * error_string) {
    this->error_description_ += error_string;
    this->error_code_ = errno;
}

SockExept::~SockExept() {
    ;
}

void SockExept::Print () {
    std::cerr << "Error in " << error_description_ << std::endl
        << "\tCode: " << error_code_ << std::endl
	<< "\tDesc: " << strerror (error_code_) << std::endl;
}

SockAddr::SockAddr () {
    address_ = new struct sockaddr_in;
    address_->sin_family = AF_INET;
    address_->sin_addr.s_addr = INADDR_ANY;
}

SockAddr::SockAddr (unsigned short port) {
    address_ = new struct sockaddr_in;
    address_->sin_family = AF_INET;
    address_->sin_addr.s_addr = INADDR_ANY;
    address_->sin_port = htons (port);
}

SockAddr::SockAddr (const char * ip, unsigned short port) {
    address_ = new struct sockaddr_in;
    address_->sin_family = AF_INET;
    inet_aton(ip, &(address_->sin_addr));

    if (address_->sin_addr.s_addr == INADDR_NONE)
        if (strncmp(ip, "255.255.255.255", strlen(ip)) != 0) {
            throw SockExept ("Socket - invalid address.");
            delete address_;
        }

    address_->sin_port = htons (port);
}

SockAddr::~SockAddr(void) {
    if (this->address_)
        delete this->address_;
}

bool SockAddr::SetIP (const char * ip) {
    if (ip)
        if (this->address_)
            if (this->address_->sin_addr.s_addr = inet_addr (ip))
								return true;
    return false;
}

bool SockAddr::SetPort (unsigned int port) {
    if (this->address_)
        if (this->address_->sin_port = htons (port))
            return false;
    return false;
}

const struct sockaddr_in * SockAddr::GetAddr (void) {
    if (this->address_)
        return this->address_;
    return (struct sockaddr_in *)NULL;
}

const char * SockAddr::GetIP (void) {
    if (this->address_)
        return inet_ntoa(this->address_->sin_addr);
    return (char *)NULL;
}

unsigned short SockAddr::GetPort (void) {
    if (this->address_)
        return ntohs (this->address_->sin_port);
    return -1;
}

bool Sock_::bind (const SockAddr * addr) {
    if (::bind (this->socket_descriptor_,
         reinterpret_cast <const struct sockaddr *>((const_cast<SockAddr *>
         (addr))->GetAddr()), sizeof (struct sockaddr_in)) == 0)
        return true;

    return false;
}

bool UdpSock::bind (const SockAddr * addr) {
    if (::bind (this->socket_descriptor_,
         reinterpret_cast <const struct sockaddr*>((const_cast<SockAddr *>
         (addr))->GetAddr()), sizeof (struct sockaddr_in)) == 0)
        return true;

    return false;
}

UdpSock::UdpSock () {
    this->socket_descriptor_ = socket(PF_INET, SOCK_DGRAM, 0); 
    if (this->socket_descriptor_ == -1)
        throw SockExept("There aren't any avalaible UDP sockets.");
}

UdpSock::~UdpSock() {
    if (this->socket_descriptor_ > 0)
        ::close(this->socket_descriptor_);
}

int UdpSock::send (const SockAddr * dest, const struct Packet * message) {
		if (message->size < 0)
    	return -1;
    if (sendto (this->socket_descriptor_, (void *)message,
    		 sizeof(PacketType) + sizeof(size_t) + message->size, MSG_DONTWAIT,
         reinterpret_cast <const sockaddr *> ((const_cast<SockAddr *>(dest))->GetAddr()),
         sizeof (struct sockaddr_in)) == sizeof(PacketType) +
         message->size + sizeof(size_t))
      return message->size;
    return -1;
}

int UdpSock::recv (SockAddr * dest, struct Packet * message) {

		if (message == NULL)
        return -1;

    unsigned int dest_len = sizeof (struct sockaddr_in);

    if (recvfrom(this->socket_descriptor_, (void *)message,
    		 sizeof(int) + sizeof(message->type) + MAX_PACKET, MSG_WAITALL,
         reinterpret_cast <sockaddr *> (const_cast<sockaddr_in *>
         (dest->GetAddr())), &dest_len) > 0)
        return message->size;
}

bool UdpSock::connect(SockAddr* srv) {

  assert(srv != (SockAddr *)NULL);

  if (this->socket_descriptor_ > 0)

    if (::connect(this->socket_descriptor_,

      reinterpret_cast<struct sockaddr *>(const_cast<struct sockaddr_in *>
       (srv->GetAddr())), sizeof (struct sockaddr_in)) == 0)

      return true;

  return false;
}

bool UdpSock::close() {
    if (this->socket_descriptor_ > 0)
        if (::close(this->socket_descriptor_) == 0)
            return true;

    return false;
}

bool UdpSock::EnableBroadcasting() {
  if (this->socket_descriptor_ < 1)
    return false;
  int i = 1;
  if (setsockopt(this->socket_descriptor_, SOL_SOCKET, SO_BROADCAST, &i,
    	sizeof(i)) < 0)
    return false;
  return true;
}

bool UdpSock::DisableBroadcasting() {
  if (this->socket_descriptor_ < 1)
    return false;
  int i = 0;
  if (setsockopt(this->socket_descriptor_, SOL_SOCKET, SO_BROADCAST, &i,
   	 sizeof(i)) < 0)
    return false;
  return true;
}

bool TcpSock::bind (const SockAddr * addr) {
    if (::bind (this->socket_descriptor_,
				 reinterpret_cast <const struct sockaddr*>((const_cast<SockAddr *>
    		 (addr))->GetAddr()), sizeof (struct sockaddr_in)) == 0)
        return true;

    return false;
}

TcpSock::TcpSock () {
    this->socket_descriptor_ = socket(PF_INET, SOCK_STREAM, 0);
    if (this->socket_descriptor_ == -1)
        throw SockExept ("There aren't any avalaible sockets!");
}

TcpSock::~TcpSock() {
    if (this->socket_descriptor_ > 0)
        ::close(this->socket_descriptor_);
}

int TcpSock::send (const SockAddr * dest, const struct Packet * message) {
    return ::send(this->socket_descriptor_, (void *)message,
    	sizeof(int) + sizeof(message->type) + message->size, MSG_DONTWAIT);
}

int TcpSock::recv (SockAddr * dest, struct Packet * message) {

    assert(message != NULL);
    return ::recv(this->socket_descriptor_, (void *)message,
    		sizeof(int) + sizeof(message->type) + MAX_PACKET, MSG_WAITALL);
}


bool TcpSock::connect(SockAddr* srv) {
    assert(srv != (SockAddr *)NULL);
    if (this->socket_descriptor_ > 0)
        if (::connect(this->socket_descriptor_,
          	reinterpret_cast<struct sockaddr *>(const_cast<struct sockaddr_in *>
          	(srv->GetAddr())), sizeof (struct sockaddr_in)) == 0)
          return true;
    return false;
}

bool TcpSock::close() {
    if (this->socket_descriptor_ > 0)
      if (::close(this->socket_descriptor_) == 0)
        return true;
    return false;
}

// TODO(Lega): add authorization by checking of the srv->GetAddr()
TcpSock * TcpSock::accept(SockAddr* srv) {
    assert(srv != (SockAddr *)NULL);
    int sd;

    if (this->socket_descriptor_ > 0)
      sd = ::accept(this->socket_descriptor_,
        reinterpret_cast<struct sockaddr *>(const_cast<struct sockaddr_in *>(srv->GetAddr())),
        (socklen_t *)NULL);

  if (sd > 0) {
    TcpSock * result = new TcpSock();
    result->close();
    result->SetDescriptor(sd);
    return result;
  }

    return (TcpSock *)NULL;
}

int TcpSock::GetDescriptor() {
  return this->socket_descriptor_;
}

bool TcpSock::SetDescriptor(int sd) {
  if (sd < 1024)
    return false;

  this->close();
  this->socket_descriptor_ = sd;
  return true;
}

bool TcpSock::listen(int backlog) {
  if (backlog < 1)
    return false;

  if (::listen(this->socket_descriptor_, backlog))
    return false;
  return true;
}

bool TcpSock::DisableBlocking () {
  if (this->socket_descriptor_ < 1025)
    return false;
  
  return true;
}
