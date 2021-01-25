//
// Created by rrzhang on 19-2-21.
//

#ifndef LSM_TREE_LSM_TREE_H
#define LSM_TREE_LSM_TREE_H

#include "buffer_.h"
#include "level_.h"
#include "worker_pool_.h"
#include "merge_.h"


class LSMTree {
private:

    boost::shared_mutex mutex;
    Buffer buffer;
    float bf_bits_per_entry;
    vector<Level*> levels;
    DataStore dataStore;
//    WorkerPool worker_pool;

    void merge_down(vector<Level*>::iterator current_level);
    RetCode search_run(entry_t* entry);
public:
    LSMTree(int buffer_size, int bits_per_entry, int num_threads, int depth, int fanout);
    ~LSMTree();

    RetCode put(const KEY_t &key, const VAL_t &value);
    VAL_t get(const KEY_t &key);
    RetCode get(const KEY_t &key, VAL_t* value);

    void flush_buffer();

// TODO:
//    void range(KEY_t, KEY_t) const;
// TODO:
//    RetCode del(KEY_t);
// TODO:
//    RetCode load(std::string);
};


#endif //LSM_TREE_LSM_TREE_H
