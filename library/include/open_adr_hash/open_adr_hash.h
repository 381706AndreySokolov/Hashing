#ifndef OPEN_ADR_OPEN_ADR_H_
#define OPEN_ADR_OPEN_ADR_H_

#include <initializer_list>
#include <functional>
#include <utility>
#include <iostream>
#include <time.h>
#include <algorithm>
#include <vector>
#include <list>
#include <stdio.h>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::list;

namespace open_adr_hash
{

template<typename Key, typename Value>
class HashNode
{
public:
    Key key;
    Value value;
    HashNode() {}
    HashNode(const Key& _key, const Value& _value) : key(_key), value(_value) {}
};

template<typename Key, typename Value, int mode>
class HashTable
{
    using HashNodeType = HashNode<Key, Value>;
public:
    HashTable(size_t tableSize);
    ~HashTable();
    size_t getTableSize() { return _tableSize; }
    size_t getSize() { return _size; }
    bool insert(const Key& key, const Value& value);
    void remove(const Key& key);
    Value operator[](const Key& key);
private:
    template <typename KeyT,
              typename std::enable_if<!std::is_same<KeyT, std::string>::value>::type* = nullptr>
    int hash(const KeyT& key, size_t i) // for numbers
    {
        if constexpr (mode == 1) // Linear probe
        {
            return  (std::hash<KeyT>()(key) + i) % _tableSize;
        }
        else if constexpr (mode == 2) // Quadratic probe
        {
            return (std::hash<KeyT>()(key) + 2 * i + 4 * i * i) % _tableSize;
        }
        else if constexpr (mode == 3) // Double hashing
        {
            return (std::hash<KeyT>()(key) + i * (key % _tableSize)) % _tableSize;
        }
    }

    template <typename KeyT,
              typename std::enable_if<std::is_same<KeyT, std::string>::value>::type* = nullptr>
    int hash(const KeyT& key, size_t i) // for strings
    {
        if constexpr (mode == 1) // Linear probe
        {
            const int hashKey = hashString(key);
            return  (std::hash<int>()(hashKey) + i) % _tableSize;
        }
        else if constexpr (mode == 2) // Quadratic probe
        {
            const int hashKey = hashString(key);
            return (std::hash<int>()(hashKey) + 2U * i + 4U * i * i) % _tableSize;
        }
        else if constexpr (mode == 3) // Double hashing
        {
            const int hashKey = hashString(key);
            return (std::hash<int>()(hashKey) + i * std::hash<int>()(hashKey)) % _tableSize;
        }
    }

    size_t _tableSize;
    size_t _size;
    HashNodeType* _buffer;
    Key maxValue;
};

template<typename Key, typename Value, int mode>
HashTable<Key, Value, mode>::HashTable(const size_t tableSize) : _tableSize(tableSize), _size(0U)
{
    static_assert(mode > 0 && mode < 4, "Mode != 1,2,3");

    if constexpr (std::is_same_v<Key, std::string>)
    {
        maxValue = std::string("ÿÿÿÿÿÿ");
    }
    else
    {
        maxValue = std::numeric_limits<Key>::max();
    }

    _buffer = new HashNodeType [tableSize];
    for (size_t idx = 0; idx < tableSize; ++idx)
    {
        _buffer[idx].key = maxValue;
    }
}

template<typename Key, typename Value, int mode>
HashTable<Key, Value, mode>::~HashTable()
{
    delete[] _buffer;
}

template<typename Key, typename Value, int mode>
Value HashTable<Key, Value, mode>::operator[](const Key& key)
{
    size_t i = 0U;

    while (_buffer[hash(key, i)].key == maxValue)
    {
        i++;
    }

    if (i == _tableSize)
    {
        return Value();
    }
    else
    {
        return _buffer[hash(key, i)].value;
    }
    return Value();
}


template<typename Key, typename Value, int mode>
bool HashTable<Key, Value, mode>::insert(const Key& key, const Value& value)
{
    size_t i = 0U;

    while (_buffer[hash(key, i)].key != maxValue)
    {
        // std::cout << "i = " << i << std::endl;
        i++;
    }

    if (i == _tableSize)
    {
        // std::cout << "i == _tableSize, _size = " << _size << std::endl;
        return false;
    }
    else
    {
        // std::cout << "Inserted, _size = " << _size << std::endl;
        _buffer[hash(key, i)].key = key;
        _buffer[hash(key, i)].value = value;
        _size++;
    }
    return true;
}

}

#endif  // OPEN_ADR_OPEN_ADR_H_