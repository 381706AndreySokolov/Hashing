cmake_minimum_required(VERSION 3.5)

project("Hashing Library")

# The version number.
set (${PROJECT_NAME}_VERSION_MAJOR 0)
set (${PROJECT_NAME}_VERSION_MINOR 1)
set (${PROJECT_NAME}_VERSION_PATCH 0)
set (${PROJECT_NAME}_VERSION_TWEAK 0)
set (${PROJECT_NAME}_VERSION "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_PATCH}.${${PROJECT_NAME}_VERSION_TWEAK}")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")

#-------------------- Create a library -----------------------------------------
# Generate the shared library from the library sources
#-------------------------------------------------------------------------------

# include_directories("${PROJECT_SOURCE_DIR}/include")

set(lib_name hashing_lib)

file(GLOB HEADERS "${PROJECT_SOURCE_DIR}/include/hashing.h")
file(GLOB HEADERS "${PROJECT_SOURCE_DIR}/include/*/*.h")
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*/*.cpp")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -O3")

add_library(${lib_name} STATIC ${HEADERS} ${SOURCES})

target_include_directories( ${lib_name}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)
