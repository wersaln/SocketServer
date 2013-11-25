include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(NAME atomic_example)
add_executable(${NAME}
  main.cc
)

target_link_libraries(${NAME}
  ${Boost_ATOMIC_LIBRARY}
  -lpthread
  -pthread
)