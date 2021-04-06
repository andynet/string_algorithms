cmake_minimum_required(VERSION 3.17)
project(string_algorithms C)

set(CMAKE_C_STANDARD 99)

add_executable(naive_SACA src/naive_SACA.c)
add_executable(test test/test_naive_SACA.c)

