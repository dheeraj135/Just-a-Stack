#ifndef _FILE_PRIVATE_H__
#define _FILE_PRIVATE_H__

#include <headers.h>
#include <file.h>

struct fileop_s{
    int fd;
    char filename[PATH_MAX];
    enum FILEMOD mod;
};

#endif