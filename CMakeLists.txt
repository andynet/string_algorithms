cmake_minimum_required(VERSION 3.16)
project(string_algorithms C)

set(CMAKE_C_STANDARD 99)

add_library(suffix_array src/suffix_array.h src/suffix_array.c)

add_executable(naive_SACA src/naive_SACA.c)
target_link_libraries(naive_SACA PRIVATE suffix_array)

add_executable(test_SACA test/test_suffix_array.c)
target_link_libraries(test_SACA suffix_array check m rt pthread subunit)
