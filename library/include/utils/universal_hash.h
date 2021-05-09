#pragma once
#include <math.h>
#include <random>
#include <string>

template <typename KeyType>
class UniversalHash
{
public:

    //UniversalHash<int>& operator=(UniversalHash<int>&&) = default;
    UniversalHash(size_t tableSize) : tableSize(tableSize)
    { }

    size_t operator()(const KeyType &key) const
    {
        return (key) % this->tableSize;
    }

private:
    size_t tableSize;
};

template <>
class UniversalHash<int>
{
public:

    UniversalHash() = default;

    UniversalHash(size_t tableSize) : tableSize(tableSize)
    {
        std::random_device randDev{};
        std::mt19937 mt(randDev());
        std::uniform_int_distribution<int> a_uid(1, prime - 1);
        std::uniform_int_distribution<int> b_uid(0, prime - 1);
        this->a = a_uid(mt);
        this->b = b_uid(mt);
    }

    void init(size_t tableSize)
    {
        this->tableSize = tableSize;
        std::random_device randDev{};
        std::mt19937 mt(randDev());
        std::uniform_int_distribution<int> a_uid(1, prime - 1);
        std::uniform_int_distribution<int> b_uid(0, prime - 1);
        this->a = a_uid(mt);
        this->b = b_uid(mt);
    }
    
    size_t hash(const int &key) const
    {
        size_t l = a * key + b;
        return l % tableSize;
    }

private:
    size_t tableSize;
    size_t a, b;
    const size_t prime = 100013U;//150001U;
};
