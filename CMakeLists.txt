cmake_minimum_required(VERSION 2.8.3)
project(WebFramefork CXX C)

set(PROJECT_ROOT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(PROJECT_ROOT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(PROJECT_BASE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/base)

# Set path to binary directory as macro definition for programs.
add_definitions(-DROOT_BINARY_DIR=${PROJECT_ROOT_BINARY_DIR})

# The path to the directory where cmake modules are.
set(CMAKE_MODULE_PATH ${PROJECT_ROOT_SOURCE_DIR}/cmake)

# Connection assembly configuration.
include(Build)

# Putting it in the directories from the list below:
add_subdirectory(src)
