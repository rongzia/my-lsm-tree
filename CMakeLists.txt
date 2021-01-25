cmake_minimum_required(VERSION 3.12)
project(lsm-tree)
set(CMAKE_CXX_STANDARD 11)

set(BOOST_ROOT /usr/local/boost)
find_package(Boost REQUIRED COMPONENTS thread)
message("${Boost_INCLUDE_DIRS}")
message("${Boost_LIBRARIES}")

#include_directories(generator)
include_directories(lib)
include_directories(src)

add_executable(lsm-tree
        my-test/test.cc
#        my-test/test-run.cpp
#        my-test/test-lsm.cpp
#        my-test/test-merge-entry.cpp
#        my-test/test-entry.cpp
#        my-test/test-bloomfilter.cpp
#        my-test/test-buffer.cpp


        my-src/bloomfilter_.cpp
        my-src/bloomfilter_.h
        my-src/buffer_.cpp
        my-src/buffer_.h
        my-src/config.h
        my-src/level_.h
        my-src/lsm_tree_.cpp
        my-src/lsm_tree_.h
        my-src/merge_.cpp
        my-src/merge_.h
        my-src/run_.cpp
        my-src/run_.h
        my-src/sst_.h
        my-src/util.cc
        my-src/util.h

        )
target_link_libraries(lsm-tree Boost::thread)