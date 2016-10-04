cmake_minimum_required(VERSION 3.2)
project(hash_table)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    dictionary.hpp
    main.cpp)

add_executable(hash_table ${SOURCE_FILES})