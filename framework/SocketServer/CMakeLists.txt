include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(NAME socket_server)
add_executable(${NAME}
  server.cc
)
