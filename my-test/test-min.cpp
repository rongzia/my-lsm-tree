//
// Created by rrzhang on 19-3-1.
//

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

bool cmp(int a,int b){
    return a<=b;
}

int main(){

    vector<int> a = {2,3,4,5,1,1,1};
    vector<int>::iterator p = min_element(a.begin(), a.end(), cmp);
    cout<<p-a.begin()<<endl;
    cout<<*p;
}