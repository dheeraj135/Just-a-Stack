#ifndef LIST_H

#define LIST_H 1

#include <hash.h>
#define MAX_DATA_LENGTH 4096

typedef struct list_s list_t;


list_t* newList();
int pushListStr(list_t* lst, char* str);
void printList(list_t* lst,int verbosity);
int verifyList(list_t* lst);
void deleteList(list_t* lst);

#endif