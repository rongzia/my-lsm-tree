//
// Created by rrzhang on 19-2-26.
//

#include "../my-src/lsm_tree_.h"
#include <iostream>
#include <cstring>

using namespace std;

int main() {

    LSMTree lsmTree(DEFAULT_BUFFER_NUM_PAGES, DEFAULT_BF_BITS_PER_ENTRY, DEFAULT_THREAD_COUNT, DEFAULT_TREE_DEPTH,
                    DEFAULT_TREE_FANOUT);


    VAL_t value;
    for (int i = 11; i >= 1; i--) {
        entry_t entry(to_string(i), to_string(i));
        lsmTree.put(entry);
    }

    for (int i = 1; i <= 11; i++) {
        RetCode ret = lsmTree.get(to_string(i), &value);
        if (succ == ret) {
            std::cout << "main value : " << value << std::endl;
        }
    }

    return 0;
}