//
// Created by rrzhang on 19-3-6.
//

#include "../my-src/sst_.h"
#include "../my-src/data_store.h"
#include <iostream>

using namespace std;

int main() {
    DataStore dataStore1(BASEDIR);
    dataStore1.Init();
    DataStore dataStore2(BASEDIR);
    dataStore2.Init();

    entry_t entry1("1");
    entry_t entry2("2");

    dataStore1.Append((entry1.key), &entry1.location);
    dataStore2.Append(entry2.key, &entry2.location);

    cout << entry1.location.offset << endl;
    cout << entry1.location.len << endl;

    cout << entry2.location.offset << endl;
    cout << entry2.location.len << endl;

    VAL_t value1;
    VAL_t value2;
    dataStore1.Read(entry1.location, &value1);
    cout << value1 << endl;
    dataStore2.Read(entry2.location, &value2);
    cout<<value2<<endl;

}