#ifndef CUCKOO_HASH_H
#define CUCKOO_HASH_H
#include "universal_hash.h"
#include "primeNumbers.h"
#include "utils.h"

template <typename KeyType>
class CuckooHash
{
public:
    CuckooKeyHash(size_t tableSize, int k = -1) : tableSize(tableSize),
                                                  uniHashFunc(tableSize, k),
                                                  a(genRandomUid(1, 12)),
                                                  b(genRandomUid(0, PRIME.size() - 1)),
                                                  k(k)
    {};

    unsigned int operator()(const K &key) const
    {
        unsigned int l;
        if (k == -1)
        {
            l = (uniHashFunc(key) << a) + PRIME[b];
            return (l >= tableSize) ? l % tableSize : l;
        }
        else
        {
            return uniHashFunc(key);
        }
    }
private:
    UniversalHash<KeyType> uniHashFunc;
    size_t tableSize;

    unsigned int a, b;
    int k = -1;
};


template<>
class CuckooKeyHash<std::string> {
private:
    size_t tableSize;
    KeyHash<std::string> uniHashFunc;
    unsigned int a, b;

public:
    CuckooKeyHash(size_t tableSize, int k = -1)
        : tableSize(tableSize),
        uniHashFunc(tableSize),
        a(genRandomUid(1, 12)),
        b(genRandomUid(0, PRIME.size() - 1))
    {};

    unsigned int operator[](const std::string &key) const
    {
        unsigned int l = PRIME[b];
        for (auto i = 0; i < key.size(); ++i) {
            l = ((l << a) + l) + key[i];
        }
        return (l >= tableSize) ? l % tableSize : l;
    }
};

#endif // CUCKOO_HASH_H