//
// Created by rrzhang on 19-2-21.
//

#ifndef LSM_TREE_CONFIG_H
#define LSM_TREE_CONFIG_H

#include <iostream>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/shared_mutex.hpp>

#define DEFAULT_TREE_DEPTH 5            //树深 5
#define DEFAULT_TREE_FANOUT 10          //扇区 10
#define DEFAULT_BUFFER_NUM_PAGES 1000   //缓存大小 1000
#define DEFAULT_THREAD_COUNT 4          //线程数 4
#define DEFAULT_BF_BITS_PER_ENTRY 3   //跟bloomfilter大小相关,每个键值对在bloomfilter中对应位数

#define MAX_KEY_LENGTH 8
#define MAX_VALUE_LENGTH 128

#define BASEDIR "/home/rrzhang/Desktop/sst/"
//#define BASEDIR "C:\\Users\\rrzhang\\Desktop\\sst\\"

typedef std::string KEY_t;
typedef std::string VAL_t;


enum RetCode {
    error = 0,
    succ = 1,
    keyNotFound = 2,
    bufferFull = 3,
    otherError = 9
};

#endif //LSM_TREE_CONFIG_H
