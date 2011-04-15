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
    std::cerr << "Error in " << this->error_description_ << std::endl
        << "\tCode: " << this->error_code_ << std::endl
	<< "\tDesc: " << strerror (this->error_code_) << std::endl;
}

SockAddr::SockAddr () {
    this->address_ = new struct sockaddr_in;
    this->address_->sin_family = AF_INET;
    this->address_->sin_addr.s_addr = INADDR_ANY;
}

SockAddr::SockAddr (unsigned short port) {
    this->address_ = new struct sockaddr_in;
    this->address_->sin_family = AF_INET;
    this->address_->sin_addr.s_addr = INADDR_ANY;
    this->address_->sin_port = htons (port);
}

SockAddr::SockAddr (const char * ip, unsigned short port) {
    this->address_ = new struct sockaddr_in;
    this->address_->sin_family = AF_INET;
    inet_aton(ip, &(this->address_->sin_addr));

    if (this->address_->sin_addr.s_addr == INADDR_NONE)
        if (strncmp(ip, "255.255.255.255", strlen(ip)) != 0) {
            throw SockExept ("Socket - invalid address");
            delete this->address_;
        }

    this->address_->sin_port = htons (port);
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
        reinterpret_cast <const struct sockaddr *>((const_cast<SockAddr *>(addr))->GetAddr()),
        sizeof (struct sockaddr_in)) == 0)
        return true;

    return false;
}

bool UdpSock::bind (const SockAddr * addr) {
    if (::bind (this->socket_descriptor_,
        reinterpret_cast <const struct sockaddr*>((const_cast<SockAddr *>(addr))->GetAddr()),
        sizeof (struct sockaddr_in)) == 0)
        return true;

    return false;
}

UdpSock::UdpSock () {
    this->socket_descriptor_ = socket(PF_INET, SOCK_DGRAM, 0); 
    if (this->socket_descriptor_ == -1)
        throw SockExept("Сокет не работает!!1111");
}

UdpSock::~UdpSock() {
    if (this->socket_descriptor_ > 0)
        ::close(this->socket_descriptor_);
}
int UdpSock::send (const SockAddr * dest, const void * data, int len) {
    return sendto (this->socket_descriptor_, (void *)data, (size_t)len,
        MSG_DONTWAIT, reinterpret_cast <const sockaddr *> ((const_cast<SockAddr *>(dest))->GetAddr()),
        sizeof (struct sockaddr_in));
}

int UdpSock::recv (SockAddr * dest, void * data, int len) {
    assert(data != (char *)NULL);
    unsigned int dest_len = sizeof (struct sockaddr_in);
    return recvfrom(this->socket_descriptor_, (void *)data, len, MSG_WAITALL,
        reinterpret_cast <sockaddr *> (const_cast<sockaddr_in *>(dest->GetAddr())),
        &dest_len);
}

bool UdpSock::connect(SockAddr* srv) {
  assert(srv != (SockAddr *)NULL);
  if (this->socket_descriptor_ > 0)
    if (::connect(this->socket_descriptor_,
      reinterpret_cast<struct sockaddr *>(const_cast<struct sockaddr_in *>(srv->GetAddr())),
      sizeof (struct sockaddr_in)) == 0)
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
        reinterpret_cast <const struct sockaddr*>((const_cast<SockAddr *>(addr))->GetAddr()),
        sizeof (struct sockaddr_in)) == 0)
        return true;

    return false;
}

TcpSock::TcpSock () {
    this->socket_descriptor_ = socket(PF_INET, SOCK_STREAM, 0);
    if (this->socket_descriptor_ == -1)
        throw SockExept ("Сокет не работает!");
}

TcpSock::~TcpSock() {
    if (this->socket_descriptor_ > 0)
        ::close(this->socket_descriptor_);
}

int TcpSock::send (const SockAddr * dest, const void * data, int len) {
    return ::send(this->socket_descriptor_, (void *)data, (size_t)len,
      MSG_DONTWAIT);
}

int TcpSock::recv (SockAddr * dest = (SockAddr *)NULL,
    void * data = (char *)NULL, int len = 0) {

    assert(data != (char *)NULL);
    return ::recv(this->socket_descriptor_, (void *)data, len, MSG_WAITALL);
}


bool TcpSock::connect(SockAddr* srv) {
    assert(srv != (SockAddr *)NULL);
    if (this->socket_descriptor_ > 0)
        if (::connect(this->socket_descriptor_,
          reinterpret_cast<struct sockaddr *>(const_cast<struct sockaddr_in *>(srv->GetAddr())),
          sizeof (struct sockaddr_in)) == 0)
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
