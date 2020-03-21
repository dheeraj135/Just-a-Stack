#ifndef _PERSISTENT_PRIVATE_H__

#define _PERSISTENT_PRIVATE_H__

#include <persistent.h>
#include <list-private.h>
#include <hash-private.h>
#include <file-private.h>

int createWritableData(data_t*, writable_data_t*);
int createWritableElem(element_t*, writable_element_t*);

struct writable_hash_s{
    unsigned char hash[HASH_LENGTH];
};

struct writable_data_s{
    unsigned char str[MAX_DATA_LENGTH];
    int32_t len;
    writable_hash_t strhash;
};

struct writable_element_s{
    writable_hash_t prevHash;
    writable_data_t info;
    writable_hash_t hash;
};

#endif