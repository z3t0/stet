cmake_minimum_required(VERSION 2.6)
project(Stet)

# version
set (Stet_VERSION_MAJOR 0)
set (Stet_VERSION_MINOR 1)

# all .c files in src
file(GLOB SOURCES src/*.c)

# create executable
add_executable(Stet ${SOURCES})
