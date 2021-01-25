//
// Created by rrzhang on 19-2-27.
//

#include "../my-src/sst_.h"
using namespace std;


int main()
{
    cout<<"entry size : "<<sizeof(entry_t)<<endl;
    entry_t e1("4");
    entry_t e2("3");

    cout<<(e1>e2)<<endl;
}