#ifndef __TreeSitter__TransitionSet__
#define __TreeSitter__TransitionSet__

#include <vector>
#include <functional>
#include "rule.h"

namespace tree_sitter {
    namespace rules {
        class Rule;

        template<typename MappedType>
        class TransitionMap {
        public:
            typedef std::shared_ptr<const Rule> rule_ptr;
            typedef std::shared_ptr<const MappedType> mapped_ptr;
            typedef std::pair<rule_ptr, mapped_ptr> pair_type;
            typedef std::vector<pair_type> contents_type;
            
            static bool elements_equal(const pair_type &left, const pair_type &right) {
                return (*left.first == *right.first) && (*left.second == *right.second);
            }
            
            TransitionMap() : contents(contents_type()) {};
            
            TransitionMap(std::initializer_list<Rule *> keys, std::initializer_list<MappedType *> values) : TransitionMap() {
                auto value_iter(values.begin());
                for (auto key_iter(keys.begin()); key_iter != keys.end(); ++key_iter) {
                    add(*key_iter, *value_iter);
                    ++value_iter;
                }
            }

            typedef typename contents_type::const_iterator const_iterator;
            typedef typename contents_type::iterator iterator;
            
            iterator begin() { return contents.begin(); }
            iterator end() { return contents.end(); }
            const_iterator begin() const { return contents.begin(); }
            const_iterator end() const { return contents.end(); }
            
            void add(const Rule *on_rule, const MappedType *to_value) {
                rule_ptr key(on_rule);
                mapped_ptr value(to_value);
                contents.push_back(pair_type(key, value));
            }

            void add(rule_ptr on_rule, mapped_ptr to_value) {
                rule_ptr key(on_rule);
                mapped_ptr value(to_value);
                contents.push_back(pair_type(key, value));
            }
            
            size_t size() const {
                return contents.size();
            }
            
            mapped_ptr operator[](Rule const &on_rule) const {
                pair_type *pair = pair_for_key(on_rule);
                if (pair)
                    return pair->second;
                else
                    return NULL;
            }
            
            mapped_ptr operator[](int i) const {
                return contents[i].second;
            }
            
            void merge(const TransitionMap<MappedType> &other, std::function<const MappedType *(const MappedType &, const MappedType &)> merge_fn) {
                for (pair_type other_pair : other) {
                    pair_type *current_pair = pair_for_key(*other_pair.first);
                    if (current_pair)
                        current_pair->second = mapped_ptr(merge_fn(*current_pair->second, *other_pair.second));
                    else
                        add(other_pair.first, other_pair.second);
                }
            }
            
        private:
            pair_type * pair_for_key(Rule const &key) {
                for (int i = 0; i < contents.size(); i++) {
                    pair_type *pair = &contents[i];
                    if (*pair->first == key) return pair;
                }
                return NULL;
            }
            
            contents_type contents;
        };
    }
}

#endif