//
// Created by rrzhang on 19-2-28.
//

#include <sstream>
#include "../my-src/sst_.h"
#include <iostream>

using namespace std;

int compa(char a[], char b[]) {
    for (int i = 0; i < MAX_KEY_LENGTH; i++) {
        if (a[i] < b[i]) { return -1; }
        else if (a[i] > b[i]) { return 1; }
    }
    return 0;
}
void print(char a[], int len){
    for(int i = 0; i < len; i++){
        std::cout<< a[i];
    }std::cout<<std::endl;
}
int main() {
    entry_t entry1 = *(new entry_t("e"));

    entry_t entry2;
    string str = "en";
    memset(entry2.key, 0, MAX_KEY_LENGTH);
    memcpy(entry2.key, str.data(), str.size());

//    cout << str.size() << endl;
    cout << (compa(entry1.key , entry2.key) == 0 ? "equal":"not equal" )<< endl;

    cout << ( (entry1.key) == (entry2.key) ? "equal":"not equal") << endl;
    cout << ((entry1 < entry2) )<< endl;

    print(entry1.key,8);
    print(entry2.key,8);
}