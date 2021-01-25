//
// Created by rrzhang on 19-2-20.
//

#include <iostream>
//导入boost里面的timer
#include <boost/timer.hpp>

using namespace std;

int main() {

    boost::timer tm;

    std::cout << "Hello, World!" << std::endl;
    //输出程序运行的时间长度
    std::cout << tm.elapsed();

    return 0;
}