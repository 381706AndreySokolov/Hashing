#pragma once
#include "sub_table.h"

namespace perfect_hash
{

template<typename Key, typename Value>
class HashTable
{
    using SubTableType = SubTable<Key, Value>;
    using HashNodeType = HashNode<Key, Value>;

    size_t _tableSize;

    UniversalHash<int> universalHash;

    std::vector<SubTableType>            _subTables;
    std::vector<std::list<HashNodeType>> _elementsInCells;

public:
    HashTable()
    { }

    void Initialize(size_t tableSize, const std::vector<std::pair<Key, Value>>& elements) // for strings
    {
        _tableSize = tableSize;
        _subTables.resize(_tableSize);
        _elementsInCells.resize(_tableSize);

        universalHash.init(_tableSize);
    
        for (size_t idx = 0; idx < elements.size(); ++idx)
        {
            const Key   key   = std::get<0>(elements[idx]);
            const Value value = std::get<1>(elements[idx]);

            size_t hash = this->hash(key);

            _elementsInCells[hash].push_back(HashNodeType{key, value});
        }

        for (size_t idx = 0; idx < _tableSize; ++idx)
        {
            _subTables[idx].Construct(_elementsInCells[idx]);
        }
    }

    bool Contains(const Key& key)
    {
        const size_t hash = this->hash(key);
        return _subTables[hash].Contains(key);
    }

    template <typename KeyT,
              typename std::enable_if<!std::is_same<KeyT, std::string>::value>::type* = nullptr>
    size_t hash(KeyT key) const // for numbers
    {
        return universalHash.hash(key);
    }

    template <typename KeyT,
              typename std::enable_if<std::is_same<KeyT, std::string>::value>::type* = nullptr>
    size_t hash(KeyT string) const // for strings
    {
        const auto stringHash = hashString(string);
        const auto hash       = universalHash.hash(stringHash);
        return hash;
    }
};

} // namespace perfect_hash
