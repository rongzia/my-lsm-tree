//
// Created by rrzhang on 19-2-22.
//

#include "merge_.h"

void MergeContext::add(entry_t *entries, size_t used_size) {
    merge_entry_t merge_entry;

    if (used_size > 0) {
        merge_entry.entries = entries;
        merge_entry.used_size = used_size;
        merge_vector.emplace_back(entries, used_size, 0);
        num_runs++;
        all_entries += used_size;
    }
}
bool cmp_(entry_t a,entry_t b){
    return a < b;
}

entry_t MergeContext::next() {
    std::vector<entry_t> external;   //存放要比较的item,即每个run的最前端的数
    int merge_entry_index;      //指向external中最小值对应于哪个run
    std::vector<entry_t>::iterator it_external;

    for (int i = 0; i < num_runs; i++) { external.push_back(merge_vector[i].entries[0]); }

    it_external = min_element(external.begin(), external.end(), cmp_);
    merge_entry_index = it_external - external.begin();

    merge_vector[merge_entry_index].used_size--;
    if(merge_vector[merge_entry_index].used_size > 0) {
        merge_vector[merge_entry_index].entries++;
    }else if(merge_vector[merge_entry_index].used_size == 0){
        merge_vector.erase(merge_vector.begin() + merge_entry_index);
        num_runs--;
    }

    all_entries--;
//    cout<<"next : "<<(*it_external).key<<endl;
    return *it_external;
}

bool MergeContext::done() {
    return (0 == all_entries);
}