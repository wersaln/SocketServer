cmake_minimum_required(VERSION 2.8.3)
project(WebFramefork CXX C)

set(ROOT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(ROOT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(BASE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/base)

# The path to the directory where cmake modules are.
set(CMAKE_MODULE_PATH ${ROOT_SOURCE_DIR}/framework/cmake)

# Putting it in the directories from the list below:
add_subdirectory(framework)
