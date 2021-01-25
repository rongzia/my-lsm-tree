//
// Created by rrzhang on 19-3-6.
//

#include <iostream>
#include <cstring>
using namespace std;

int main(){
    string str1(8, 's');
    string str2(8, 's');

    str1[0] = '\0';
    str2[0] = '\0';

    cout<<(str1 == str2);
}