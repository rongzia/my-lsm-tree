//
// Created by rrzhang on 19-2-26.
//

#include "../my-src/lsm_tree_.h"

int main() {

    LSMTree lsmTree(DEFAULT_BUFFER_NUM_PAGES, DEFAULT_BF_BITS_PER_ENTRY, DEFAULT_THREAD_COUNT, DEFAULT_TREE_DEPTH, DEFAULT_TREE_FANOUT);




    VAL_t value;
    for (int i = 100; i >= 1; i--) {
//        string key = to_string(i+1);
        lsmTree.put(to_string(i), to_string(i));
//        lsmTree.get(to_string(i+1), &value);
//        std::cout<<"main value : "<<value<<std::endl;
    }

    for (int i = 1; i <= 100; i++) {
        RetCode ret = lsmTree.get(to_string(i), &value);
        if (succ == ret) {
            std::cout << "main value : " << value << std::endl;
        }
    }

    return 0;
}