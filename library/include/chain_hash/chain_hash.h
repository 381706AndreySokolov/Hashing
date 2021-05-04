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

#include "utils/utils.h"

namespace chain_hash
{

template<typename Key, typename Value>
class HashNode
{
public:
    Key key;
    Value value;
    HashNode* next;

    HashNode(const Key& _key, const Value& _value) : key(_key), value(_value), next(nullptr) {}
};

template<typename Key, typename Value, int mode>
class HashTable
{
    using HashNodeType = HashNode<Key, Value>;

public:
    HashTable(const size_t tableSize);
    ~HashTable();
    int getTableSize() { return _tableSize; }
    int getSize() { return _size; }
    void insert(const Key& key, const Value& value);
    void remove(const Key& key);
    auto getDistribution()
    {
        std::vector<int> distribution(_tableSize, 0);
        for (int idx = 0; idx < _tableSize; ++idx)
        {
            auto entry = _buffer[idx];
            while (entry != nullptr)
            {
                auto prev = entry;
                entry = entry->next;
                distribution[idx]++;
            }
        }
        return distribution;
    }
    Value operator[](const Key& key);
    
    // For Universal Hashing
    void initUniversalHash()
    {
        setP(17LL);
        setA(std::rand() % _p_prime);
        setB(1 + std::rand() % (_p_prime - 1));
    }
private:
    template <typename KeyT,
              typename std::enable_if<!std::is_same<KeyT, std::string>::value>::type* = nullptr>
    int hash(const KeyT& key)
    {
        if constexpr (mode == 1U) // Div method
        {
            return key % _tableSize;
        }
        else if constexpr (mode == 2U) // Mul method
        {
            constexpr float A{ 0.618f };
            int idx = floor(_tableSize * fmod(key * A, 1.0f));
            //std::cout << "idx = " << idx << std::endl;
            return idx;
        }
        else if constexpr (mode == 3U) // Universal method
        {
            int idx = ((_a_prime * key + _b_prime) % _p_prime) % _tableSize;
            //std::cout << "idx = " << idx << std::endl;
            return idx;
        }
        else if constexpr (mode == 4U) // k-Independent method
        {
            std::uint64_t sum{ 0ULL };
            for (int idx = _aVector.size() - 1; idx >= 0; --idx)
            {
                sum += _aVector[idx] * pow(key, idx);
            }
            //std::cout << "sum = " << sum << std::endl;
            int idx = (sum % _p_prime) % _tableSize;
            //std::cout << "idx = " << idx << std::endl;
            return idx;
        }
        else if constexpr (mode == 5U) // std::hash
        {
            return std::hash<Key>()(key) % _tableSize;
        }
    }

    template <typename KeyT,
              typename std::enable_if<std::is_same<KeyT, std::string>::value>::type* = nullptr>
    int hash(const KeyT& key)
    {
        if constexpr (mode == 1U) // Div method
        {
            int hkey = hashString(key);
            int index = hkey % _tableSize;
            return index;
        }
        else if constexpr (mode == 2U) // Mul method
        {
            int hkey = hashString(key);
            float A{ 0.618f };
            int idx = floor(_tableSize * fmod(hkey * A, 1.0f));

            if (idx % _tableSize > _tableSize)
                std::cout << "idx = " << idx << std::endl;

            return idx % _tableSize;
        }
        else if constexpr (mode == 3U) // Universal method
        {
            int hkey = hashString(key);
            int idx = ((_a_prime * hkey + _b_prime) % _p_prime) % _tableSize;
            //std::cout << "idx = " << idx << std::endl;
            return idx;
        }
        else if constexpr (mode == 4U) // k-Independent method
        {
            int hkey = hashString(key);
            std::uint64_t sum{ 0ULL };
            for (int idx = _aVector.size() - 1; idx >= 0; --idx)
            {
                sum += _aVector[idx] * pow(hkey, idx);
            }
            //std::cout << "sum = " << sum << std::endl;
            int idx = (sum % _p_prime) % _tableSize;
            //std::cout << "idx = " << idx << std::endl;
            return idx;
        }
        else if constexpr (mode == 5U) // std::hash
        {
            return std::hash<Key>()(key) % _tableSize;
        }
        return 0;
    }

    int hashString(std::string str)
    {
        int hkey = 0;
        for (size_t i = 0; i < str.size(); ++i)
        {
            hkey = ((hkey << 5)+hkey) + str[i];
        }
        return hkey;
    }

    const size_t _tableSize;
    size_t _size;
    HashNodeType** _buffer;


private:
    // void setP(std::int64_t p_prime = 17LL) { _p_prime = p_prime; }
    // void setA(std::int64_t a_prime = (std::rand() % _p_prime)) { _a_prime = a_prime; }
    // void setB(std::int64_t b_prime = (1 + std::rand() % (_p_prime - 1))) { _b_prime = b_prime; }

    void setP(std::int64_t p_prime) { _p_prime = p_prime; }
    void setA(std::int64_t a_prime) { _a_prime = a_prime; }
    void setB(std::int64_t b_prime) { _b_prime = b_prime; }

    std::int64_t _p_prime;// = pow(2, _tableSize) - 1;
    std::int64_t _a_prime;//  = std::rand() % (_p_prime - 1);
    std::int64_t _b_prime;// = 1 + std::rand() % (_p_prime - 1);

// For K-Independent Hashing
public:
    void setAVector(std::vector<int64_t>& aVector) { _aVector = aVector; }
    void generateAVector(int k)
    {
        _aVector.resize(k);
        for (auto& value : _aVector)
        {
            value = std::rand() % _p_prime;
        }
    }
private:
    std::vector<int64_t> _aVector;
};

template<typename Key, typename Value, int mode>
HashTable<Key, Value, mode>::HashTable(const size_t tableSize) : _tableSize(tableSize), _size(0)
{
    _buffer = new HashNodeType* [_tableSize];
    for (size_t idx = 0; idx < _tableSize; ++idx)
    {
        _buffer[idx] = nullptr;
    }
}

template<typename Key, typename Value, int mode>
HashTable<Key, Value, mode>::~HashTable()
{
    for (size_t i = 0; i < _tableSize; ++i)
    {
        auto entry = _buffer[i];
        while (entry != nullptr)
        {
            auto prev = entry;
            entry = entry->next;
            delete prev;
        }
        _buffer[i] = nullptr;
    }
    delete[] _buffer;
}

template<typename Key, typename Value, int mode>
Value HashTable<Key, Value, mode>::operator[](const Key& key)
{
    auto hashIndex = hash(key);
    auto entry = _buffer[hashIndex];

    while (entry != nullptr)
    {
        if (entry->key == key)
        {
            return entry->value;
        }
        entry = entry->next;
    }
    return Value();
}

template<typename Key, typename Value, int mode>
void HashTable<Key, Value, mode>::insert(const Key& key, const Value& value)
{
    auto hashindex = hash(key);
    HashNodeType* newNode = new HashNodeType(key, value);
    HashNodeType* prev = _buffer[hashindex];
    _buffer[hashindex] = newNode;
    if (prev != nullptr)
    {
        _buffer[hashindex]->next = prev;
    }
    _size++;
}

template<typename Key, typename Value, int mode>
void HashTable<Key, Value, mode>::remove(const Key& key)
{
    auto hashindex = hash(key);
    auto entry = _buffer[hashindex];
    HashNodeType* prev = nullptr;

    while (entry != nullptr && entry->key != key)
    {
        prev = entry;
        entry = entry->next;
    }

    if (entry == nullptr)
    {
        return;
    }
    else
    {
        if (prev == nullptr)
        {
            _buffer[hashindex] = entry->next;
        }
        else
        {
            prev->next = entry->next;
        }
        delete entry;
    }
    _size--;
}

} // namespace chain_hash
