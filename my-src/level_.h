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
    std::deque<Run*> runs;

    Level(int num, long size, int id) : num_run(num), size_per_run(size), level_id(id){}

    bool remaining() const { return num_run > runs.size(); }

    long get_size_per_run() { return this->size_per_run; }

    int get_Level_id() { return this->level_id; }
    int get_num_run() { return this->num_run; }

    void clear(){
        for(auto &run: runs ){
            delete run;
        }
        runs.clear();
    }

};


#endif //LSM_TREE_LEVEL_H
