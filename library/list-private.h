#ifndef _LIST_PRIVATE_H__
#define _LIST_PRIVATE_H__

#include <list.h>
#include <hash.h>

typedef struct data_s{
    unsigned char* str; /* MAX_DATA_LENGTH */
    int32_t len;
    hash_t* strhash;
}data_t;

typedef struct element_s{
    struct element_s* next;
    hash_t* prevHash;
    data_t* info;
    hash_t* hash;
}element_t;

struct list_s{
    element_t* head;
    element_t* tail;
    element_t* curr;
};

#endif