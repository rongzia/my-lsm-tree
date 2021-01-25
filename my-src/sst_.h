//
// Created by rrzhang on 19-2-28.
//

#ifndef LSM_TREE_SST_H
#define LSM_TREE_SST_H

#include <cstdint>
#include <cstring>
#include "config.h"

struct Location {
    Location() : offset(0), len(0) {
    }
    uint64_t offset;
    uint32_t len;
};

struct entry_ {
    char key[MAX_KEY_LENGTH];
    Location location;

    entry_() {};

    entry_(std::string key_) {
        memset(key, 0, MAX_KEY_LENGTH);
        memcpy(key, key_.data(), key_.size());
    }

// TODO: 构造成string才好比较，不然比较的是地址,可能影响性能，后期改成自定义函数
    bool operator==(const entry_ &other) const { return std::string(key, MAX_KEY_LENGTH) == std::string(other.key, MAX_KEY_LENGTH); }
    bool operator<(const entry_ &other) const { return std::string(key, MAX_KEY_LENGTH) < std::string(other.key, MAX_KEY_LENGTH); }
    bool operator>(const entry_ &other) const { return std::string(key, MAX_KEY_LENGTH) > std::string(other.key, MAX_KEY_LENGTH); }
//    bool operator<=(const entry_ &other) const { return std::string(key, MAX_KEY_LENGTH) == std::string(other.key, MAX_KEY_LENGTH); }
};
typedef struct entry_ entry_t;

struct sst {
    int fd;
    std::string path;
};
typedef struct sst sst_t;

//这个算法中，first是最终要返回的位置


#endif //LSM_TREE_SST_H
