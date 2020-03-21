#include <http.h>

int startServer(const int port)
{
    struct addrinfo host;
    memset(&host,0,sizeof(struct addrinfo));

    host.ai_family = AF_INET;
    host.ai_socktype = SOCK_STREAM;
    host.ai_flags = AI_PASSIVE;

    if (get)
}