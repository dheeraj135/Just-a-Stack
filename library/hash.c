
#include <hash-private.h>

int getHexHash(hash_t* hash,   /* I- */
                char** out);      /* O- */

hash_t* newHash()
{
    hash_t* nw;
    if ((nw = (hash_t*)calloc(1,sizeof(hash_t)) ) == NULL){
        return NULL;
    }

    return nw;
}

hash_t* computeHash(unsigned char* str,int len)
{
    hash_t* hashed = newHash();
    
    SHA512_CTX sha512;
    
    if (!SHA512_Init(&sha512))
        return NULL;
    if (!SHA512_Update(&sha512,str,len))
        return NULL;
    if (!SHA512_Final(hashed->hash,&sha512))
        return NULL;
    return hashed;
}

int getHexHash(hash_t* hash,   /* I- */
                char** out)      /* O- */
{
    if (hash == NULL)
    {
        out=NULL;
        return -1;
    }

    if ( (*out = calloc(2*HASH_LENGTH+1,sizeof(char))) == NULL)
    {
        return -1;
    }

    int i = 0;
    for (; i< HASH_LENGTH; i++)
        sprintf(*out+(i*2), "%02x", hash->hash[i]);

    (*out)[2*HASH_LENGTH] = 0;
    return 0;
}

char* getStrHash(hash_t* hash)
{
    char* out;
    if( getHexHash(hash,&out) )
        return NULL;
    return out;
}

int copyHash(hash_t* output,hash_t* input)
{
    strncpy(output->hash,input->hash,HASH_LENGTH);
    return 0;
}

void deleteHash(hash_t* ht)
{
    free(ht);
}

int mergeHash (hash_t* first,   /* I - First Hash */
                hash_t* second, /* I - Second Hash */
                hash_t* out)   /* O- Output Hash */
{
    char* firstString, *secondString;

    if(getHexHash(first,&firstString))
        return -1;
    if(getHexHash(second,&secondString))
        return -1;
    
    unsigned char string[4*HASH_LENGTH+1];
    snprintf(string,sizeof(string),"%s%s",firstString,secondString);
    hash_t* temp = computeHash(string,strlen(string));
    copyHash(out,temp);
    if (temp == NULL)
        return -1;
        
    deleteHash(temp);
    free(firstString);
    free(secondString);

    return 0;
}

int compareHash (hash_t* a,hash_t* b)
{
    return strncmp(a->hash,b->hash,HASH_LENGTH);
}