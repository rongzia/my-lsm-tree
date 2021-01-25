//
// Created by rrzhang on 19-2-25.
//

#include <iostream>
#include "db_entry.h"
#include "../my-src/merge_.h"
using namespace std;

void print_entry(entry_t entry){
    cout<<entry.key<<" : "<<entry.val<<endl;
}

int main(){

    string strs[6][2] = {
            {"2", "4"}
            ,{"4", "7"}
            ,{"9", "1"}
            ,{"1", "1"}
            ,{"4","12"}
            ,{"7", "9"}
    };
    entry_t entry1[3];
    entry_t entry2[3];
    for(int i = 0; i<3; i++){
        entry1[i].key = strs[i][0];
        entry1[i].val = strs[i][1];
        entry2[i].key = strs[i+3][0];
        entry2[i].val = strs[i+3][1];
    }

    MergeContext *mergeContext = new MergeContext();
    mergeContext->add(entry2, 3);
    mergeContext->add(entry1, 3);

    for(int i = 0; i<5; i++){
        print_entry(mergeContext->next());
    }

    return 0;
}