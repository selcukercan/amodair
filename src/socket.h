#pragma once

#include "socket.h"
#include <sys/socket.h>
#include <stdexcept>
#include <string>
#include <unistd.h> // read()
// Print Error
#define handle_error(msg)   \
    do                      \
    {                       \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)

using namespace std;
using std::string;

class Socket
{
public:
    Socket(int SOCKET_TYPE, string SOCKET_ADDRESS);
    ~Socket();

    int initializeSocket(int DOMAIN, int CONNECTION_TYPE, int protocol_type);
    template <class T>
    int bindSocket(int fd, T socket);
    int listenSocket(int sfd, int backlog);
    int acceptCall(int sfd, int caddr, int caddrlen);
    int readSocket(int cfd, char *buffer, int BUFFER_SIZE);

private:
    // socket initialization
    int DOMAIN_ = -1;
    int CONNECTION_TYPE_ = -1;
    int protocol_type_ = -1;
    // socket binding
    int fd = -1;
    const char *SOCKET_ADDRESS_ = NULL;
    // client interaction
    int backlog_ = -1;
    int sfd = -1;
    int caddr = -1;
    int caddrlen = -1;
};

Socket::Socket(int SOCKET_TYPE, string SOCKET_ADDRESS)
{
    SOCKET_ADDRESS_ = SOCKET_ADDRESS.c_str();
    // Close the connection if previous connection remained unclosed
    unlink(SOCKET_ADDRESS_);
}

Socket::~Socket()
{
    // Close the connection before the object is destroyed
    unlink(SOCKET_ADDRESS_);
}

int Socket::initializeSocket(int DOMAIN, int CONNECTION_TYPE, int protocol_type)
{
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

    // Check socket initialization success
    if (sfd == -1)
    {
        handle_error("Failed to create a file descriptor for the new socket");
    }
    else
    {
        std::cout << "Successfully to create a socket!" << std::endl;
    }

    return sfd;
}

template <class T>
int Socket::bindSocket(int fd, T socket)
{
    // Attempt to bind
    // Bind generated socket **sfd** to socket address **socket**
    //int bind_stat = bind(sfd, (const struct sockaddr *) &socket, sizeof(struct sockaddr_unix));
    //unlink(socket.sun_path);
    int bind_stat = bind(fd, (const struct sockaddr *)&socket, sizeof(T));

    // Check binding success
    if (bind_stat == -1)
    {
        handle_error("Failed to bind");
    }
    return bind_stat;
}

int Socket::listenSocket(int sfd, int backlog)
{
    // Allowed size of the queue *backlog* for waiting for connecting **sfd**
    int list_stat = listen(sfd, backlog);

    // Check listening success
    if (list_stat == -1)
    {
        handle_error("Failed to listen");
    }
    return list_stat;
}

int Socket::acceptCall(int sfd, int caddr, int caddrlen)
{
    // see: http://www.linuxhowtos.org/manpages/2/accept.htm
    //The accept() system call is used with connection-based socket types (SOCK_STREAM, SOCK_SEQPACKET).
    //It extracts the first connection request on the queue of pending connections for the listening socket,
    //sockfd, creates a new connected socket, and returns a new file descriptor referring to that socket.
    int scfd = 0; // TODO Is it a problem to initialize to 0?

    if (caddr == NULL)
    {
        scfd = accept(sfd, NULL, NULL); // fd of the connected socket
    }
    else
    {
        throw std::logic_error("Function not yet implemented");
    }
    return scfd;
}

int Socket::readSocket(int cfd, char *buffer, int BUFFER_SIZE)
{
    int read_stat = read(cfd, buffer, BUFFER_SIZE);
    if (read_stat == -1)
    {
        handle_error("Failed to read the buffer");
    }

    return read_stat;
}
