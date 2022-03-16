cmake_minimum_required(VERSION 3.21)
project(pmt)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(pmt
        src/main.cpp
        src/main.h)
