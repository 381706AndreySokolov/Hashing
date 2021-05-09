#pragma once
#include "utils/utils.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <unordered_map>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <cstring>

namespace cuckoo_hash
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

template<typename Key, typename Value>
class HashTable
{
    using HashNodeType = HashNode<Key, Value>;
public:
    size_t _tableSize;
    size_t _size;
    size_t _subTableSize;
    size_t _maxLoop;
    Key    _maxValue;

    std::vector<HashNodeType> _table1;
    std::vector<HashNodeType> _table2;
    KIndHash<int> kIndHash1;
    KIndHash<int> kIndHash2;

    HashTable(size_t tableSize)
    {
        if constexpr (std::is_same_v<Key, std::string>)
        {
            _maxValue = std::string("ÿÿÿÿÿÿ");
        }
        else
        {
            _maxValue = std::numeric_limits<Key>::max();
        }
        _tableSize    = tableSize;
        _subTableSize = _tableSize / 2U;
        _maxLoop      = _subTableSize / 2U;
        kIndHash1 = KIndHash<int>(_subTableSize, 4);
        kIndHash2 = KIndHash<int>(_subTableSize, 4);
        _table1.assign(_subTableSize, HashNodeType{_maxValue, Value{}});
        _table2.assign(_subTableSize, HashNodeType{_maxValue, Value{}});
    }

    ~HashTable() = default;

    size_t getTableSize()
    {
        return _tableSize;
    }

    size_t getSize()
    {
        return _size;
    }

    double getLoadfactor()
    {
        return static_cast<double>(_size) / static_cast<double>(_tableSize);
    }

    Value operator[] (Key index)
    {
        return find(index);
    }

    Value find(Key _key)
    {
        int i = hash1(_key);
        if(_table1[i].key == _key)
            return _table1[i].value;

        int j = hash2(_key);
        if(_table2[j].key == _key)
            return _table2[j].value;

        return Value{};
    }

    void insert(Key _key, Value _value)
    {
        HashNodeType newNode{_key, _value};
        if(_table1[hash1(_key)].key == _key || _table2[hash2(_key)].key == _key)
            return;

        for(size_t i = 0; i < _maxLoop; ++i)
        {
            std::swap(newNode, _table1[hash1(newNode.key)]);
            if(newNode.key == _maxValue)
            {
                ++_size;
                return;
            }
            std::swap(newNode, _table2[hash2(newNode.key)]);
            if(newNode.key == _maxValue)
            {
                ++_size;
                return;
            }
        }
        rehash();
        insert(newNode.key, newNode.value);
    }

private:
    void rehash()
    {
        std::vector<HashNodeType> elemVector;
        
        for(size_t i = 0; i < _subTableSize; ++i)
        {
            if(_table1[i].key != _maxValue)
            {
                elemVector.push_back(_table1[i]);
                _table1[i].key = _maxValue;
            }

            if(_table2[i].key != _maxValue)
            {
                elemVector.push_back(_table2[i]);
                _table2[i].key = _maxValue;
            }
        }
        
        if(static_cast<double>(_size) / static_cast<double>(_tableSize) > 0.8)
            realloc();
        
        kIndHash1 = KIndHash<int>(_subTableSize, 4);
        kIndHash2 = KIndHash<int>(_subTableSize, 4);

        for(size_t i = 0; i < elemVector.size(); ++i)
        {
            insert(elemVector[i].key, elemVector[i].value);
        }
    }

    void realloc()
    {
        const auto _oldSubTableSize = _subTableSize;

        _tableSize    = 2U * _tableSize;
        _subTableSize = _tableSize / 2U;
        _maxLoop      = _subTableSize / 2U;

        _table1.reserve(_subTableSize);
        _table2.reserve(_subTableSize);
        
        for (size_t i = _oldSubTableSize; i < _subTableSize; ++i)
        {
            _table1.push_back(HashNodeType{_maxValue, Value{}});
            _table2.push_back(HashNodeType{_maxValue, Value{}});
        }
    }

    template <typename KeyT,
              typename std::enable_if<!std::is_same<KeyT, std::string>::value>::type* = nullptr>
    size_t hash1(KeyT key) // for numbers
    {
        return kIndHash1.hash(key);
    }

    template <typename KeyT,
              typename std::enable_if<std::is_same<KeyT, std::string>::value>::type* = nullptr>
    size_t hash1(KeyT string) // for strings
    {
       const auto keyNumber = hashString(string);
        return kIndHash1.hash(keyNumber);
    }

    template <typename KeyT,
              typename std::enable_if<!std::is_same<KeyT, std::string>::value>::type* = nullptr>
    size_t hash2(KeyT key) // for numbers
    {
        return kIndHash2.hash(key);
    }

    template <typename KeyT,
              typename std::enable_if<std::is_same<KeyT, std::string>::value>::type* = nullptr>
    size_t hash2(KeyT string) // for strings
    {
        const auto keyNumber = hashString(string);
        return kIndHash2.hash(keyNumber);
    }
};

} // namespace cuckoo_hash
