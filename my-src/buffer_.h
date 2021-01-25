//
// Created by rrzhang on 19-2-25.
//

#ifndef LSM_TREE_BUFFER_H
#define LSM_TREE_BUFFER_H

#include <set>
#include <vector>
#include "data_store.h"
#include "sst_.h"
#include "config.h"

class Buffer {
private:
    int size;

public:
    std::set<entry_t> entries;

    Buffer(int max_size) : size(max_size) {};

    RetCode put(const entry_t &entry)  ;
    RetCode get(entry_t* entry) const;
    std::vector<entry_t> *range(const entry_t &start_entry, const entry_t &end_entry) const;
    void clear();

//    std::set<entry_t> get_entries(){return this->entries; }
};
#endif //LSM_TREE_BUFFER_H
