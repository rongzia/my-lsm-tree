//
// Created by rrzhang on 2019/3/1.
//

#include <iostream>
#include <cstring>
#include "../my-src/merge_.h"
#include "../my-src/sst_.h"
using namespace std;

int main(){

    entry_t entries[3][3];
    int count = 1;
//    for(int i = 0; i<10; i++){
//        for(int j = 0; j<10; j++){
//            memcpy(entries[i][j].key, to_string(count++).data(), 8 );
//        }
//    }

    for(int i = 7; i <= 9; i++){
        memcpy(entries[0][i-7].key, to_string(i).data(), 8 );
    }
    for(int i = 4; i <= 6; i++){
        memcpy(entries[1][i-4].key, to_string(i).data(), 8 );
    }
    for(int i = 1; i <= 3; i++){
        memcpy(entries[2][i-1].key, to_string(i).data(), 8 );
    }

    MergeContext mergeContext;
    for(int i = 0; i<3; i++) {
        mergeContext.add( entries[i], 3 );
    }

    entry_t entry;
    while ( !mergeContext.done()){
        entry = mergeContext.next();
//        cout<<"key : "<<entry.key<<endl;
    }
    return 0;
}