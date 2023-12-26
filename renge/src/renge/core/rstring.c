#include "rstring.h"

char *rn_strstr(const char *a, const char *b)
{
    if (!*b) return (char *)a;

    while (*a) {
        const char *p1 = a;
        const char *p2 = b;
        while (*p1 && *p2 && *p1 == *p2) {
            p1++;
            p2++;
        }
        if (!*p2) {
            return (char *)a;
        }
        a++;
    }

    return NULL; 
}

size_t rn_strlen(const char *cstr)
{
    size_t i;
    for(i = 0; cstr[i] != '\0'; ++i);
    return i;
}

