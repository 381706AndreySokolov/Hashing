cmake_minimum_required(VERSION 2.6)

project("Functional Tests")

add_subdirectory("${PROJECT_SOURCE_DIR}/test_utils")
add_subdirectory("${PROJECT_SOURCE_DIR}/chain_hash")
add_subdirectory("${PROJECT_SOURCE_DIR}/open_adr_hash")
add_subdirectory("${PROJECT_SOURCE_DIR}/perfect_hash")
add_subdirectory("${PROJECT_SOURCE_DIR}/cuckoo_hash")




