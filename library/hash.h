#ifndef HASHING_H
#define HASHING_H 1

#include <headers.h>
#include <openssl/sha.h>

#define HASH_LENGTH SHA512_DIGEST_LENGTH
#define HASH_POLICY "SHA512"
#define HASH_NULL computeHash("---",3);

typedef struct hash_s hash_t;

hash_t* newHash();
hash_t* copyHash(hash_t* hash);
hash_t* computeHash(unsigned char* str,int len);

char* getStrHash(hash_t* hash);

int mergeHash (hash_t* first,   /* I - First Hash */
                hash_t* second, /* I - Second Hash */
                hash_t** out);   /* O- Output Hash */

int compareHash (hash_t* first,
                 hash_t* second);

void deleteHash(hash_t* ht);

#endif
