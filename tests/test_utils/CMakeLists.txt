cmake_minimum_required(VERSION 2.6)

project("Utils for functional tests")

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_BUILD_TYPE Release)

set(lib_name tests_utils)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")

file(GLOB CPP_HEADERS "include/*.h")
file(GLOB CPP_SOURCES "src/*.cpp")

add_library(${lib_name} STATIC ${CPP_HEADERS} ${CPP_SOURCES})

target_include_directories( ${lib_name}
                            PUBLIC ${PROJECT_SOURCE_DIR}/include
)

include_directories(${GTEST_INCLUDE_DIRS})
include_directories("${CMAKE_SOURCE_DIR}/library/include")

target_link_libraries(${lib_name}
                      PUBLIC
                      hashing_lib
                      ${GTEST_LIBRARIES}
)