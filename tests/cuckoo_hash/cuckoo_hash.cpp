#include <testing.h>

TEST(cuckoo_hashing, cuckoo_hashing_1_1) 
{
    constexpr size_t tableSize = 10U;
    using TableType = cuckoo_hash::HashTable<int, std::string>;
    TableType table(tableSize);

    std::string name("Vasiliy");

    table.insert(63, name);

    auto value = table.find(63);

    ASSERT_EQ(value, name);
}

TEST(cuckoo_hashing, cuckoo_hashing_1_2) 
{
    constexpr size_t tableSize = 10U;
    using TableType = cuckoo_hash::HashTable<std::string, std::string>;
    TableType table(tableSize);

    std::string key("SomeWord");
    std::string name("Vasiliy");

    table.insert(key, name);

    auto value = table.find(key);

    ASSERT_EQ(value, name);
}
