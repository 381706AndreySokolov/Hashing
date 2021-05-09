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

namespace perfect_hash
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

// class for mini-hash table in cells of main hash-table 
template<typename Key, typename Value>
class SubTable
{
    using HashNodeType = HashNode<Key, Value>;

    size_t size;
    Key maxValue;

    UniversalHash<int> universalHash;

    std::vector<HashNodeType> _cells;

public:
    SubTable()
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


    void Construct(std::list<HashNode<Key, Value>>& input)  // for strings
    {
        if (input.empty())
        {
            size = 0;
            return;
        }

        size = input.size() * input.size();

        bool isCollisions = false;
        int rehashCount = 0;
    
        while (isCollisions == false)
        {
            //std::cout << "rehashCount = " << rehashCount << std::endl;
            // std::cout << "\nCollision!!!!!!!!!!!!\n";
            _cells.assign(size, HashNodeType{maxValue, Value{}});
            universalHash.init(size);
            typename std::list<HashNodeType>::iterator elem = input.begin();
            while (elem != input.end() && isCollisions == false)
            {

                const Key   key   = (*elem).key;
                const Value value = (*elem).value;
                // std::cout << "key = " << key << std::endl;

                size_t hash = this->hash(key);

                // std::cout << "hash = " << hash << std::endl;

                // if collision then construct hash table from the begining!
                // if (_cells[hash].key != maxValue)
                // {
                //     isCollisions = true;
                //     break;
                // }

                _cells[hash].key   = key;
                _cells[hash].value = value;
                ++elem;
            }

            if (isCollisions)
                isCollisions = false;
            else
                isCollisions = true;

            rehashCount++;
        }
    }

    bool Contains(Key key)
    {
        if (size == 0)
        {
            return false;
        }

        size_t hash = this->hash(key);
        if (_cells[hash].key == key)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    template <typename KeyT,
              typename std::enable_if<!std::is_same<KeyT, std::string>::value>::type* = nullptr>
    size_t hash(KeyT key) // for numbers
    {
        return universalHash.hash(key);
    }

    template <typename KeyT,
              typename std::enable_if<std::is_same<KeyT, std::string>::value>::type* = nullptr>
    size_t hash(KeyT string) // for strings
    {
        const auto keyNumber = hashString(string);
        return universalHash.hash(keyNumber);
    }
};

}
