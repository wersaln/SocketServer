include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(NAME protobuf_example)
add_executable(${NAME}
  main.cc
  shake_protocol.pb.cc
)

target_link_libraries(${NAME}
  -lprotobuf
  -lpthread
)