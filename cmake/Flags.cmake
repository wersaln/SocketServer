
# Definitions for build types.
if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  # Flags fog GCC.

  if (${CMAKE_COMPILER_IS_GNUCXX})
    add_definitions(-ggdb3)
    # Profiling: run cmake -DGPROF=1.
    if (GPROF)
      add_definitions(-pg)
      set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
    endif (GPROF)

    # Do not allow function inlining in debug mode.
    add_definitions(-fno-inline-functions -fno-inline)
    add_definitions(-std=gnu++11)
  endif (${CMAKE_COMPILER_IS_GNUCXX})
elseif (${CMAKE_BUILD_TYPE} STREQUAL "Release")
  # Flags for GCC.
  add_definitions(-std=gnu++11)
  if (${CMAKE_COMPILER_IS_GNUCXX})
    add_definitions(-O3)
    add_definitions(-DNDEBUG=1)
  endif (${CMAKE_COMPILER_IS_GNUCXX})
endif (${CMAKE_BUILD_TYPE} STREQUAL "Debug")

