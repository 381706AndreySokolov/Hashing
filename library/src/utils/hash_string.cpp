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
    //return std::hash<std::string>()(str);

    //unsigned int hash = 0;

    // while (*str)
    // {

    //     hash = 65599 * hash + (*str);
    //     hash = (*str++) + (hash << 6) + (hash << 16) - hash;
    // }
    // return (hash & 0x7FFFFFFF)
}

// size_t hashString(std::string str)
// {
//     size_t hkey = 0;
//     int p_pow = 1;
//     const int p = 31;
//     // std::cout << "str = " << str << std::endl;
//     for (size_t i = 0; i < str.size(); ++i)
//     {
//         hkey += (str[i] - 'a' + 1) * p_pow;
//         p_pow *= p;
//        //std::cout << "hkey in " << i << " = " << hkey << std::endl;
//     }
    
//     return hkey;
// }