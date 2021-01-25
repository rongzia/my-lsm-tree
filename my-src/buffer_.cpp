//
// Created by rrzhang on 19-2-25.
//

#include <cstring>
#include "buffer_.h"

RetCode Buffer::put(const entry_t &entry) {
    if (entries.size() == size) {
        return bufferFull;
    }

    std::set<entry_t>::iterator it_entry = entries.find(entry);
    if (it_entry != entries.end()) {
        entries.erase(it_entry);
    }

    entries.insert(entry);
    return succ;
}

RetCode Buffer::get(entry_t* entry) const {
    std::set<entry_t>::iterator it_entry = entries.find(*entry);

    if (it_entry == entries.end()) {
        return keyNotFound;
    } else {
        (*entry).location = it_entry->location;
        return succ;
    }
}

std::vector<entry_t> *Buffer::range(const entry_t &start_entry, const entry_t &end_entry) const {
    entry_t searched_entry;
    std::set<entry_t>::iterator subrange_start, subrange_end;

    memcpy(searched_entry.key, start_entry.key, MAX_KEY_LENGTH);
    subrange_start = entries.lower_bound(searched_entry);

    memcpy(searched_entry.key, end_entry.key, MAX_KEY_LENGTH);
    subrange_end = entries.upper_bound(searched_entry);

    return new std::vector<entry_t>(subrange_start, subrange_end);
}


void Buffer::clear() {
    entries.clear();
}