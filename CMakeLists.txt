cmake_minimum_required(VERSION 3.12)
project(lsm-tree)
set(CMAKE_CXX_STANDARD 11)

set(BOOST_ROOT /usr/local/boost)
find_package(Boost REQUIRED COMPONENTS thread )
message("${Boost_INCLUDE_DIRS}")
message("${Boost_LIBRARIES}")

#include_directories(generator)
include_directories(lib)
include_directories(src)

add_executable(lsm-tree
        my-test/test.cc

        #        lib/thread_pool.h
        my-src/bloomfilter_.cpp
        my-src/bloomfilter_.h
        my-src/buffer_.cpp
        my-src/buffer_.h
        my-src/config.h
        my-src/data_store.cc
        my-src/data_store.h
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
        #        my-src/worker_pool_.cpp
        #        my-src/worker_pool_.h

        )
target_link_libraries(lsm-tree Boost::thread)