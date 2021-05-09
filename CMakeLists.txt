cmake_minimum_required(VERSION 2.6)

project(Hashing)

set (${PROJECT_NAME}_VERSION_MAJOR 0)
set (${PROJECT_NAME}_VERSION_MINOR 1)
set (${PROJECT_NAME}_VERSION_PATCH 0)
set (${PROJECT_NAME}_VERSION_TWEAK 0)
set (${PROJECT_NAME}_VERSION "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_PATCH}.${${PROJECT_NAME}_VERSION_TWEAK}")

set(CMAKE_VERBOSE_MAKEFILE ON)

include(cmake_utils/macro.cmake)

export_gtest()

add_subdirectory("${CMAKE_SOURCE_DIR}/library")

# add_subdirectory("${CMAKE_SOURCE_DIR}/3rdparty/gtest")

add_subdirectory("${CMAKE_SOURCE_DIR}/performance")

add_subdirectory("${CMAKE_SOURCE_DIR}/tests")

add_subdirectory("${CMAKE_SOURCE_DIR}/examples")
