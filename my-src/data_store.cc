// Copyright [2018] Alibaba Cloud All rights reserved
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <vector>
#include "util.h"
#include "data_store.h"



static const int kDataFilePrefixLen = 5;
//static const int kSingleFileSize = 1024 * 1024 * 100;


RetCode DataStore::init() {
    if (!FileExists(dir_)
        && 0 != mkdir(dir_.c_str(), 0755)) {
        return otherError;
    }

    std::vector<std::string> files;
    if (0 != GetDirFiles(dir_, &files)) {
        return otherError;
    }

    // Get last data file offset
    path  = path + BASEDIR + "db.txt";
//            ; path = path + BASEDIR + "db.txt";
    int len = GetFileLength(path.c_str());
    next_location_.offset = len > 0 ? len : 0;

    // Open file
    return OpenCurFile();
}

RetCode DataStore::append(const std::string &value, Location *location) {

    // std::cout<<"DataStore::Read::"<<std::endl;
    if (0 != FileAppend(fd_, value)) {
        return otherError;
    }

    location->offset = next_location_.offset;
    location->len = value.size();

    next_location_.offset += location->len;
    return succ;
}

RetCode DataStore::read_data(const Location &l, std::string *value) {
    int fd = open(path.c_str(), O_RDONLY, 0644);
    if (fd < 0) {
        return otherError;
    }
    lseek(fd, l.offset, SEEK_SET);

//    std::cout<<"DataStore::Read::"<<"l.offset:"<<l.offset<<", l.len:"<<l.len<<std::endl;
    char *buf = new char[l.len]();
    char *pos = buf;
    uint32_t value_len = l.len;

    while (value_len > 0) {
        ssize_t r = read(fd, pos, value_len);
        if (r < 0) {
            if (errno == EINTR) {
                continue;  // Retry
            }
            close(fd);
            return otherError;
        }
        pos += r;
        value_len -= r;
    }
    *value = std::string(buf, l.len);

    delete buf;
    close(fd);
    return succ;
}

RetCode DataStore::OpenCurFile() {
    int fd = open(path.c_str(), O_APPEND | O_WRONLY | O_CREAT, 0644);
    if (fd < 0) {
        return otherError;
    }
    fd_ = fd;
    return succ;
}

