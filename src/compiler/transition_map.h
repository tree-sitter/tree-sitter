#ifndef __TreeSitter__TransitionSet__
#define __TreeSitter__TransitionSet__

#include <vector>
#include <functional>
#include <initializer_list>
#include "rules.h"

namespace tree_sitter {
    template<typename MappedType>
    class TransitionMap {
        typedef std::shared_ptr<const rules::Rule> rule_ptr;
        typedef std::shared_ptr<const MappedType> mapped_ptr;
        typedef std::pair<rule_ptr, mapped_ptr> pair_type;
        typedef std::vector<pair_type> contents_type;

    public:
        static bool elements_equal(const pair_type &left, const pair_type &right) {
            return (*left.first == *right.first) && (*left.second == *right.second);
        }
        
        TransitionMap() : contents(contents_type()) {};
        TransitionMap(std::initializer_list<std::pair<rule_ptr, mapped_ptr>> pairs) : contents(pairs) {};
        
        typedef typename contents_type::const_iterator const_iterator;
        typedef typename contents_type::iterator iterator;
        
        iterator begin() { return contents.begin(); }
        iterator end() { return contents.end(); }
        const_iterator begin() const { return contents.begin(); }
        const_iterator end() const { return contents.end(); }
        
        void add(const rule_ptr on_rule, const mapped_ptr to_value) {
            contents.push_back(pair_type(on_rule, to_value));
        }
        
        size_t size() const {
            return contents.size();
        }
        
        mapped_ptr operator[](rules::Rule const &on_rule) const {
            pair_type *pair = pair_for_key(on_rule);
            if (pair)
                return pair->second;
            else
                return NULL;
        }
        
        mapped_ptr operator[](int i) const {
            return contents[i].second;
        }
        
        void merge(const TransitionMap<MappedType> &other, std::function<mapped_ptr(mapped_ptr, mapped_ptr)> merge_fn) {
            for (pair_type other_pair : other) {
                if (pair_type *current_pair = pair_for_key(*other_pair.first))
                    current_pair->second = merge_fn(current_pair->second, other_pair.second);
                else
                    add(other_pair.first, other_pair.second);
            }
        }


        TransitionMap<MappedType> where(std::function<bool(rule_ptr)> filter_fn) {
            TransitionMap<MappedType> result;
            for (pair_type pair : *this)
                if (filter_fn(pair.first))
                    result.add(pair.first, pair.second);
            return result;
        }
        
        template<typename NewMappedType>
        TransitionMap<NewMappedType> map(std::function<std::shared_ptr<const NewMappedType>(mapped_ptr)> map_fn) {
            TransitionMap<NewMappedType> result;
            for (pair_type pair : *this) {
                auto new_value = map_fn(pair.second);
                result.add(pair.first, new_value);
            }
            return result;
        }

    private:
        pair_type * pair_for_key(rules::Rule const &key) {
            for (int i = 0; i < contents.size(); i++) {
                pair_type *pair = &contents[i];
                if (*pair->first == key) return pair;
            }
            return NULL;
        }
        
        contents_type contents;
    };
    
    template<typename MappedType>
    std::ostream& operator<<(std::ostream &stream, const TransitionMap<MappedType> &map) {
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
