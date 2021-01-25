//
// Created by rrzhang on 19-2-21.
//

#include "lsm_tree_.h"

LSMTree::LSMTree(int buffer_size, int bits_per_entry, int num_threads, int depth, int fanout)
        : buffer(buffer_size), bf_bits_per_entry(bits_per_entry) {
    long run_size = buffer_size;

    for (int i = 0; i < depth; i++){
        levels.push_back(new Level(fanout, run_size, i+1));
        run_size = run_size*fanout;
        std::cout<<"levels["<<i<<"]"<<"'s"<<" run_size: "<<levels[i]->get_size_per_run() << ". fanout: "<<levels[i]->get_num_run()<<std::endl;
    }
}

LSMTree::~LSMTree() {
    merge_down(levels.begin());
    flush_buffer();
    for(auto &level : levels){
        delete level;
    }
}

void LSMTree::merge_down(std::vector<Level*>::iterator current_level) {     //std::cout<< "in LSMTree::merge_down"<< std::endl;
    std::vector<Level*>::iterator next;
    MergeContext merge_ctx;
    entry_t entry;

    assert( current_level >= levels.begin());

    if ( (*current_level)->remaining() > 0) {   // std::cout<< "当前level仍有空间" << std::endl;
        return;
    } else if (current_level >= levels.end() - 1) {  //levels.end()-1 为最下一层
        std::cout << ("No more space in tree.");
    } else {
        next = current_level + 1;
    }

    //递归执行merge_down
    if ((*next)->remaining() == 0) {
        merge_down(next);
        assert( (*next)->remaining() > 0);
    }

    //把当前level的所有run添加到上下文当中
    for (auto &run : (*current_level)->runs) {
        merge_ctx.add(run->get_entry_ptr(), run->get_used_size());
    }

    (*next)->runs.push_front( new Run((*next)->get_size_per_run(), bf_bits_per_entry, (*next)->get_Level_id(), (*next)->runs.size()) );

    while (!merge_ctx.done()) {
        entry = merge_ctx.next();
//        if ( entry.location.offset >= 0) {    // 把已经删除的键值对过滤掉，对应的offset < 0
            (*next)->runs.front()->put(entry);
//        }
    }

    for (auto &run : (*current_level)->runs) {
        run->deletefile();      // run.~Run();
    }

    (*current_level)->clear();      //此处会调用~run()析构函数，不需要像上面显示调用
}

RetCode LSMTree::put(const entry_t &entry){
    put(entry.key, entry.value);
}


RetCode LSMTree::put(const KEY_t &key, const VAL_t &value) {
    boost::unique_lock<boost::shared_mutex> ul(mutex);
    if(buffer.full()){
        merge_down(levels.begin());
        flush_buffer();
    }
    ul.unlock();

    entry_t entry( key, value );
    RetCode ret = buffer.put(entry);

    assert(succ == ret);
    return ret;
}

VAL_t LSMTree::get(const KEY_t &key){
    VAL_t value;
    if(succ == get(key, &value)){
        return value;
    }else {
        return NULL;
    }
}

RetCode LSMTree::get(const KEY_t &key, VAL_t* value ) {     //    std::cout<< "in LSMTree::get"<< std::endl;

    entry_t entry(key);
    RetCode ret = buffer.get(&entry);
    if(succ == ret){
        value->assign(entry.value, MAX_VALUE_LENGTH);
        return ret;
    }
    else if(keyNotFound == ret){
        ret = search_run(&entry);
        value->assign(entry.value, MAX_VALUE_LENGTH);
        assert( succ == ret);
        return ret;
    }

// TODO: 判断值是否存在或已删除
//    if (nullptr != value && VAL_TOMBSTONE != *value) { return value; }

    return ret;
}

RetCode LSMTree::search_run(entry_t* entry){
    std::vector<Level*>::iterator it_level = levels.begin();
    std::deque<Run*>::iterator it_run;
    RetCode ret = keyNotFound;

    while( it_level != levels.end()){
        it_run = (*it_level)->runs.begin();
        while( it_run != (*it_level)->runs.end()){
            ret = (*it_run)->get(entry);
            if(succ == ret){ return ret; }
            it_run++;
        }
        it_level++;
    }
    return ret;
}

void LSMTree::flush_buffer(){

    levels.front()->runs.push_front( new Run(levels.front()->get_size_per_run(), bf_bits_per_entry, 1 , levels.front()->runs.size()) );
    for (const auto &entry : buffer.entries) {
        levels.front()->runs.front()->put(entry);
    }
    buffer.clear();
}
