include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(NAME socket_client)
add_executable(${NAME}
  client.cc
)
