#include "utils/hash_string.h"
#include <iostream>

size_t hashString(std::string str)
{
    size_t hkey = 0;
    for (size_t i = 0; i < str.size(); ++i)
    {
        hkey = 65599 * hkey + str[i];
        hkey = str[i] + (hkey << 6) + (hkey << 16) - hkey;
    }
    return hkey;
}
