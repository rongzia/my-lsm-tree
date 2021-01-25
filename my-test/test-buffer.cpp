//
// Created by rrzhang on 19-3-4.
//

#include "../my-src/buffer_.h"
#include <iostream>
#include <cstring>
using namespace std;

int main(){

    Buffer buffer(10);

    for(int i = 0; i<5; i++){
        entry_t entry(to_string(i+1), to_string(i+11));
        buffer.put(entry);
    }

    for(const auto &entry : buffer.entries){
        cout<<entry.key<<" "<<entry.value<<endl;
    }
}