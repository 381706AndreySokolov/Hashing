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
    const size_t _tableSize;
    size_t _size;
    HashNodeType** _buffer;

    UniversalHash<int> universalHash;
    KIndHash<int> kIndHash;

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

    template <typename KeyT,
              typename std::enable_if<!std::is_same<KeyT, std::string>::value>::type* = nullptr>
    int hash(const KeyT& key) // for numbers
    {
        if constexpr (mode == 1U) // Div method
        {
            return key % _tableSize;
        }
        else if constexpr (mode == 2U) // Mul method
        {
            constexpr float A{ 0.618f };
            int hash = floor(_tableSize * fmod(key * A, 1.0f));
            return hash % _tableSize;
        }
        else if constexpr (mode == 3U) // Universal method
        {
            auto hash = universalHash.hash(key);
            return hash;
        }
        else if constexpr (mode == 4U) // k-Independent method
        {
            auto hash = kIndHash.hash(key);
            return hash;
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
            int stringHash = hashString(key);
            int hash = stringHash % _tableSize;
            return hash;
        }
        else if constexpr (mode == 2U) // Mul method
        {
            int stringHash = hashString(key);
            float A{ 0.618f };
            int hash = floor(_tableSize * fmod(stringHash * A, 1.0f));
            return hash % _tableSize;
        }
        else if constexpr (mode == 3U) // Universal method
        {
            int stringHash = hashString(key);
            auto hash = universalHash.hash(stringHash);
            return hash;
        }
        else if constexpr (mode == 4U) // k-Independent method
        {
            int stringHash = hashString(key);
            auto hash = kIndHash.hash(stringHash);
            return hash;
        }
        else if constexpr (mode == 5U) // std::hash
        {
            return std::hash<Key>()(key) % _tableSize;
        }
        return 0;
    }
};

template<typename Key, typename Value, int mode>
HashTable<Key, Value, mode>::HashTable(const size_t tableSize) : _tableSize(tableSize), _size(0)
{
    static_assert(mode > 0 && mode < 6, "Mode != 1,2,3,4,5");
    _buffer = new HashNodeType* [_tableSize];
    for (size_t idx = 0; idx < _tableSize; ++idx)
    {
        _buffer[idx] = nullptr;
    }
    universalHash.init(tableSize);
    kIndHash.init(tableSize, 3);
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
