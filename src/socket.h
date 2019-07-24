#pragma once

#include <string>
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