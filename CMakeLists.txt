cmake_minimum_required(VERSION 3.3)
project(hyperloglog)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Werror")

set(SOURCE_FILES main.cpp hyperloglog.h)
add_executable(hyperloglog ${SOURCE_FILES})