#include <persistent-private.h>

writable_hash_t* newWritableHash()
{
    return calloc(1,sizeof(writable_hash_t));
}

writable_data_t* newWritableData()
{
    return calloc(1,sizeof(writable_data_t));
}

writable_element_t* newWritableElem()
{
    return calloc(1,sizeof(writable_element_t));
}

int createWritableHash(hash_t* input, writable_hash_t* output)
{
    if (input==NULL || output == NULL) 
        return -1;
    // if (input == NULL)
    // {
    //     for (int i =0 ;i<HASH_LENGTH;i++)
    //         output->hash[i] = '#';
    //     return 0;
    // }
    strncpy(output->hash,input->hash,HASH_LENGTH);
    return 0;
}

int createWritableData(data_t* input, writable_data_t* output)
{
    if (input == NULL || output == NULL)
        return -1;
    strlcpy(output->str,input->str,MAX_DATA_LENGTH);
    output->len = strlen(output->str);
    createWritableHash(input->strhash,&(output->strhash));
}

int createWritableElem(element_t* input,writable_element_t* output)
{
    if (input==NULL || output == NULL)
        return -1;
    createWritableHash(input->prevHash,&(output->prevHash));
    createWritableHash(input->hash,&(output->hash));
    createWritableData(input->info,&(output->info));
}

int printWritableHash(writable_hash_t* input)
{
    for (int i=0;i<HASH_LENGTH;i++)
    printf("%02x",input->hash[i]);
    printf("\n");
    return 0;
}

int writeElement(fileop_t* file, writable_element_t wrt)
{
    return fileWrite(file,(void*)(&wrt),sizeof(wrt));
}

int writeList(char* filename, list_t* lst)
{
    lst->curr = lst->head;
    fileop_t* file = fileOpen(filename,WRITENEWMOD);
    while(lst->curr)
    {
        writable_element_t wrt;
        memset(&wrt,0,sizeof(wrt));
        createWritableElem(lst->curr,&wrt);
        writeElement(file,wrt);
        lst->curr = lst->curr->next;
    }
    fileClose(file);
}

int readList(char* filename)
{
    fileop_t* fl = fileOpen(filename,READMOD);
    writable_element_t wrt;
    while(fileRead(fl,(void*)(&wrt),sizeof(wrt)))
    {
        printf("%s\n",wrt.info.str);
    }
    fileClose(fl);
}

int readKElem(fileop_t* fl,writable_element_t *buf,int k)
{
    if (fl==NULL)
        return -1;
    if (fl->mod != READMOD)
        return -1;
    
    fileSeek(fl,k*(sizeof(writable_element_t)),FILEBEGIN);
    return fileRead(fl,buf,sizeof(writable_element_t));
}

int readElem(fileop_t* fl,writable_element_t* buf)
{
    if (fl==NULL)
        return -1;
    if (fl->mod != READMOD)
        return -1;
    return fileRead(fl,buf,sizeof(writable_element_t));
}

int printWritableElem(writable_element_t* elem)
{
    printf("%s\n",elem->info.str);
}