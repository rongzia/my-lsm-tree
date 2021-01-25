#include <assert.h>
#include <stdio.h>
#include <string>

#include <thread>
#include <mutex>
#include <random>
#include <iostream>
#include <algorithm>
#include <set>

#include "../my-src/lsm_tree_.h"

template <typename T>
class threadsafe_vector : public std::vector<T>
{
public:
    void add(const T& val)
    {
        std::lock_guard<std::mutex> lock(mMutex);
        this->push_back(val);
    }

    void add(T&& val)
    {
        std::lock_guard<std::mutex> lock(mMutex);
        this->emplace_back(val);
    }

private:
    mutable std::mutex mMutex;
};

class RandNum_generator
{
private:
    RandNum_generator(const RandNum_generator&) = delete;
    RandNum_generator& operator=(const RandNum_generator&) = delete;
    std::uniform_int_distribution<unsigned> u;
    std::default_random_engine e;
    int mStart, mEnd;
public:
    // [start, end], inclusive, uniformally distributed
    RandNum_generator(int start, int end)
        : u(start, end)
        , e(std::hash<std::thread::id>()(std::this_thread::get_id()))
        , mStart(start), mEnd(end)
    {}

    // [mStart, mEnd], inclusive
    unsigned nextNum()
    {
        return u(e);
    }

    // [0, max], inclusive
    unsigned nextNum(unsigned max)
    {
        return unsigned((u(e) - mStart) / float(mEnd - mStart) * max);
    }
};

std::string random_str(RandNum_generator& rng, std::size_t strLen)
{
    std::string rs(strLen, ' ');
    for (auto& ch : rs) {
        ch = rng.nextNum();
    }
    return rs;
}

typedef unsigned long long hash64_t;


std::string key_from_value(const std::string& val)
{
    std::string key(8, ' ');
    
    key[0] = val[32];
    key[1] = val[65];
    key[2] = val[3];
    key[3] = val[96];
    key[4] = val[121];
    key[5] = val[48];
    key[6] = val[84];
    key[7] = val[29];
    
    return key;
}

void write_(LSMTree* lsmTree, threadsafe_vector<std::string>& keys, unsigned numWrite)
{
    RandNum_generator rng(1, 255);
    for (unsigned i = 0; i < numWrite; ++i) {
        std::string val(random_str(rng, 128));
        
        //std::string key = hash_to_str(fnv1_hash_64(val)); // strong hash, slow but barely any chance to duplicate
        std::string key(key_from_value(val)); // random positions, faster but tiny chance to duplicate

        lsmTree->put(key, val);
        keys.add(key);
    }
}

void randomRead(LSMTree* lsmTree, const threadsafe_vector<std::string>& keys, unsigned numRead)
{
    RandNum_generator rng(0, keys.size() - 1);
    for (unsigned i = 0; i < numRead; ++i) {
        auto& key = keys[rng.nextNum()];
        std::string val;
        lsmTree->get(key, &val);
        //if (key != hash_to_str(fnv1_hash_64(val)) {
        if (key != key_from_value(val)) {
            std::cout << "Random Read error: key and value not match" << std::endl;
            exit(-1);
        }
    }
}


int main()
{
//    auto numThreads = std::thread::hardware_concurrency();
    auto numThreads = 4;
    std::cout << numThreads << std::endl;

    LSMTree* lsmTree = new LSMTree(DEFAULT_BUFFER_NUM_PAGES, DEFAULT_BF_BITS_PER_ENTRY, DEFAULT_THREAD_COUNT, DEFAULT_TREE_DEPTH, DEFAULT_TREE_FANOUT);

    threadsafe_vector<std::string> keys;
    
    // Write
    auto writeStart = std::chrono::high_resolution_clock::now();
    unsigned numWrite = 100000;
    std::vector<boost::thread> writers;
    for (int i = 0; i < numThreads; ++i) {
        writers.emplace_back(boost::thread(write_, lsmTree, boost::ref(keys), numWrite));
    }
    for (auto& th : writers) {
        th.join();
    }
    writers.clear();
    
    auto writeEnd = std::chrono::high_resolution_clock::now();
    std::cout << "Writing takes: "
              << std::chrono::duration<double, std::milli>(writeEnd - writeStart).count()
              << " milliseconds" << std::endl;
    std::cout << keys.size() << std::endl;
    std::cout <<  keys.size()*1000 / std::chrono::duration<double, std::milli>(writeEnd - writeStart).count() << "/s" <<std::endl;
    std::sort(keys.begin(), keys.end());
    auto last = std::unique(keys.begin(), keys.end());
    keys.erase(last, keys.end());
    
    
    // Random Read
    auto rreadStart = std::chrono::high_resolution_clock::now();
    unsigned numRead = 100000;
    std::vector<boost::thread> rreaders;
    for (int i = 0; i < numThreads; ++i) {
        rreaders.emplace_back(boost::thread(randomRead, lsmTree, boost::cref(keys), numRead));
    }
    for (auto& th : rreaders) {
        th.join();
    }
    rreaders.clear();
    
    auto rreadEnd = std::chrono::high_resolution_clock::now();
    std::cout << "Random read takes: "
              << std::chrono::duration<double, std::milli>(rreadEnd - rreadStart).count()
              << " milliseconds" << std::endl;
    std::cout <<  keys.size()*1000 / std::chrono::duration<double, std::milli>(rreadEnd - rreadStart).count() << "/s" <<std::endl;
    std::cout << keys.size() << std::endl;
    
    delete lsmTree;

    return 0;
}

