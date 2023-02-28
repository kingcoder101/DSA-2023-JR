cmake_minimum_required(VERSION 3.5)

project(DSA_homework_4_BinarySearchTree LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(DSA_homework_4_BinarySearchTree
        main.cpp
        src/gtest-all.cc
        include/gtest/gtest.h
)

include_directories(include src .)

install(TARGETS DSA_homework_4_BinarySearchTree
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
