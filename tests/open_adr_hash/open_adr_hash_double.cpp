#include <testing.h>

TEST(open_adr_hashing, double_1_1) 
{
    constexpr size_t tableSize = 10U;
    using TableType = open_adr_hash::HashTable<int, std::string, 3>;
    TableType table(tableSize);

    std::string name("Vasiliy");
    
    table.insert(63, name);
    auto value = table[63];

    ASSERT_EQ(value, name);
}

TEST(open_adr_hashing, double_1_2) 
{
    constexpr size_t tableSize = 10U;
    using TableType = open_adr_hash::HashTable<std::string, std::string, 3>;
    TableType table(tableSize);

    std::string key("SomeWord");
    std::string name("Vasiliy");

    table.insert(key, name);

    auto value = table[key];

    ASSERT_EQ(value, name);
}
