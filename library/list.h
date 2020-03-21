#ifndef LIST_H

#define LIST_H 1

#include <hash.h>
#define MAX_DATA_LENGTH 1024

typedef struct list_s list_t;
typedef struct element_s element_t;

list_t* newList();
int pushListStr(list_t* lst, char* str);
void printList(list_t* lst,int verbosity);
void printElem(element_t* elem);
int verifyList(list_t* lst);
void deleteList(list_t* lst);
element_t* newElement2();

#endif