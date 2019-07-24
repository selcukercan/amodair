#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <sys/types.h>

#include <string>
#include "socket.h"

using namespace std;

// Unix Socket Address Definition
struct sockaddr_unix
{
	sa_family_t sun_family;
	char sun_path[108]; /* pathname */
};

int main()
{
	string FD_ADDRESS = "/home/selcuk/amodair/sockets/socket_1";
	const char *SOCKET_ADDRESS = FD_ADDRESS.c_str();
	int BUFFER_SIZE = 12;
	char buffer[BUFFER_SIZE];
	int backlog = 1;
	int SOCKET_TYPE = -1;

	Socket my_socket(SOCKET_TYPE, FD_ADDRESS);
	// Socket Description
	int sfd = my_socket.initializeSocket(AF_UNIX, SOCK_STREAM, 0);

	// Socket Address
	sockaddr_unix socket;
	socket.sun_family = AF_UNIX;
	strncpy(socket.sun_path, SOCKET_ADDRESS, sizeof(socket.sun_path) - 1);

	// Attempt to bind the socket
	int bind_stat = my_socket.bindSocket(sfd, socket);
	
	// Attempt to listen
	int listening = my_socket.listenSocket(sfd, backlog);

	// Attempt to accept
	int cfd = my_socket.acceptCall(sfd, NULL, NULL);

	while (true)
	{
		// Attempt to read
		int reading = my_socket.readSocket(cfd, buffer, BUFFER_SIZE);
		printf(buffer);
	}
}
