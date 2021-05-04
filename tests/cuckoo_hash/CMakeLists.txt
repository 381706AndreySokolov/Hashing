cmake_minimum_required(VERSION 3.5)

project("Open adress Hash Functional Tests")
enable_testing()
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -O2")

file(GLOB CPP_SOURCES "*.cpp")

add_executable(cuckoo_hash_tests ${CPP_SOURCES})

include_directories("${CMAKE_SOURCE_DIR}/tests/test_utils/include")
include_directories("${CMAKE_SOURCE_DIR}/library/include")
# include_directories("${CMAKE_SOURCE_DIR}/3rdparty/gtest/googletest/include")
include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(cuckoo_hash_tests
                      PUBLIC
                      tests_utils
                      ${GTEST_LIBRARIES}
                      pthread
)




