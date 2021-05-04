#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include "hashing.h"

#define CHAIN_DIVIDE_MODE_TIME
#define CHAIN_MUL_MODE_TIME
#define CHAIN_UNIV_MODE_TIME
#define CHAIN_K_IND_MODE_TIME
#define CHAIN_STD_MODE_TIME

#define OPEN_ADR_LIN_MODE_TIME
#define OPEN_ADR_QUADRIC_MODE_TIME
#define OPEN_ADR_DOUBLE_MODE_TIME

#define PERFECT_HASH_TIME

#define CUCKOO_HASH_TIME

int main()
{
    std::cout << "======================Dictionary===================" << std::endl;
    constexpr std::uint64_t wordsCount{466552UL}; // Words in english.txt file
    std::uint64_t           wordsInserted{0UL};   // Inserted words into a hash table
    std::uint64_t           fillFactor{10UL};      // Expected hash table fill factor
    size_t                  tableSize{wordsCount / fillFactor};

    std::string word{};
    std::string fileName("performance/english.txt");
    std::ifstream inFile;

#ifdef CHAIN_DIVIDE_MODE_TIME
{
    std::cout << "======================CHAIN_DIVIDE_MODE_TIME===================" << std::endl;

    inFile.open(fileName.c_str());
    if(!inFile)
    {
        std::cout << "Unable to open file \"" << fileName << "\"!" << std::endl;
        throw "Unable to open file!";
    }

    using TableType = chain_hash::HashTable<std::string, std::uint64_t, 1>;
    TableType table(tableSize);

    auto start = std::chrono::system_clock::now();

    while(getline(inFile, word))
    {
        table.insert(word, wordsInserted);
        wordsInserted++;
    }
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elasped_seconds = end-start;

    std::cout << "Total time = "  << elasped_seconds.count() << 
    ". Inserted " << wordsInserted << " words of " << wordsCount << std::endl;
    std::cout << "Table size = " << tableSize << std::endl;
    inFile.close();
    wordsInserted = 0UL;
}
#endif

#ifdef CHAIN_MUL_MODE_TIME
{
    std::cout << "======================CHAIN_MUL_MODE_TIME===================" << std::endl;

    inFile.open(fileName.c_str());
    if(!inFile)
    {
        std::cout << "Unable to open file \"" << fileName << "\"!" << std::endl;
        throw "Unable to open file!";
    }

    using TableType = chain_hash::HashTable<std::string, std::uint64_t, 2>;
    TableType table(tableSize);

    auto start = std::chrono::system_clock::now();

    while(getline(inFile, word))
    {
        table.insert(word, wordsInserted);
        wordsInserted++;
    }
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elasped_seconds = end-start;

    std::cout << "Total time = "  << elasped_seconds.count() << 
    ". Inserted " << wordsInserted << " words of " << wordsCount << std::endl;
    std::cout << "Table size = " << tableSize << std::endl;
    inFile.close();
    wordsInserted = 0UL;
}
#endif

#ifdef CHAIN_UNIV_MODE_TIME
{
    std::cout << "======================CHAIN_UNIV_MODE_TIME===================" << std::endl;

    inFile.open(fileName.c_str());
    if(!inFile)
    {
        std::cout << "Unable to open file \"" << fileName << "\"!" << std::endl;
        throw "Unable to open file!";
    }

    using TableType = chain_hash::HashTable<std::string, std::uint64_t, 3>;
    TableType table(tableSize);
    table.initUniversalHash();

    auto start = std::chrono::system_clock::now();

    while(getline(inFile, word))
    {
        table.insert(word, wordsInserted);
        wordsInserted++;
    }
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elasped_seconds = end-start;

    std::cout << "Total time = "  << elasped_seconds.count() << 
    ". Inserted " << wordsInserted << " words of " << wordsCount << std::endl;
    std::cout << "Table size = " << tableSize << std::endl;
    inFile.close();
    wordsInserted = 0UL;
}
#endif

#ifdef CHAIN_K_IND_MODE_TIME
{
    std::cout << "======================CHAIN_K_IND_MODE_TIME===================" << std::endl;

    inFile.open(fileName.c_str());
    if(!inFile)
    {
        std::cout << "Unable to open file \"" << fileName << "\"!" << std::endl;
        throw "Unable to open file!";
    }

    using TableType = chain_hash::HashTable<std::string, std::uint64_t, 4>;
    TableType table(tableSize);

    auto start = std::chrono::system_clock::now();

    while(getline(inFile, word))
    {
        table.insert(word, wordsInserted);
        wordsInserted++;
    }
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elasped_seconds = end-start;

    std::cout << "Total time = "  << elasped_seconds.count() << 
    ". Inserted " << wordsInserted << " words of " << wordsCount << std::endl;
    std::cout << "Table size = " << tableSize << std::endl;
    inFile.close();
    wordsInserted = 0UL;
}
#endif

#ifdef CHAIN_STD_MODE_TIME
{
    std::cout << "======================CHAIN_STD_MODE_TIME===================" << std::endl;

    inFile.open(fileName.c_str());
    if(!inFile)
    {
        std::cout << "Unable to open file \"" << fileName << "\"!" << std::endl;
        throw "Unable to open file!";
    }

    using TableType = chain_hash::HashTable<std::string, std::uint64_t, 5>;
    TableType table(tableSize);

    auto start = std::chrono::system_clock::now();

    while(getline(inFile, word))
    {
        table.insert(word, wordsInserted);
        wordsInserted++;
    }
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elasped_seconds = end-start;

    std::cout << "Total time = "  << elasped_seconds.count() << 
    ". Inserted " << wordsInserted << " words of " << wordsCount << std::endl;
    std::cout << "Table size = " << tableSize << std::endl;
    inFile.close();
    wordsInserted = 0UL;
}
#endif

#ifdef OPEN_ADR_LIN_MODE_TIME
{
    std::cout << "======================OPEN_ADR_LIN_MODE_TIME===================" << std::endl;

    inFile.open(fileName.c_str());
    if(!inFile)
    {
        std::cout << "Unable to open file \"" << fileName << "\"!" << std::endl;
        throw "Unable to open file!";
    }

    using TableType = open_adr_hash::HashTable<std::string, std::uint64_t, 1>;
    TableType table(tableSize * 15U);

    auto start = std::chrono::system_clock::now();

    while(getline(inFile, word))
    {
        bool ret = table.insert(word, wordsInserted);
        if (ret)
            wordsInserted++;
    }
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elasped_seconds = end-start;

    std::cout << "Total time = "  << elasped_seconds.count() << 
    ". Inserted " << wordsInserted << " words of " << wordsCount << std::endl;
    std::cout << "Table size = " << tableSize << std::endl;
    inFile.close();
    wordsInserted = 0UL;
}
#endif

#ifdef OPEN_ADR_QUADRIC_MODE_TIME
{
    std::cout << "======================OPEN_ADR_QUADRIC_MODE_TIME===================" << std::endl;

    inFile.open(fileName.c_str());
    if(!inFile)
    {
        std::cout << "Unable to open file \"" << fileName << "\"!" << std::endl;
        throw "Unable to open file!";
    }

    using TableType = open_adr_hash::HashTable<std::string, std::uint64_t, 2>;
    TableType table(tableSize * 15U);

    auto start = std::chrono::system_clock::now();

    while(getline(inFile, word))
    {
        bool ret = table.insert(word, wordsInserted);
        if (ret)
            wordsInserted++;
    }
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elasped_seconds = end-start;

    std::cout << "Total time = "  << elasped_seconds.count() << 
    ". Inserted " << wordsInserted << " words of " << wordsCount << std::endl;
    std::cout << "Table size = " << tableSize << std::endl;
    inFile.close();
    wordsInserted = 0UL;
}
#endif

#ifdef OPEN_ADR_DOUBLE_MODE_TIME
{
    std::cout << "======================OPEN_ADR_DOUBLE_MODE_TIME===================" << std::endl;

    inFile.open(fileName.c_str());
    if(!inFile)
    {
        std::cout << "Unable to open file \"" << fileName << "\"!" << std::endl;
        throw "Unable to open file!";
    }

    using TableType = open_adr_hash::HashTable<std::string, std::uint64_t, 2>;
    TableType table(tableSize * 15U);

    auto start = std::chrono::system_clock::now();

    while(getline(inFile, word))
    {
        bool ret = table.insert(word, wordsInserted);
        if (ret)
            wordsInserted++;
    }
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elasped_seconds = end-start;

    std::cout << "Total time = "  << elasped_seconds.count() << 
    ". Inserted " << wordsInserted << " words of " << wordsCount << std::endl;
    std::cout << "Table size = " << tableSize << std::endl;
    inFile.close();
    wordsInserted = 0UL;
}
#endif

#ifdef PERFECT_HASH_TIME
{
    std::cout << "======================PERFECT_HASH_TIME===================" << std::endl;

    inFile.open(fileName.c_str());
    if(!inFile)
    {
        std::cout << "Unable to open file \"" << fileName << "\"!" << std::endl;
        throw "Unable to open file!";
    }

    using TableType = chain_hash::HashTable<std::string, std::uint64_t, 5>;
    TableType table(tableSize);

    auto start = std::chrono::system_clock::now();

    while(getline(inFile, word))
    {
        table.insert(word, wordsInserted);
        wordsInserted++;
    }
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elasped_seconds = end-start;

    std::cout << "Total time = "  << elasped_seconds.count() << 
    ". Inserted " << wordsInserted << " words of " << wordsCount << std::endl;
    std::cout << "Table size = " << tableSize << std::endl;
    inFile.close();
    wordsInserted = 0UL;
}
#endif

#ifdef CUCKOO_HASH_TIME
{
    std::cout << "======================CUCKOO_HASH_TIME===================" << std::endl;

    inFile.open(fileName.c_str());
    if(!inFile)
    {
        std::cout << "Unable to open file \"" << fileName << "\"!" << std::endl;
        throw "Unable to open file!";
    }

    using TableType = chain_hash::HashTable<std::string, std::uint64_t, 5>;
    TableType table(tableSize + tableSize / 2U );

    auto start = std::chrono::system_clock::now();

    while(getline(inFile, word))
    {
        table.insert(word, wordsInserted);
        wordsInserted++;
    }
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elasped_seconds = end-start;

    std::cout << "Total time = "  << elasped_seconds.count() << 
    ". Inserted " << wordsInserted << " words of " << wordsCount << std::endl;
    std::cout << "Table size = " << tableSize << std::endl;
    inFile.close();
    wordsInserted = 0UL;
}
#endif

    return 0;
}