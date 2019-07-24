#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include "socket.h"


using namespace std;
// Socker Address, file-like.


// Print Error
#define handle_error(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0) 

// Unix Socket Address Definition
struct sockaddr_unix{
sa_family_t sun_family;
char        sun_path[108]; /* pathname */ }; 


int main() {
	string tmp11 = "/home/selcuk/amodair/sockets/socket_1";
	const char * SOCKET_ADDRESS = tmp11.c_str();
	int BUFFER_SIZE = 12; 
	// Close the connection if previous connection remained unclosed
	unlink(SOCKET_ADDRESS);

	// Socket Creation
	// see: http://www.linuxhowtos.org/manpages/2/socket.htm
	// socket(domain, type, protocol)
	// The **domain** argument specifies a communication domain
	//   AF_UNIX -> local communication
	// The socket has the indicated **type**, which specifies the communication semantics.
	//   SOCK_STREAM -> TCP
	// The protocol indicates the **protocol** used for communication
	//   0 -> Default Protocol
	// socket(..) generates a files descriptor on linux

	Socket my_socket;
	// Socket Description
	int sfd = my_socket.initializeSocket(AF_UNIX, SOCK_STREAM, 0);
	if(sfd == -1){
		handle_error("Failed to create a file descriptor for the new socket");
	}
	else{
		std::cout << "Successfully to create a socket!" << std::endl;
	}

	// Socket Address 
	sockaddr_unix socket;
	socket.sun_family = AF_UNIX;
	strncpy(socket.sun_path, SOCKET_ADDRESS, sizeof(socket.sun_path) - 1);


	// Socket Binding 
	// Attempt to bind
	// Bind generated socket **sfd** to socket address **socket** 
	//int bind_stat = bind(sfd, (const struct sockaddr *) &socket, sizeof(struct sockaddr_unix));
	int bind_stat = my_socket.bindSocket(sfd, socket);
	// Check for binding success
	if(bind_stat == -1){
		 handle_error("Failed to bind");
	}

	// Attempt to listen
	// Allowed size of the queue for waiting for connecting **sfd** 
	int backlog = 1;
	int listening = listen(sfd, backlog);

	if(listening == -1){
		handle_error("Failed to listen");
	}

	// Attempt to accept
	// Start accepting the calls on the socket
	char buffer[BUFFER_SIZE]; 
	sockaddr_unix  client_socket;
	//int cfd = accept(sfd, (struct sockaddr *) &client_socket, (socklen_t*) &sizeof(client_socket)); 
	int cfd = accept(sfd, NULL, NULL);

	while(true){
	// Attemp to read
	int reading = read(cfd, buffer, BUFFER_SIZE);
	if (reading == -1) {
		handle_error("Failed to read the buffer");
	}
	// Ensure buffer is 0-terminated  
	buffer[BUFFER_SIZE - 1] = 0; 
	printf(buffer);
	}

	// Close the connection
	unlink(SOCKET_ADDRESS); 
}	
