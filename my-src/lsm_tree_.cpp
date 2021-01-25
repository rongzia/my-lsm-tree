//
// Created by rrzhang on 19-2-21.
//

#include "lsm_tree_.h"

LSMTree::LSMTree(int buffer_size, int bits_per_entry, int num_threads, int depth, int fanout)
        : buffer(buffer_size), bf_bits_per_entry(bits_per_entry)
        , dataStore(BASEDIR) {
    long run_size = buffer_size;

    for (int i = 0; i < depth; i++){
        levels.push_back(new Level(fanout, run_size, i+1));
        run_size = run_size*fanout;
        cout<<"levels["<<i<<"]"<<"'s"<<" run_size: "<<levels[i]->get_size_per_run() << ". fanout: "<<levels[i]->get_num_run()<<endl;
    }
    dataStore.init();
}

LSMTree::~LSMTree() {
    merge_down(levels.begin());
    flush_buffer();
    for(auto &level : levels){
        delete level;
    }
}

void LSMTree::merge_down(vector<Level*>::iterator current_level) {

    vector<Level*>::iterator next;
    MergeContext merge_ctx;
    entry_t entry;

    assert( current_level >= levels.begin());

    if ( (*current_level)->remaining() > 0) {
//        std::cout<< "当前level仍有空间" << std::endl;
        return;
    } else if (current_level >= levels.end() - 1) {  //levels.end()-1 为最下一层
        cout << ("No more space in tree.");
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
        run->mapping();
        merge_ctx.add(run->get_entry_ptr(), run->get_used_size());
    }

    (*next)->runs.push_front( new Run((*next)->get_size_per_run(), bf_bits_per_entry, (*next)->get_Level_id(), (*next)->runs.size()) );
    (*next)->runs.front()->mapping();

    int count = 0;
    while (!merge_ctx.done()) {
        entry = merge_ctx.next();
        // 把已经删除的键值对过滤掉，对应的offset < 0
        if ( entry.location.offset >= 0) {
            (*next)->runs.front()->put(entry);
            count++;
        }
    }

    (*next)->runs.front()->unmap();

    for (auto &run : (*current_level)->runs) {
        run->deletefile();
//        run.~Run();
    }

//    (*current_level)->runs.clear();       //此处会调用~run()析构函数，不需要像上面显示调用
    (*current_level)->clear();
}

RetCode LSMTree::put(const KEY_t &key, const VAL_t &value) {
    boost::unique_lock<boost::shared_mutex> ul(mutex);

    Location location;
    entry_t entry(key);

    dataStore.append(value, &location);
    entry.location = location;

    if (succ == buffer.put(entry)) {
        return succ;
    }

    merge_down(levels.begin());
    ul.unlock();
    flush_buffer();
    assert(buffer.put(entry));
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
        ret = dataStore.read_data(entry.location, value);
        return ret;
    }
    else if(keyNotFound == ret){
        ret = search_run(&entry);
        assert( succ == ret);
        ret = dataStore.read_data(entry.location, value);
        return ret;
    }

// TODO: 判断值是否存在或已删除
//    if (nullptr != value && VAL_TOMBSTONE != *value) { return value; }

//    std::cout<< "out LSMTree::get"<< std::endl;
    return ret;
}

RetCode LSMTree::search_run(entry_t* entry){
    vector<Level*>::iterator it_level = levels.begin();
    deque<Run*>::iterator it_run;
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
    boost::unique_lock<boost::shared_mutex> ul(mutex);

    levels.front()->runs.push_front( new Run(levels.front()->get_size_per_run(), bf_bits_per_entry, 1 , levels.front()->runs.size()) );
    levels.front()->runs.front()->mapping();
    for (const auto &entry : buffer.entries) {
        levels.front()->runs.front()->put(entry);
    }
    levels.front()->runs.front()->unmap();

    buffer.clear();
}
