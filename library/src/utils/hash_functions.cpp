#include "utils/hash_functions.h"

unsigned int SDBMHash(char *str, size_t tableSize)
{
    unsigned int hash = 0;

    while (*str)
    {

        hash = 65599 * hash + (*str++);
        hash = (*str++) + (hash << 6) + (hash << 16) - hash;
    }
    return (hash & 0x7FFFFFFF) % tableSize;
}

unsigned int RSHash(char *str, size_t tableSize)
{
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;

    while (*str)
    {

        hash = hash * a + (*str++);
        a *= b;
    }

    return (hash & 0x7FFFFFFF) % tableSize;
}
