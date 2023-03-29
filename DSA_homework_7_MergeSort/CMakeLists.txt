cmake_minimum_required(VERSION 3.5)

project(DSA_homework_7_MergeSort LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(DSA_homework_7_MergeSort
        main.cpp
        src/gtest-all.cc
        include/gtest/gtest.h
)

include_directories(include src .)

install(TARGETS DSA_homework_7_MergeSort
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
