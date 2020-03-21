#ifndef _FILE_H__
#define _FILE_H__

typedef struct fileop_s fileop_t;
enum FILEMOD {
    READMOD,
    WRITEAPPENDMOD,
    WRITENEWMOD
};

enum FILESEEK{
    FILEBEGIN,
    FILECURR,
    FILEEND
};

fileop_t* fileOpen(char* filename,enum FILEMOD);
int fileClose(fileop_t*);
int fileWrite(fileop_t*,const void*,int);
int fileRead(fileop_t*,void*,int);
int fileSeek(fileop_t*,int,int);
int iseof(fileop_t* fl);
#endif