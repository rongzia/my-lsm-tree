//
// Created by rrzhang on 19-2-25.
//

#ifndef LSM_TREE_WORKER_POOL_H
#define LSM_TREE_WORKER_POOL_H

#include <functional>
#include <vector>
#include "thread_pool.h"
using namespace std;

typedef function<void()> worker_task;

class WorkerPool : ThreadPool {
    vector<future<void>> futures;
public:
    using ThreadPool::ThreadPool;
    void launch(worker_task&);
    void wait_all(void);
};

class DynamicWorkerPool {
    vector<thread> workers;
public:
    void launch(worker_task&);
    void wait_all(void);
};


#endif //LSM_TREE_WORKER_POOL_H
