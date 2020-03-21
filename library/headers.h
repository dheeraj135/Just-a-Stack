#ifndef HEADERS_H
#define HEADERS_H 1

#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#ifndef HAVE_STRLCPY
size_t strlcpy(char* dest,char* src, size_t len);
#endif

#endif