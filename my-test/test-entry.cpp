//
// Created by rrzhang on 19-2-27.
//

#include "../my-src/sst_.h"
using namespace std;


int main()
{
    cout<<"entry size : "<<sizeof(entry_t)<<endl;
    entry_t e1("10");
    entry_t e2("2");

    cout<<(e1<e2)<<endl;
}