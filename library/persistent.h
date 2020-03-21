#ifndef _PERSISTENT_H__

#define _PERSISTENT_H__

#include <file.h>
#include <hash.h>
#include <list.h>

typedef struct writable_hash_s writable_hash_t;

typedef struct writable_data_s writable_data_t;

typedef struct writable_element_s writable_element_t;

int createWritableHash(hash_t*, writable_hash_t*);
int printWritableHash(writable_hash_t*);
writable_hash_t* newWritableHash();
writable_data_t* newWritableData();
writable_element_t* newWritableElem();
int writeList(char* filename, list_t* lst);
int readList(char* filename);
int readElem(fileop_t* fl,writable_element_t* buf);
int readKElem(fileop_t* fl,writable_element_t *buf,int k);
int printWritableElem(writable_element_t* elem);

#endif
