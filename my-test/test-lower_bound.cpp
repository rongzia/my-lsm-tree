//
// Created by rrzhang on 19-3-7.
//
#include <iostream>
#include "../my-src/sst_.h"
using namespace std;

entry_t my_lower_bound2(entry_t *entries, size_t size, entry_t key)
{
    size_t first = 0,middle;
    size_t half, len;
    len = size;


    while(len > 0) {
        half = len >> 1;
        middle = first + half;
        if(entries[middle] < key) {
            first = middle + 1;
            len = len-half-1;       //在右边子序列中查找
        }
        else
            len = half;            //在左边子序列（包含middle）中查找
    }
    return entries[first];
}

int main(){
    entry_t entry1("5");
    entry_t entry2("6");
    entry_t entry3("7");
    entry_t entry4("9");

    entry_t entries[3];
    entries[0] = entry1;
    entries[1] = entry2;
    entries[3] = entry3;

    entry_t entry = my_lower_bound2(entries, 3, entry4);
    cout<<entry.key;
}