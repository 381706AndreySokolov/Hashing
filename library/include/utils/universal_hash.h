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

    unsigned int operator()(const KeyType &key) const
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

    UniversalHash(size_t tableSize, int k) : tableSize(tableSize), k(k)
    {
        std::random_device randDev;
        std::mt19937 mt(randDev());
        std::uniform_int_distribution<int> a_uid(1, prime - 1);
        std::uniform_int_distribution<int> b_uid(0, prime - 1);
        for (int i = 0; i < k; i++)
        {
            this->a_array.push_back(a_uid(mt));
        }
        this->b = b_uid(mt);
    }

    unsigned int hash(const int &key) const
    {
        unsigned int l = 0;

        if (k == -1)
        {
            l = a * key + b;
        }
        else
        {
            for (int i = 0; i < k; i++)
            {
                l = l + this->a_array[i] * pow(key, i);
            }
            l = l + this->b;
        }

        if (l >= tableSize)
        {
            l = (l >= prime) ? l % prime : l;
            return (l >= tableSize) ? (l % tableSize) : l;
        }
        else
        {
            return l;
        }
    }

private:
    size_t tableSize;
    int k = -1;
    unsigned int a, b;
    const unsigned int prime = 100013U;//150001U;
    std::vector<int> a_array;
};

template <>
class UniversalHash<std::string>
{
public:

    UniversalHash(size_t tableSize)
    {
        this->tableSize = tableSize;
        intUniversal = new UniversalHash<int>(tableSize);
    }

    unsigned int hash(const std::string key) const
    {
        int hkey = 0;//5381;
        for (size_t i = 0; i < key.size(); ++i)
        {
            hkey = ((hkey << 5)+hkey) + key[i];
        }
        //return (hkey >= tableSize) ? hkey % tableSize : hkey;
        return intUniversal->hash(hkey);
    }
private:
    UniversalHash<int>* intUniversal;
    size_t tableSize;
};