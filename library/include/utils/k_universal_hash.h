#pragma once
#include <math.h>
#include <random>


template <typename KeyType>
class KIndHash
{
public:
    KIndHash() = default;

    KIndHash(size_t tableSize) : tableSize(tableSize) {}

    size_t operator[](const KeyType &key) const
    {
        return (key) % tableSize;
    }

private:
    size_t tableSize;
};

template <>
class KIndHash<int>
{
private:
    size_t tableSize;
    int k = -1;
    unsigned int a, b;
    unsigned int prime = 150001;
    std::vector<int> a_array;
public:
    KIndHash() = default;

    KIndHash(size_t tableSize, int k)
    {
        this->k = k;
        this->tableSize = tableSize;
        std::random_device randDev;
        std::mt19937 mers(randDev());
        std::uniform_int_distribution<int> a_uid(1, prime - 1);
        std::uniform_int_distribution<int> b_uid(0, prime - 1);
        for (int i = 0; i < k; i++)
        {
            this->a_array.push_back(a_uid(mers));
        }
        this->b = b_uid(mers);
    }

    void init(size_t tableSize, int k)
    {
        this->k = k;
        this->tableSize = tableSize;
        std::random_device randDev;
        std::mt19937 mers(randDev());
        std::uniform_int_distribution<int> a_uid(1, prime - 1);
        std::uniform_int_distribution<int> b_uid(0, prime - 1);
        for (int i = 0; i < k; i++) {
            this->a_array.push_back(a_uid(mers));
        }
        this->b = b_uid(mers);
    }

    size_t hash(const int &key) const
    {
        size_t l = 0;

        for (int i = 0; i < k; i++)
        {
            l = l + this->a_array[i] * pow(key, i);
        }
        l = l + this->b;

        return (l >= tableSize) ? (l % tableSize) : l;
    }
};
