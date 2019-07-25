#include <sys/socket.h>

// Unix Socket Address Definition
struct sockaddr_unix
{
	sa_family_t sun_family;
	char sun_path[108]; /* pathname */
};


