//
// Created by rrzhang on 19-2-21.
//

#ifndef LSM_TREE_LEVEL_H
#define LSM_TREE_LEVEL_H

#include <deque>
#include "run_.h"

class Level {

private:
    int num_run;        //num_run和fanout相等
    int level_id;
    long size_per_run;

public:
    std::deque<Run> runs;
//    int num_used_run;

    Level(int num, long size, int id) : num_run(num), size_per_run(size), level_id(id)
//    , num_used_run(0)
    {}

    bool remaining() const { return num_run > runs.size(); }

    long get_size_per_run() { return this->size_per_run; }

    int get_Level_id() { return this->level_id; }
    int get_num_run() { return this->num_run; }
//    deque<Run> get_runs() const& { return this->runs; }

};


#endif //LSM_TREE_LEVEL_H
