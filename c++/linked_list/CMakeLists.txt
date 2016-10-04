cmake_minimum_required(VERSION 3.2)
project(linked_list)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    linked_list/main.cpp
    linked_list/s_linked_list.hpp)

add_executable(linked_list ${SOURCE_FILES})