#include <headers.h>

#ifndef HAVE_STRLCPY
size_t strlcpy (char* dest, char* src,size_t len)
{
    size_t srclen = strlen(src);
    len --;

    if (srclen > len)
        srclen = len;
    
    memmove(dest,src,srclen);
    dest[srclen] = '\0';
}
#endif