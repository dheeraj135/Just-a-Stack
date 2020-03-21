#ifndef _LIST_PRIVATE_H__
#define _LIST_PRIVATE_H__

#include <list.h>
#include <hash-private.h>

typedef struct data_s{
    unsigned char str[MAX_DATA_LENGTH]; /* MAX_DATA_LENGTH */
    int32_t len;
    hash_t strhash;
}data_t;

struct element_s{
    hash_t prevHash;
    data_t info;
    hash_t hash;
};

typedef struct lelement_s{
    struct lelement_s* next;
    element_t elem;
}lelement_t;

struct list_s{
    lelement_t* head;
    lelement_t* tail;
    lelement_t* curr;
};

#endif