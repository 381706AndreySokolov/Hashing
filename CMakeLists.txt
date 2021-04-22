cmake_minimum_required(VERSION 2.8) 

set(PROJECT_NAME HasingTables) 
project(${PROJECT_NAME})

set(main main)
set(chain_hash chain_hash)
set(open_adr_hash open_adr_hash)
set(perfect_hash perfect_hash)
set(graph_hash graph_hash)
set(cuckoo_hash cuckoo_hash)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
if(NOT CMAKE_BUILD_TYPE) 
  set(CMAKE_BUILD_TYPE Release) 
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/chain_hash)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/open_adr_hash)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/perfect_hash)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/graph_hash)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cuckoo_hash)

add_subdirectory(main)
add_subdirectory(chain_hash)
add_subdirectory(open_adr_hash)
add_subdirectory(perfect_hash)
add_subdirectory(graph_hash)
add_subdirectory(cuckoo_hash)

file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")
