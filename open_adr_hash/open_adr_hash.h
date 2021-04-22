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
    hashNode() {}
    hashNode(const Key& _key, const Value& _value) : key(_key), value(_value) {}
};

template<typename Key = int, typename Value = int>
class HashTable
{
    using HashNodeType = HashNode<Key, Value>;
public:
    explicit HashTable(const int tableSize, int mode);
    ~HashTable();
    int getTableSize() { return _tableSize; }
    int getSize() { return _size; }
    void insert(const Key& key, const Value& value);
    void remove(const Key& key);
    Value operator[](const Key& key);
private:
    int hash(const Key& key, int i);
    int _tableSize;
    int _size;
    int _mode;
    HashNodeType* _buffer;
};

template <typename Key, typename Value>
HashTable<Key, Value>::HashTable(const int max_size, int mode) : _tableSize(tableSize), _size(0), _mode(mode)
{
    _buffer = new HashNodeType [tableSize];
    for (int i = 0; i < tableSize; ++i)
     {
        _buffer[i].key = INT_MAX;
    }
}

template <typename Key, typename Value>
HashTable<Key, Value>::~HashTable()
{
    delete[] _buffer;
}

template <typename Key, typename Value>
Value HashTable<Key, Value>::operator[](const Key& key)
{
    int i = 0;

    while (_buffer[hash(key, i)].key != INT_MAX)
    {
        i++;
    }

    if (i == _tableSize)
    {
        return 0;
    }
    else
    {
        return _buffer[hash(key, i)].value;
    }
    return Value();
}

template <typename Key, typename Value>
void HashTable<Key, Value>::insert(const Key& key, const Value& value)
{
    int i = 0;

    while (_buffer[hash(key, i)].key != INT_MAX)
    {
        i++;
    }

    if (i == _tableSize)
        return;
    else
    {
        _buffer[hash(key, i)].key = key;
        _buffer[hash(key, i)].value = value;
    }

    _size++;
}

template <typename Key, typename Value>
int HashTable<Key, Value>::hash(const Key& key, int i)
{
    if (_mode == 1) // Linear probe
        return  (std::hash<Key>()(key) + i) % _tableSize;
    else if (_mode == 2) // Quadratic probe
        return (std::hash<Key>()(key) + 2 * i + 4 * i * i) % _tableSize;
    else if (_mode == 3) // Double hashing
        return (std::hash<Key>()(key) + i * (key % _tableSize)) % _tableSize;
}

}

#endif  // OPEN_ADR_OPEN_ADR_H_