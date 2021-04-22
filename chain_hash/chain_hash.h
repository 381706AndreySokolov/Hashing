#ifndef CHAIN_HASH_CHAIN_HASH_H
#define CHAIN_HASH_CHAIN_HASH_H

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

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::list;

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

template<typename Key = int, typename Value = int>
class HashTable
{
    using HashNodeType = HashNode<Key, Value>;

public:
    HashTable(const int tableSize, int mode);
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

private:
    int hash(const Key& key);

    int _tableSize;
    int _size;
    int _mode;
    HashNodeType** _buffer;

// For Universal Hashing
public:
    void setP(std::int64_t p_prime = 17LL) { _p_prime = p_prime }
    void setA(std::int64_t a_prime = (std::rand() % _p_prime)) { _a_prime = a_prime }
    void setB(std::int64_t b_prime = (1 + std::rand() % (_p_prime - 1))) { _b_prime = b_prime }
private:
    std::int64_t _p_prime = pow(2, _tableSize) - 1;
    std::int64_t _a_prime = std::rand() % (_p_prime - 1);
    std::int64_t _b_prime = 1 + std::rand() % (_p_prime - 1);

// For K-Independent Hashing
public:
    void setAVector(std::vector<int64_t>& aVector) { _aVector = aVector }
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

template <typename Key, typename Value>
HashTable<Key, Value>::HashTable(const int tableSize, int mode) : _tableSize(tableSize), _size(0), _mode(mode)
{
    //std::cout << "_tableSize = " << _tableSize << std::endl;
    assert(_tableSize > 0);
    _buffer = new HashNodeType* [_tableSize];
    for (int idx = 0; idx < _tableSize; ++idx)
    {
        _buffer[idx] = nullptr;
    }
    if (mode == 4)
        generateAVector(3);
}

template <typename Key, typename Value>
HashTable<Key, Value>::~HashTable()
{
    for (int i = 0; i < _tableSize; ++i)
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

template <typename Key, typename Value>
Value HashTable<Key, Value>::operator[](const Key& key)
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

template <typename Key, typename Value>
void HashTable<Key, Value>::insert(const Key& key, const Value& value)
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

template <typename Key, typename Value>
void HashTable<Key, Value>::remove(const Key& key) {
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

template <typename Key, typename Value>
int HashTable<Key, Value>::hash(const Key& key)
{
    if (_mode == 1U) // Div method
    {
        return key % _tableSize;
    }
    else if (_mode == 2U) // Mul method
    {
        constexpr float A{ 0.618f };
        int idx = floor(_tableSize * fmod(key * A, 1.0f));
        //std::cout << "idx = " << idx << std::endl;
        return idx;
    }
    else if (_mode == 3U) // Universal method
    {
        int idx = ((_a_prime * key + _b_prime) % _p_prime) % _tableSize;
        //std::cout << "idx = " << idx << std::endl;
        return idx;
    }
    else if (_mode == 4U) // k-Independent method
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
    else if (_mode == 5U) // std::hash
    {
        return std::hash<Key>()(key) % _tableSize;
    }
}

//===============================================================================================================================


const int max_int = 1000000001; // value, that could't be in the table. Analog of NULL.

// function for calculation of hash    
inline int UniversalHash(std::int64_t a_prime, std::int64_t b_prime, std::int64_t p_prime, int table_size, int key)
{
    return (((a_prime * key + b_prime) % p_prime) % table_size);
}

// class for mini-hash table in cells of main hash-table 
class Bucket
{
    vector<int> _cells;
    int size; // the size of mini-table should be greater then 4 
    std::int64_t hash_a;
    std::int64_t hash_b;
    int prime;

public:
    Bucket() {}
    void Initialize()
    {
        prime = 17;
        hash_a = std::rand() % prime;
        hash_b = 1 + std::rand() % (prime - 1);
    }

    // construct hash table from list of elements
    void Construct(list<int>& input)
    {
        if (input.empty())
        {
            size = 0;
            return;
        }

        size = input.size() * input.size();
        bool flag = true;

        // while there is no collisions in table 
        while (flag)
        {
            _cells.assign(size, max_int);
            Initialize();
            list<int>::iterator elem = input.begin();
            while (elem != input.end() && flag)
            {
                int hashKey = UniversalHash(hash_a, hash_b, prime, size, *elem);
                if (hashKey < 0)
                    hashKey = -hashKey;

                // if collision then construct hash table from the begining!
                if (_cells[hashKey] != max_int)
                {
                    flag = false;
                    break;
                }
                _cells[hashKey] = *elem;
                ++elem;
            }

            if (!flag)
                flag = true;
            else
                flag = false;
        }
    }

    bool Contains(int elem)
    {
        if (size == 0)
            return false;
        int hashKey = UniversalHash(hash_a, hash_b, prime, size, elem);
        if (hashKey < 0)
            hashKey = -hashKey;
        if (_cells[hashKey] == elem)
            return true;
        return false;
    }
};

// class for main hash table
class FixedSet
{
    int _tableSize;
    std::int64_t _hashFuncA;
    std::int64_t _hashFuncB;
    int _primeNumber;
    vector<list<int> > _elementsInCells;
    vector<Bucket> _buckets;

public:
    FixedSet()
    {
        _primeNumber = 100013; // the maximum prime number
        _hashFuncA = std::rand() % _primeNumber;
        _hashFuncB = 1 + std::rand() % (_primeNumber - 1);
    }

    void setTableSize(int size)
    {
        _tableSize = size;
        _buckets.resize(size);
    }

    void Initialize(const vector<int>& numbers)
    {
        _tableSize = numbers.size();
        _buckets.resize(numbers.size());
        _elementsInCells.resize(numbers.size());
        for (int i = 0; i < numbers.size(); ++i)
        {
            int hashKey = UniversalHash(_hashFuncA, _hashFuncB, _primeNumber, _tableSize, numbers[i]);
            if (hashKey < 0)
                hashKey = -hashKey;
            _elementsInCells[hashKey].push_back(numbers[i]);
        }
        for (int i = 0; i < numbers.size(); ++i)
        {
            _buckets[i].Construct(_elementsInCells[i]);
        }
    }

    bool Contains(int number)
    {
        int hashKey = UniversalHash(_hashFuncA, _hashFuncB, _primeNumber, _tableSize, number);
        if (hashKey < 0)
            hashKey = -hashKey;
        return _buckets[hashKey].Contains(number);
    }
};

} // namespace chain_hash

#endif  // CHAIN_HASH_CHAIN_HASH_H_
