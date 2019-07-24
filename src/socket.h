#pragma once

#include "socket.h"
#include <sys/socket.h>
#include <stdexcept>
#include <string>

// Print Error
#define handle_error(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0) 


using namespace std;
using std::string;

class Socket
{
public:
    Socket();
    ~Socket();

    int initializeSocket(int DOMAIN, int CONNECTION_TYPE, int protocol_type);
    template <class T>
    int bindSocket(int fd, T socket);
    int listenSocket(int sfd, int backlog);
    int acceptCall(int sfd, int caddr, int caddrlen);

private:
    // socket initialization
    int DOMAIN_ = -1;
    int CONNECTION_TYPE_ = -1;
    int protocol_type_ = -1;
    // socket binding
    int fd = -1;
    const char * SOCKET_ADDRESS_ = NULL;
    // client interaction
    int backlog_ = -1;
    int sfd = -1;
    int caddr = -1;
    int caddrlen = -1;
};

/* 
struct socketConfig{
    // socket initialization
    int DOMAIN_ = NULL;
    int CONNECTION_TYPE_ = NULL;
    int protocol_type_ = NULL;
    // socket binding
    int fd = NULL;
    string SOCKET_ADDRESS_ = NULL;
    // client interaction
    int backlog_ = NULL;
    int sfd = NULL;
    int caddr = NULL;
    int caddrlen = NULL;
}
*/


Socket::Socket() {}

Socket::~Socket() {}

int Socket::initializeSocket(int DOMAIN, int CONNECTION_TYPE, int protocol_type){
	// Socket Initialization
	// see: http://www.linuxhowtos.org/manpages/2/socket.htm
	// socket(domain, type, protocol)
	// The **domain** argument specifies a communication domain
	//   AF_UNIX -> local communication
	// The socket has the indicated **type**, which specifies the communication semantics.
	//   SOCK_STREAM -> TCP
	// The protocol indicates the **protocol** used for communication
	//   0 -> Default Protocol
	// socket(..) generates a files descriptor on linux

	int sfd = socket(DOMAIN, CONNECTION_TYPE, protocol_type);

	return sfd;
}

template <class T>
int Socket::bindSocket(int fd, T socket){
    // Attempt to bind
	// Bind generated socket **sfd** to socket address **socket** 
	//int bind_stat = bind(sfd, (const struct sockaddr *) &socket, sizeof(struct sockaddr_unix));
	//unlink(socket.sun_path); 
    int bind_stat = bind(fd, (const struct sockaddr *) &socket, sizeof(T)); 
	return bind_stat;
}


int Socket::listenSocket(int sfd, int backlog){
	int list_stat = listen(sfd, backlog);
	return list_stat;
}
	
int Socket::acceptCall(int sfd, int caddr, int caddrlen){
	// see: http://www.linuxhowtos.org/manpages/2/accept.htm
	//The accept() system call is used with connection-based socket types (SOCK_STREAM, SOCK_SEQPACKET). 
	//It extracts the first connection request on the queue of pending connections for the listening socket, 
	//sockfd, creates a new connected socket, and returns a new file descriptor referring to that socket.
	int scfd = 0; // TODO Is it a problem to initialize to 0?   

	if(caddr == NULL){
		int scfd = accept(sfd, NULL, NULL); // fd of the connected socket
	}
	else{
		throw std::logic_error("Function not yet implemented"); 
	}
	return scfd;
}

