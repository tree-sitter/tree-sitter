#ifndef __TreeSitter__TransitionSet__
#define __TreeSitter__TransitionSet__

#include <vector>
#include <functional>
#include <initializer_list>
#include "rule.h"

namespace tree_sitter {
    template<typename TKey, typename TValue>
    class transition_map {
        typedef std::shared_ptr<const TKey> TKeyPtr;
        typedef std::shared_ptr<const TValue> TValuePtr;
        typedef std::pair<const TKeyPtr, TValuePtr> pair_type;
        typedef std::vector<pair_type> contents_type;

    public:
        
        transition_map() : contents(contents_type()) {};
        transition_map(std::initializer_list<pair_type> pairs) : contents(pairs) {};
        
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
        
        void merge(const transition_map<TKey, TValue> &other, std::function<TValuePtr(TValuePtr, TValuePtr)> merge_fn) {
            for (pair_type other_pair : other) {
                if (pair_type *current_pair = pair_for_key(*other_pair.first))
                    current_pair->second = merge_fn(current_pair->second, other_pair.second);
                else
                    add(other_pair.first, other_pair.second);
            }
        }
        
        template<typename NewV>
        transition_map<TKey, NewV> map(std::function<const std::shared_ptr<const NewV>(TValuePtr)> map_fn) {
            transition_map<TKey, NewV> result;
            for (pair_type pair : *this) {
                auto new_value = map_fn(pair.second);
                result.add(pair.first, new_value);
            }
            return result;
        }

#pragma mark - Container

        typedef typename contents_type::const_iterator const_iterator;
        typedef typename contents_type::iterator iterator;
        iterator begin() { return contents.begin(); }
        iterator end() { return contents.end(); }
        const_iterator begin() const { return contents.begin(); }
        const_iterator end() const { return contents.end(); }
        size_t size() const { return contents.size(); }

    private:
        
        pair_type * pair_for_key(const TKey &key) {
            for (int i = 0; i < contents.size(); i++) {
                pair_type *pair = &contents[i];
                if (*pair->first == key) return pair;
            }
            return NULL;
        }
        
        contents_type contents;
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
