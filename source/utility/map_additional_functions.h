#pragma once

#include <cassert>

#include <map>


// the function is similar to map.at, but does not affect performance in production
template <typename Key, typename Value, typename Alloc>
inline const Value& safe_find(const std::map<Key, Value, Alloc>& source_map, const Key& key) {
    auto it = source_map.find(key);
    assert(it != source_map.end());
    return it->second;
}
