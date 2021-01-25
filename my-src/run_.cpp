//
// Created by rrzhang on 19-2-21.
//
#include <cassert>
#include <cstdio>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <sstream>
#include <cstring>

#include "run_.h"

Run::Run(const long &size_per_run, const int &bf_bits_per_entry, const int &level_id, const int &run_id) :
        size(size_per_run), bloomFilter(size_per_run * bf_bits_per_entry) {
    used_size = 0;
    mmap_size = size * sizeof(entry_t);
    entry_ptr = nullptr;

    init(level_id, run_id);
}

Run::~Run() {
    if (sst.fd >= 0) {
        sst.fd = close(sst.fd);
    }
    if (entry_ptr != nullptr) {
        unmap();
    }
}

void Run::init(int level_id, int run_id) {


    std::string path = BASEDIR + std::to_string(level_id) + "_" + std::to_string(run_id) + ".txt";
//    std::cout << path << std::endl;

    bool new_create;
    if (!(0 == access(path.c_str(), F_OK))) { new_create = true; }

    int fd = open(path.c_str(), O_RDWR | O_CREAT, 0644);
    if (fd >= 0) {  //文件打洞
        if (posix_fallocate(fd, 0, mmap_size) != 0) {
            std::cerr << "posix_fallocate failed: " << strerror(errno) << std::endl;
            close(fd);
        }
    }
//      if (fd > 0) { std::cout << "文件打开或创建成功" << std::endl; }

    sst.path = path;
    sst.fd = fd;

    mapping();
    if (new_create) { memset(entry_ptr, 0, mmap_size); }
}

void Run::mapping() {
    mapping(0, mmap_size);
}

void Run::mapping(size_t index, size_t s) {
    if (sst.fd <= 0) { sst.fd = open(sst.path.c_str(), O_RDWR | O_CREAT, 0644); }
    if (entry_ptr != nullptr) { unmap(); }
    entry_ptr = (entry_t *) mmap(NULL, s, PROT_READ | PROT_WRITE, MAP_SHARED, sst.fd, index);
}

void Run::unmap() {
    munmap(entry_ptr, mmap_size);       //若后面mapping改变了长度，这个地方会出问题
    entry_ptr = nullptr;
}

void Run::put(entry_t entry) {     //    std::cout << "Run::put" << std::endl;
    assert(entry_ptr != nullptr);
    assert(used_size <= size);

    bloomFilter.set(entry.key);
    memcpy(&entry_ptr[used_size++], &entry, sizeof(entry_t)); //    entry_ptr[used_size++] = entry;
}

entry_t Run::lower_bound_(entry_t *entries, size_t size, entry_t key) {
    size_t first = 0, middle;
    size_t half, len = size;

    while (len > 0) {
        half = len >> 1;
        middle = first + half;
        if (entries[middle] < key) {
            first = middle + 1;
            len = len - half - 1;       //在右边子序列中查找
        } else
            len = half;            //在左边子序列（包含middle）中查找
    }
    return entries[first];
}

RetCode Run::get(entry_t *entry) {      //    std::cout << "in Run::get" << std::endl;
    RetCode ret = keyNotFound;
    if (!bloomFilter.is_set(entry->key)) {
        return ret;
    }
    entry_t search_entry = lower_bound_(entry_ptr, size, *entry);

    if (*entry == search_entry) {
        (*entry) = search_entry;
        ret = succ;
    }
    return ret;
}

void Run::deletefile() {
    remove(sst.path.c_str());       //    std::cout<<"deleted "<<sst.path.c_str()<<std::endl;
}