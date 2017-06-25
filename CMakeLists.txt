cmake_minimum_required(VERSION 2.6)
project(Stet)

# version
set (Stet_VERSION_MAJOR 0)
set (Stet_VERSION_MINOR 1)

# use clang compiler
# set(CMAKE_C_COMPILER "/usr/bin/clang")

# compile flags
set (CMAKE_C_FLAGS "-Wall -Wextra -pedantic -std=c99")

# cmake
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# zeromq
find_package(ZeroMQ REQUIRED)
include_directories(${ZMQ_INCLUDE_DIRS})

# zeromq
add_subdirectory(external/cppzmq)
include_directories(external/cppzmq)


set(LIBRARIES
  ${ZMQ_LIBRARY}
  boost_system
  )

# create executable
add_executable(Stet src/stet.cpp src/server.cpp)
include_directories(src/)
target_link_libraries(Stet ${LIBRARIES})

