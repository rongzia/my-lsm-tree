//
// Created by rrzhang on 19-3-6.
//

#include <iostream>
#include <deque>
using namespace std;

int main(){

    deque<int> deque1;
    deque1.emplace_back(1);

    deque<int>::iterator it_deque = deque1.begin();

    cout<<( deque1.end() - deque1.begin() );

}