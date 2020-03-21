#ifndef BLOCK_HTTP_H
#define BLOCK_HTTP_H 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <signal.h>

#define MAXCONN 100

typedef struct http_server_s{
    int fd;
    int port;
}http_server_t;

#endif