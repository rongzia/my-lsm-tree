//
// Created by rrzhang on 19-2-21.
//

#ifndef LSM_TREE_LSM_TREE_H
#define LSM_TREE_LSM_TREE_H

#include "buffer_.h"
#include "level_.h"
#include "merge_.h"
#include "vector"
using namespace std;

class LSMTree {
private:
    Buffer buffer;
    float bf_bits_per_entry;
    std::vector<Level> levels;
    DataStore dataStore;

    void merge_down(std::vector<Level>::iterator);
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
