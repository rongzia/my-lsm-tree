//
// Created by rrzhang on 19-2-20.
//
#include "../my-src/bloomfilter_.h"
#include <iostream>
#include <string.h>
#include <malloc.h>
using namespace std;

int main(){


    BloomFilter bf(1000);

    std::string str(MAX_KEY_LENGTH, 'c');
    str[2] = '\0';

    bf.set( (char* )str.data() );
    std::cout<<"key is set : "<<bf.is_set((char* )str.data())<<endl;

    cout<< "bloom size : "<<bf.get_table_size()<<endl;

    return 0;
}
