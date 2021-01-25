//
// Created by rrzhang on 19-3-4.
//

#include "../my-src/buffer_.h"
#include <iostream>
#include <cstring>
#include "../my-src/data_store.h"
using namespace std;

int main(){

    Buffer buffer(10);

    for(int i = 0; i<5; i++){
        entry_t entry(to_string(i+1));
        Location location;
        buffer.put(to_string(i+1), location);
    }

    for(const auto &entry : buffer.entries){
        cout<<entry.key<<" ";
    }
}