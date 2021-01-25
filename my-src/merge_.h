//
// Created by rrzhang on 19-2-22.
//

#ifndef LSM_TREE_MERGE_H
#define LSM_TREE_MERGE_H

#include <cassert>
#include <vector>
#include <algorithm>
#include "sst_.h"



struct merge_entry {    //类似run
    entry_t *entries;
    size_t used_size;
    size_t current_index = 0;

    merge_entry(){}
    merge_entry(entry_t *e, size_t u, size_t c) : entries(e), used_size(u), current_index(c){}
    bool done(void) const {return current_index == used_size;}

};

typedef struct merge_entry merge_entry_t;

class MergeContext {
private:
    std::vector<merge_entry_t> merge_vector;
    int num_runs;
    int all_entries;


public:
    MergeContext() : num_runs(0),all_entries(0) {}
    void add(entry_t* entries, size_t used_size);
    entry_t next(void);
    bool done(void);
};


#endif //LSM_TREE_MERGE_H
