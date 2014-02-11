#ifndef __TreeSitter__TransitionSet__
#define __TreeSitter__TransitionSet__

#include <vector>
#include <functional>
#include "rule.h"

namespace tree_sitter {
    template<typename TKey, typename TValue>
    class transition_map {
        typedef std::shared_ptr<TKey> TKeyPtr;
        typedef std::shared_ptr<TValue> TValuePtr;
        typedef std::pair<TKeyPtr, TValuePtr> pair_type;
        typedef std::vector<pair_type> contents_type;

        contents_type contents;

    public:
        transition_map() : contents(contents_type()) {};
        transition_map(std::vector<pair_type> pairs) : contents(pairs) {};
        
        bool operator==(const transition_map<TKey, TValue> &other) const {
            if (size() != other.size()) return false;
            for (int i = 0; i < size(); i++) {
                auto left = contents[i];
                auto right = other.contents[i];
                if (!(*left.first == *right.first) ||
                    !(*left.second == *right.second)) return false;
            }
            return true;
        }
        
        void add(TKeyPtr key, TValuePtr value) {
            contents.push_back(pair_type(key, value));
        }
        
        TValuePtr operator[](const TKey &key) const {
            for (auto pair : *this) {
                if (*pair.first == key) {
                    return pair.second;
                }
            }
            return TValuePtr();
        }
        
#pragma mark - Container

        typedef typename contents_type::const_iterator const_iterator;
        typedef typename contents_type::iterator iterator;
        iterator begin() { return contents.begin(); }
        iterator end() { return contents.end(); }
        const_iterator begin() const { return contents.begin(); }
        const_iterator end() const { return contents.end(); }
        size_t size() const { return contents.size(); }
    };
    
    template<typename K, typename V>
    std::ostream& operator<<(std::ostream &stream, const transition_map<K, V> &map) {
        stream << std::string("[");
        bool started = false;
        for (auto pair : map) {
            if (started) stream << std::string(", ");
            stream << pair.first->to_string() << std::string(" => ");
            stream << *pair.second;
            started = true;
        }
        stream << std::string("]");
        return stream;
    }
}


#endif
