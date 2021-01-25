//
// Created by rrzhang on 19-2-20.
//

#include "bloomfilter_.h"


uint64_t BloomFilter::BKDRHash(char *str) const {
    uint64_t seed = 131; // 31 131 1313 13131 131313 etc..
    uint64_t hash = 0;

    while (*str) {
        hash = hash * seed + (*str);
        str++;
    }
//    return (hash & 0x7FFFFFFFFFFFFFFF);
    return (hash & 0x7FFFFFFF) % table.size();
}

uint64_t BloomFilter::APHash(char *str) const {
    uint64_t hash = 0;
    int i;

    for (i = 0; *str; i++) {
        if ((i & 1) == 0) {
            hash ^= ((hash << 7) ^ (*str++) ^ (hash >> 3));
        } else {
            hash ^= (~((hash << 11) ^ (*str++) ^ (hash >> 5)));
        }
    }

    return (hash & 0x7FFFFFFF) % table.size();
}

uint64_t BloomFilter::DJBHash(char *str) const {
    uint64_t hash = 5381;

    while (*str) {
        hash += (hash << 5) + (*str);
        str++;
    }

    return (hash & 0x7FFFFFFF) % table.size();
}


void BloomFilter::set(char* key) {
    table.set(BKDRHash(key));
    table.set(APHash(key));
    table.set(DJBHash(key));
}

bool BloomFilter::is_set(char* key) const {
    return (table.test(BKDRHash(key))
            && table.test(APHash(key))
            && table.test(DJBHash(key)));
}

void BloomFilter::clear() {
    this->table.clear();
}