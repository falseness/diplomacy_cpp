#pragma once

#include <cassert>

#include <map>
#include <set>


// the function is similar to map.at, but does not affect performance in production
template <typename Key, typename Value, typename Alloc>
inline const Value& safe_find(const std::map<Key, Value, Alloc>& source_map, const Key& key) {
    auto it = source_map.find(key);
    assert(it != source_map.end());
    return it->second;
}

template <typename Key, typename Alloc>
inline void unique_insert(std::set<Key, Alloc>& source_set, Key key) {
    bool was_inserted = source_set.insert(key).second;
    assert(was_inserted);
}

template <typename Key, typename Alloc>
inline void guaranteed_erase(std::set<Key, Alloc>& source_set, Key key) {
    bool was_erased = source_set.erase(key);
    assert(was_erased);
}
