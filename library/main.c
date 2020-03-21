#include <hash.h>
#include <list.h>
#include <persistent.h>
#include <file.h>
#include <errno.h>

int main()
{
    unsigned char* str = "Hello world";
    unsigned char* str2 = "Kill world";

    list_t* lst = newList();
    pushListStr(lst,"Hello");
    pushListStr(lst,"Baby");
    pushListStr(lst,"FOFF");
    printList(lst,0);
    // writeList("test.txt",lst);
    deleteList(lst);
    // readList("test.txt");
    // fileop_t* fl = fileOpen("test.txt",WRITEAPPENDMOD);
    // printf("%x\n",fl);
    // fprintf(stdout,"%d %s\n",fileWrite(fl,(const void*)str,strlen(str)),strerror(errno));
    // fileClose(fl);
    // fl = fileOpen("test.txt",READMOD);
    // char buf[PATH_MAX];
    // fileRead(fl,(void*)buf,PATH_MAX-1);
    // fileClose(fl);
    // printf("Content: %s\n",buf);
    
    // fileop_t* fl = fileOpen("test.txt",READMOD);
    // writable_element_t* elem = newWritableElem();
    // while(!iseof(fl))
    // {
    //     readElem(fl,elem);
    //     printWritableElem(elem);
    // }
    // readKElem(fl,elem,10);
    // free(elem);
    // fileClose(fl);
    return 0;
}