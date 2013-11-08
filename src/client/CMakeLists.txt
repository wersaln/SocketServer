include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(NAME simple_client)
add_executable(${NAME}
  simple_client.cc
)

set(NAME2 multiconnect_client)
add_executable(${NAME2}
  multiconnect_client.cc
)


set(NAME3 asio_client)
add_executable(${NAME3}
  asio_client.cc
)

target_link_libraries(${NAME3}
  ${Boost_DATE_TIME_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_REGEX_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_IOSTREAMS_LIBRARY}
  ${Boost_TIMER_LIBRARY}
  ${Boost_CHRONO_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  rt
)