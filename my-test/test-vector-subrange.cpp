//
// Created by rrzhang on 19-2-25.
//
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main() {


    vector<int> vec;
    for (int i = 0; i < 10; i++) { vec.push_back(i); }
    vector<int>::iterator sub_begin = ++vec.begin();
    vector<int>::iterator sub_end = --vec.end();

    vector<int> new_vec(sub_begin, sub_end);


    for_each(new_vec.begin(), new_vec.end(), [](int x) { cout << x; });
//    for_each(vec.begin(),vec.end(),[](const int& x)->void{cout<<x;});
//    for(int it:vec){cout<<it;}

    cout << endl;

    cout<<*(vec.end()-1);
}