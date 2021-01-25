//
// Created by rrzhang on 19-2-20.
//
#include "../my-src/bloomfilter_.h"
#include <iostream>
#include <string.h>
#include <malloc.h>
using namespace std;

int main(){


    BloomFilter bf(10);
//    BloomFilter bf(INT32_MAX);
//    std::string str = {'a', 'b', '\0', 'c'};
    std::string str = {'a', 'b', 'c'};
    char* key = (char*) malloc(str.size());
    memcpy(key, str.c_str(), str.size());

    cout<<"key : "<<key<<endl<<"size of key : "<<str.size()<<endl;
    bf.set( key );
    std::cout<<"key is set : "<<bf.is_set(key)<<endl;


    cout<< "bloom size : "<<bf.get_table_size()<<endl;
    cout<<"pagesize : "<<getpagesize()<<endl; //4096
    return 0;
}
