set (${PROJECT_NAME}_VERSION_MAJOR 0)
set (${PROJECT_NAME}_VERSION_MINOR 1)
set (${PROJECT_NAME}_VERSION_PATCH 0)
set (${PROJECT_NAME}_VERSION_TWEAK 0)
set (${PROJECT_NAME}_VERSION "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_PATCH}.${${PROJECT_NAME}_VERSION_TWEAK}")

# file(GLOB hdrs "*.h*") 
# file(GLOB srcs_random_numbers "random_*.cpp")
# file(GLOB srcs_dictionary "dictionar*.cpp")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -O3")


add_executable(random_numbers ${CMAKE_CURRENT_SOURCE_DIR}/random_numbers.cpp) 

target_link_libraries(random_numbers hashing_lib)

add_executable(dictionary ${CMAKE_CURRENT_SOURCE_DIR}/dictionary.cpp) 

target_link_libraries(dictionary hashing_lib)
