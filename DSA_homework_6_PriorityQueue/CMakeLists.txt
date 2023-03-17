cmake_minimum_required(VERSION 3.5)

project(DSA_homework_6_PriorityQueue LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(DSA_homework_6_PriorityQueue
        main.cpp
        src/gtest-all.cc
        include/gtest/gtest.h
)

include_directories(include src .)

install(DSA_homework_6_PriorityQueue
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
