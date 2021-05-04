#include "utils/hash_string.h"

int hashString(std::string str)
{
    int hkey = 0;
    for (size_t i = 0; i < str.size(); ++i)
    {
        hkey = ((hkey << 5)+hkey) + str[i];
    }
    return hkey;
}