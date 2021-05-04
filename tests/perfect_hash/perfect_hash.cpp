#include <testing.h>

TEST(perfect_hashing, perfect_hashing_1_1) 
{
    constexpr size_t tableSize = 10U;
    using TableType = perfect_hash::HashTable<int, std::string>;
    TableType table{};

    constexpr int         key = 63;
    const     std::string name("Vasiliy");

    using InputVecorType = std::vector<std::pair<int, std::string>>;

    table.Initialize(tableSize, InputVecorType{{key, name}});

    auto value = table.Contains(key);

    ASSERT_EQ(value, true);
}

TEST(perfect_hashing, perfect_hashing_1_2) 
{
    constexpr size_t tableSize = 10U;
    using TableType = perfect_hash::HashTable<std::string, std::string>;
    TableType table{};

    const std::string key("SomeWord");
    const std::string name("Vasiliy");

    using InputVecorType = std::vector<std::pair<std::string, std::string>>;

    table.Initialize(tableSize, InputVecorType{{key, name}});
    auto value = table.Contains(key);

    ASSERT_EQ(value, true);
}
