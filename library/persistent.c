#include <persistent-private.h>

int writeElement(fileop_t* file, element_t wrt)
{
    return fileWrite(file,(void*)(&wrt),sizeof(wrt));
}

int writeList(char* filename, list_t* lst)
{
    lst->curr = lst->head;
    fileop_t* file = fileOpen(filename,WRITENEWMOD);
    while(lst->curr)
    {
        writeElement(file,lst->curr->elem);
        lst->curr = lst->curr->next;
    }
    fileClose(file);
}

int readList(char* filename)
{
    fileop_t* fl = fileOpen(filename,READMOD);
    element_t wrt;
    while(fileRead(fl,(void*)(&wrt),sizeof(wrt)))
    {
        printf("%s\n",wrt.info.str);
    }
    fileClose(fl);
}

int readKElem(fileop_t* fl,element_t *buf,int k)
{
    if (fl==NULL)
        return -1;
    if (fl->mod != READMOD)
        return -1;
    
    fileSeek(fl,k*(sizeof(element_t)),FILEBEGIN);
    return fileRead(fl,buf,sizeof(element_t));
}

int readElem(fileop_t* fl,element_t* buf)
{
    if (fl==NULL)
        return -1;
    if (fl->mod != READMOD)
        return -1;
    return fileRead(fl,buf,sizeof(element_t));
}

int printWritableElem(element_t* elem)
{
    printf("%s\n",elem->info.str);
}