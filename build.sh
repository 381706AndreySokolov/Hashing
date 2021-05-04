# rm -r build

cmake CMakeLists.txt -Bbuild

cmake --build build

./build/performance/dictionary

echo
./build/tests/chain_hash/chain_hash_tests
echo
./build/tests/open_adr_hash/open_adr_hash_tests
echo
./build/tests/perfect_hash/perfect_hash_tests
echo
./build/tests/cuckoo_hash/cuckoo_hash_tests