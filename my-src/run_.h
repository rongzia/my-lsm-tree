//
// Created by rrzhang on 19-2-21.
//

#ifndef LSM_TREE_RUN_H
#define LSM_TREE_RUN_H

#include <vector>
#include <string>
#include "bloomfilter_.h"
#include "sst_.h"


class Run {
private:
    BloomFilter bloomFilter;
    size_t used_size, size;
    size_t mmap_size;

//    size_t fence_page_size;
//    std::vector<KEY_t> fence; //类似于索引，用pagesize取模，pagesize作个数用，并不是作页面大小用

    sst_t sst;
    entry_t *entry_ptr;
    entry_t lower_bound_(entry_t *entries, size_t size, entry_t key);
public:

    Run(const long &size_per_run, const int &bf_bits_per_entry, const int &level_id, const int &run_id);
    ~Run();

    void init(int level_id, int run_id);

    void mapping();
    void mapping(size_t index, size_t s);
    void unmap();

    void put( entry_t entry);
    RetCode get(entry_t* entry);
// TODO:
//    std::vector<entry_t> *range(KEY_t, KEY_t);

    long get_used_size() { return this->used_size; }
    entry_t* get_entry_ptr(){ return this->entry_ptr; }

    void deletefile();
};


#endif //LSM_TREE_RUN_H
