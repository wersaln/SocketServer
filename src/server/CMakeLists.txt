include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(NAME socket_server)
add_executable(${NAME}
  server.cc
)

set(NAME2 asio_server)
add_executable(${NAME2}
  asio_server.cc
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