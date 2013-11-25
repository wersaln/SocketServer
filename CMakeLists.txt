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

# Set depending on the boost.

# Compose boost libraries as static.
set(Boost_USE_STATIC_LIBS ON)

# Use the multithreaded version.
set(Boost_USE_MULTITHREADED ON)

# Does not replace the standard library.
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(LibEvent)

message(STATUS "Searching for Boost...")
find_package(Boost 1.52 COMPONENTS
  date_time
  filesystem
  program_options
  system
  unit_test_framework
  iostreams
  regex
  serialization
  context
  timer
  chrono
  thread
  atomic
)

message(STATUS "Boost components summary:")
message(STATUS "  date time: ${Boost_DATE_TIME_LIBRARY}")
message(STATUS "  filesystem: ${Boost_FILESYSTEM_LIBRARY}")
message(STATUS "  program options: ${Boost_PROGRAM_OPTIONS_LIBRARY}")
message(STATUS "  system: ${Boost_SYSTEM_LIBRARY}")
message(STATUS "  unit test framework: ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}")
message(STATUS "  iostreams: ${Boost_IOSTREAMS_LIBRARY}")
message(STATUS "  serialization: ${Boost_SERIALIZATION_LIBRARY}")
message(STATUS "  regex: ${Boost_REGEX_LIBRARY}")
message(STATUS "  context: ${Boost_CONTEXT_LIBRARY}")
message(STATUS "  timer: ${Boost_TIMER_LIBRARY}")
message(STATUS "  chrono: ${Boost_CHRONO_LIBRARY}")
message(STATUS "  atomic: ${Boost_ATOMIC_LIBRARY}")

if (Boost_FOUND)
  message(STATUS "Boost library dirs: " ${Boost_LIBRARY_DIRS})
  message(STATUS "Boost include dirs: " ${Boost_INCLUDE_DIRS})
  include_directories(${Boost_INCLUDE_DIRS})
else ()
  message(FATAL_ERROR "Some boost libraries not found.")
endif ()

# Putting it in the directories from the list below:
add_subdirectory(src)
