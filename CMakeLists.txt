cmake_minimum_required(VERSION 3.16)
project(string_algorithms C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic -march=native")

# build libraries
add_library(ctoi lib/ctoi.h lib/ctoi.c)
add_library(ndarray lib/ndarray.h lib/ndarray.c)
add_library(suffix_array src/suffix_array.h src/suffix_array.c)

# build tests
add_executable(test_ctoi test/ctoi.c)
target_link_libraries(test_ctoi criterion ctoi)

add_executable(test_ndarray test/test_ndarray.c)
target_link_libraries(test_ndarray criterion ndarray)

add_executable(test_SACA test/test_suffix_array.c)
target_link_libraries(test_SACA suffix_array check m rt pthread subunit)    # TODO: change to criterion

add_executable(test_bmh test/test_bmh.c)
target_link_libraries(test_bmh check m rt pthread subunit)                  # TODO: change to criterion

add_executable(test_suffix_tree test/suffix_tree_test.c)
target_link_libraries(test_suffix_tree criterion)

add_executable(test_jaccard_dist test/test_jaccard.c)
target_link_libraries(test_jaccard_dist criterion ctoi)

# build executables
add_executable(run test/run.c)
target_link_libraries(run ctoi)

add_executable(naive_SACA src/naive_SACA.c)
target_link_libraries(naive_SACA suffix_array)

add_executable(jaccard_dist src/jaccard_dist.c)
target_link_libraries(jaccard_dist ctoi)
