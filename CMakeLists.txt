cmake_minimum_required(VERSION 3.13)
project(lsm_tree_1)

set(CMAKE_CXX_STANDARD 11)

include_directories(my-src)
include_directories(src)

add_executable(lsm_tree_1
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
#        my-test/string_char.cpp
#        my-test/test-bloomfilter.cpp
#        my-test/test-boost.cpp
#        my-test/test-buffer.cpp
#        my-test/test-cmp-string.cpp
#        my-test/test-coppare-char.cpp
#        my-test/test-dataStore.cpp
#        my-test/test-deque.cpp
#        my-test/test-duoluguibing.cpp
#        my-test/test-entry.cpp
#        my-test/test-lower_bound.cpp
        my-test/test-lsm.cpp
#        my-test/test-merge-entry.cpp
#        my-test/test-merge.cpp
#        my-test/test-min.cpp
#        my-test/test-mmap.cpp
#        my-test/test-run.cpp
#        my-test/test-vector-subrange.cpp
#        my-test/test-zhizhen-yinyong.cpp
#        my-test/test.cc
        )
