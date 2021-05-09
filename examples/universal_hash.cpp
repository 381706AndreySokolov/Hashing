
#include <iostream>
#include <string>
#include "utils/universal_hash.h"

int main()
{
    constexpr size_t tableSize{10};

    constexpr int    intKey{12};
    UniversalHash<int> UniversalHashInt(tableSize);

    unsigned int idx_int = UniversalHashInt.hash(intKey);

    std::cout << "=========================================" << std::endl;
    std::cout << "tableSize = " << tableSize << std::endl;
    std::cout << "=========================================" << std::endl;
    std::cout << "int key = " << intKey << std::endl;
    std::cout << "Index for int key = " << idx_int << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}