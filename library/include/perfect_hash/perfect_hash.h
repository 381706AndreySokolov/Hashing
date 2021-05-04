#pragma once

#include <initializer_list>
#include <functional>
#include <utility>
#include <iostream>
#include <time.h>
#include <algorithm>
#include <vector>
#include <list>
#include <stdio.h>
#include <assert.h>
#include <cmath>

namespace perfect_hash
{

// function for calculation of hash    
inline int UniversalHash(std::int64_t a_prime, std::int64_t b_prime, std::int64_t p_prime, int table_size, int key)
{
    return (((a_prime * key + b_prime) % p_prime) % table_size);
}

inline int hashString(std::string str)
{
    int hkey = 0;
    for (size_t i = 0; i < str.size(); ++i)
    {
        hkey = ((hkey << 5)+hkey) + str[i];
    }
    return hkey;
}

inline int UniversalHash(std::int64_t a_prime, std::int64_t b_prime, std::int64_t p_prime, int table_size, std::string key)
{
    int hkey = hashString(key);
    return (((a_prime * hkey + b_prime) % p_prime) % table_size);
}

template<typename Key, typename Value>
class HashNode
{
public:
    Key key;
    Value value;
    HashNode() {}
    HashNode(const Key& _key, const Value& _value) : key(_key), value(_value) {}
};

// class for mini-hash table in cells of main hash-table 
template<typename Key, typename Value>
class Bucket
{
    using HashNodeType = HashNode<Key, Value>;
    std::vector<HashNodeType> _cells;
    int size; // the size of mini-table should be greater then 4 
    std::int64_t hash_a;
    std::int64_t hash_b;
    int prime;
    Key maxValue;

public:
    Bucket()
    {
        if constexpr (std::is_same_v<Key, std::string>)
        {
            maxValue = std::string("ÿÿÿÿÿÿ");
        }
        else
        {
            maxValue = std::numeric_limits<Key>::max();
        }
    }
    void Initialize()
    {
        prime = 17;
        hash_a = std::rand() % prime;
        hash_b = 1 + std::rand() % (prime - 1);
    }

    // construct hash table from list of elements
    void Construct(std::list<HashNodeType>& input)
    {
        if (input.empty())
        {
            size = 0;
            return;
        }

        size = input.size() * input.size();
        //std::cout << "size = " << size << std::endl;
        bool flag = true;

        // while there is no collisions in table 
        while (flag)
        {
            _cells.assign(size, HashNodeType{maxValue, Value{}});
            Initialize();
            typename std::list<HashNodeType>::iterator elem = input.begin();
            while (elem != input.end() && flag)
            {
                // std::cout << "(*elem).key = " << (*elem).key << std::endl;
                int hashKey = UniversalHash(hash_a, hash_b, prime, size, (*elem).key);
                if (hashKey < 0)
                    hashKey = -hashKey;
                // std::cout << "hashKey = " << hashKey << std::endl;
                // if collision then construct hash table from the begining!
                if (_cells[hashKey].key != maxValue)
                {
                    flag = false;
                    break;
                }
                _cells[hashKey].key = (*elem).key;
                _cells[hashKey].value = (*elem).value;
                ++elem;
            }

            if (!flag)
                flag = true;
            else
                flag = false;
        }
    }

    bool Contains(Key key)
    {
        if (size == 0)
            return false;
        int hashKey = UniversalHash(hash_a, hash_b, prime, size, key);
        if (hashKey < 0)
            hashKey = -hashKey;
        if (_cells[hashKey].key == key)
            return true;
        return false;
    }
};

// class for main hash table
template<typename Key, typename Value>
class HashTable
{
    using BucketType = Bucket<Key, Value>;
    using HashNodeType = HashNode<Key, Value>;

    size_t _tableSize;
    int _primeNumber;
    std::int64_t _hashFuncA;
    std::int64_t _hashFuncB;
    Key maxValue;

    std::vector<std::list<HashNodeType>> _elementsInCells;
    std::vector<BucketType> _buckets;

public:
    HashTable()
    {
        _primeNumber = 100013; // the maximum prime number
        _hashFuncA = std::rand() % _primeNumber;
        _hashFuncB = 1 + std::rand() % (_primeNumber - 1);

        if constexpr (std::is_same_v<Key, std::string>)
        {
            maxValue = std::string("ÿÿÿÿÿÿ");
        }
        else
        {
            maxValue = std::numeric_limits<Key>::max();
        }
    }

    void setTableSize(int size)
    {
        _tableSize = size;
        _buckets.resize(size);
    }

    void Initialize(size_t tableSize, const std::vector<std::pair<Key, Value>>& numbers)
    {
        _tableSize = tableSize;
        _buckets.resize(_tableSize);
        _elementsInCells.resize(_tableSize);
        for (size_t i = 0; i < numbers.size(); ++i)
        {
            // std::cout << "1)i = " << i << std::endl;

            int hashKey = UniversalHash(_hashFuncA, _hashFuncB, _primeNumber, _tableSize, std::get<0>(numbers[i]));
            if (hashKey < 0)
                hashKey = -hashKey;
            _elementsInCells[hashKey].push_back(HashNodeType(std::get<0>(numbers[i]), std::get<1>(numbers[i])));
        }
        for (size_t i = 0; i < _tableSize; ++i)
        {
            // std::cout << "2)i = " << i << std::endl;
            _buckets[i].Construct(_elementsInCells[i]);
        }
    }

    bool Contains(Key number)
    {
        int hashKey = UniversalHash(_hashFuncA, _hashFuncB, _primeNumber, _tableSize, number);
        if (hashKey < 0)
            hashKey = -hashKey;
        return _buckets[hashKey].Contains(number);
    }
};

} // namespace perfect_hash
