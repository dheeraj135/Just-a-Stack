#ifndef _PERSISTENT_H__

#define _PERSISTENT_H__

#include <file.h>
#include <hash.h>
#include <list.h>


int writeList(char* filename, list_t* lst);
int readList(char* filename);
int readElem(fileop_t* fl,element_t* buf);
int readKElem(fileop_t* fl,element_t *buf,int k);

#endif
