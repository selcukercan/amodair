#pragma once
#include <string>

using std::string;

class Socket {
public:
Socket(string SOCKET_ADDRESS, int BUFFER_SIZE);
int createSocket();
private:
// socket creation
string SOCKET_ADDRESS_;
int BUFFER_SIZE_;
}; 
