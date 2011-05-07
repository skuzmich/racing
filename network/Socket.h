/* 
 * File:   Socket.h
 * Author: destructor
 *
 * Created on 12 март 2011 ã., 1:46
 */

#ifndef SOCKET_H
#define	SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <string>

enum PacketType {SYNHRO, DELTA, INIT};

struct Packet {
  static const size_t MAX_PACKET = 1024;

	PacketType type;
  size_t size;
  char data[MAX_PACKET];
};

class SockExept {
public:
    SockExept (const char * error_string);
    ~SockExept (void);

    // Print error info.
    void Print (void);

    // Get error code.
    int	GetCode (void);
private:
    int	error_code_;
    std::string error_description_;    
};

class SockAddr {
private:
  SockAddr(SockAddr &orign);
	struct sockaddr_in * address_;

public:
    SockAddr (void);
    explicit SockAddr (unsigned short port);
    explicit SockAddr (const char * ip, unsigned short port);
    virtual ~SockAddr ();

    virtual bool SetIP (const char * ip);
    virtual bool SetPort (unsigned port);

		virtual const struct sockaddr_in * GetAddr (void);
    virtual const char * GetIP (void);
    virtual unsigned short GetPort (void);
};

class Sock_ {
private:
    Sock_(Sock_ &orirn);
    int socket_descriptor_;

public:
    explicit Sock_(void) {;};
		virtual ~Sock_ (void) {;};

    // Bind socket to network addres.
    virtual bool bind (const SockAddr * addr);
    // Send the message.
    virtual int send (const SockAddr * dest, const struct Packet * message) {;};
    // Receive a message.
    virtual int recv (SockAddr * dest, struct Packet * message) {;};

    // Connect to remote host.
    virtual bool connect(SockAddr *srv) {;};

    virtual bool close() {;};

    // Get socket descriptor.
    virtual int GetDescriptor(void) {;};

    // Set as unblocking descriptor.
    virtual bool DisableBlocking(void) {return true;}
};

class TcpSock: public Sock_ {
public:
    TcpSock();
    virtual ~TcpSock();

    // Bind socket to network addres.
    virtual bool bind (const SockAddr * addr);

    // Send the message. dest may be NULL pointer.
    virtual int send (const SockAddr * dest, const struct Packet * message);

    // Receive a message.
    virtual int recv (SockAddr * dest, struct Packet * message);

    // Close the descriptor.
    virtual bool close(void);

    // Connect to remote host.
    virtual bool connect(SockAddr *srv);

    TcpSock * accept(SockAddr *srv);

    // Get socket descriptor.
    virtual int GetDescriptor(void);

    // Set socket descriptor. sd must be valid socket descriptor.
    bool SetDescriptor(int sd);

    bool listen(int backlog);
 
    // Set as unblocking descriptor.
    virtual bool DisableBlocking(void);
  
private:
    // TODO(Lega): write a copy constructor, and destructor that doesn't close
    // the socket descriptor. The same for UdpSock.
    int socket_descriptor_;
  TcpSock (TcpSock &orign);
};

class UdpSock: public Sock_ {
public:
    UdpSock();
    virtual ~UdpSock();

    // Bind socket to network addres.
    virtual bool bind (const SockAddr * addr);

    // Send the message.
    virtual int send (const SockAddr * dest, const struct Packet * message);

    // Receive a message.
    virtual int recv (SockAddr * dest, struct Packet * message);

    // Close the descriptor.
    virtual bool close(void);

    // Connect to remote host.
    virtual bool connect(SockAddr *srv);

    // Get socket descriptor.
    virtual int GetDescriptor() {
        return this->socket_descriptor_;
    }

    // Set as broadcast socket.
    bool EnableBroadcasting (void);

    // Disable broadcasting.
    bool DisableBroadcasting(void);

    // Set as unblocking descriptor.
    virtual bool DisableBlocking(void){ return true;};

private:
    UdpSock(UdpSock &orign);
    int socket_descriptor_;
};

#endif	// SOCKET_H
