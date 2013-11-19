include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(NAME select_server)
add_executable(${NAME}
  select_server.cc
)

set(NAME2 asio_server)
add_executable(${NAME2}
  asio_server.cc
)

set(NAME3 poll_server)
add_executable(${NAME3}
  poll_server.cc
)

set(NAME4 event_server)
add_executable(${NAME4}
  event_server.cc
)

set(NAME5 epoll_server)
add_executable(${NAME5}
  epoll_server.cc
)

target_link_libraries(${NAME4}
  -levent
)
target_link_libraries(${NAME2}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_REGEX_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_IOSTREAMS_LIBRARY}
  ${Boost_TIMER_LIBRARY}
  ${Boost_CHRONO_LIBRARY}
  rt
)