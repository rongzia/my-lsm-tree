//
// Created by rrzhang on 19-2-20.
//

#ifndef LSM_TREE_BLOOMFILTER_H
#define LSM_TREE_BLOOMFILTER_H


#include <boost/dynamic_bitset.hpp>
#include "sst_.h"

class BloomFilter {
    boost::dynamic_bitset<> table;

public:
    uint64_t BKDRHash(char *) const;
    uint64_t APHash(char *) const;
    uint64_t DJBHash(char *) const;
    BloomFilter(unsigned long length) : table(length) {}
    void set_size(unsigned long length) { table.reserve(length); }
    void set(char* );
    bool is_set(char* ) const;

    unsigned long get_table_size() const{ return table.size(); }
    void clear();
};


#endif //LSM_TREE_BLOOMFILTER_H
