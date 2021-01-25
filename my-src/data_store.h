// Copyright [2018] Alibaba Cloud All rights reserved
#ifndef ENGINE_SIMPLE_DATA_STORE_H_
#define ENGINE_SIMPLE_DATA_STORE_H_

//#include <string>
#include <cstring>
#include <unistd.h>
#include "config.h"
#include "sst_.h"
#include "data_store.h"


class DataStore {
public:
    explicit DataStore(const std::string dir)
            : fd_(-1), dir_(dir) {}

    ~DataStore() {
        if (fd_ > 0) { close(fd_); }
    }

    RetCode init();

    RetCode read_data(const Location &l, std::string *value);

    RetCode append(const std::string &value, Location *location);

private:
    int fd_;
    std::string dir_;
    std::string path;
    Location next_location_;

    RetCode OpenCurFile();
};

#endif  // ENGINE_SIMPLE_DATA_STORE_H_
