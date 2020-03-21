#include <file-private.h>

fileop_t* newFileop()
{
    fileop_t* fl = calloc(1, sizeof(fileop_t));
    return fl;
}

fileop_t* fileOpen(char* filename,enum FILEMOD mod)
{
    fileop_t* fl = newFileop();
    if (fl==NULL)
        return NULL;
    int md = 0;
    mode_t perm = S_IWUSR|S_IRUSR;

    if (mod==READMOD)
        md = O_RDONLY;
    else
    {
        md = O_CREAT|O_WRONLY;
        if (mod==WRITEAPPENDMOD)
            md |= O_APPEND;
        else md |= O_TRUNC;
    }

    strlcpy(fl->filename,filename,PATH_MAX);
    fl->fd = open(fl->filename,md,perm);
    // printf("%d %d %d %s\n",fl->fd,perm,md,fl->filename);
    fl->mod = mod;
    return fl;
}

int fileClose(fileop_t* file)
{
    close(file->fd);
    free(file);
    return 0;
}

int fileWrite(fileop_t* file,const void* data, int len)
{
    if (file ==NULL)
        return -1;
    if (file->fd <=0 || file->filename == NULL)
        return -1;
    if (data == NULL)
        return -1;
    if (file->mod != WRITEAPPENDMOD && file->mod != WRITENEWMOD)
        return -1;
    return write(file->fd, data, len);
}

int fileRead(fileop_t* file, void* data, int len)
{
    if (file ==NULL) 
        return -1;
    if (file->fd <=0 || file->filename == NULL)
        return -1;
    if (data == NULL)
        return -1;
    if (file->mod != READMOD)
        return -1;
    return read(file->fd, data,len);
}

int fileSeek(fileop_t* file,int offset,int whence)
{
    if (file==NULL)
        return -1;
    if (file->fd <=0 || file->filename == NULL )
        return -1;
    return lseek(file->fd,offset,whence);
}

int iseof(fileop_t* fl)
{
    if (fl==NULL)
        return -1;

    char buf[2];
    int res = fileRead(fl,&buf,1);
    if(res<0)
        return res;
    int res2 = fileSeek(fl,-1*res,FILECURR);
    if (res2<0 )
        return -1;

    return (1^res);
}