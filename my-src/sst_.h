//
// Created by rrzhang on 19-2-28.
//

#ifndef LSM_TREE_SST_H
#define LSM_TREE_SST_H

#include <cstdint>
#include <cstring>
#include "config.h"

struct entry_ {
    char key[MAX_KEY_LENGTH];
    char value[MAX_VALUE_LENGTH];

    entry_() {};
    entry_(const entry_ &entry){
        memcpy(key, entry.key, MAX_KEY_LENGTH);
        memcpy(value, entry.value, MAX_VALUE_LENGTH);
    }
    entry_(std::string key_) {
        memset(key, 0, MAX_KEY_LENGTH);
        memcpy(key, key_.data(), key_.size() < MAX_KEY_LENGTH ? key_.size() : MAX_KEY_LENGTH);
    }
    entry_(std::string key_, std::string value_) {
        memset(key, 0, MAX_KEY_LENGTH);
        memcpy(key, key_.data(), key_.size() < MAX_KEY_LENGTH ? key_.size() : MAX_KEY_LENGTH);
        memset(value, 0, MAX_VALUE_LENGTH);
        memcpy(value, value_.data(), value_.size() < MAX_VALUE_LENGTH ? value_.size() : MAX_VALUE_LENGTH);
    }

    entry_& operator = (const entry_ &entry){
        memcpy(key, entry.key, MAX_KEY_LENGTH);
        memcpy(value, entry.value, MAX_VALUE_LENGTH);
    }
    bool operator==(const entry_ &other) const { return 0 == memcmp(key, other.key, MAX_KEY_LENGTH); }
    bool operator<(const entry_ &other) const { return memcmp(key, other.key, MAX_KEY_LENGTH) < 0; }
    bool operator>(const entry_ &other) const { return memcmp(key, other.key, MAX_KEY_LENGTH) > 0; }
};
typedef struct entry_ entry_t;

struct sst {
    int fd;
    std::string path;
};
typedef struct sst sst_t;


#endif //LSM_TREE_SST_H
