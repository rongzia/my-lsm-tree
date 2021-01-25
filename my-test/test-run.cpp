//
// Created by rrzhang on 19-3-1.
//

#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>

#include "../my-src/run_.h"

using namespace std;

struct str{
    int a;
    int b;
};

int main(){
    std::string path = "";
    path = path + BASEDIR + "123" + ".txt";

    int fd = open(path.c_str(), O_RDWR | O_CREAT, 0666);
    void * temp = mmap(NULL, 256, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    str * str1 = reinterpret_cast<str *>(temp);
    cout<<str1<<endl;
    cout<<fd<<endl;
    str str2;
    str2.a = 1;
    str2.b = 2;
     memcpy(str1 , &str2, sizeof(str));
    cout<<(*str1).a;
}