//
// Created by rrzhang on 19-3-1.
//
#include <iostream>


void huoquzhi(int *ptr) {
    *ptr = 3;
}

int b;

void shezhizhi(const int &ptr) {
    b = ptr;
}

int main() {
    int zhi;
    huoquzhi(&zhi);
    std::cout << zhi << std::endl;

    shezhizhi(zhi);
    std::cout << b << std::endl;
}