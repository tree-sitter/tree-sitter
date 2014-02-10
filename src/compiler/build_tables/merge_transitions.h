#ifndef __tree_sitter__merge_transitions__
#define __tree_sitter__merge_transitions__

#include "transition_map.h"
#include "character_set.h"
#include "symbol.h"

namespace tree_sitter {
    namespace build_tables {
        template<typename T>
        transition_map<rules::Symbol, T>
        merge_sym_transitions(const transition_map<rules::Symbol, T> &left,
                              const transition_map<rules::Symbol, T> &right,
                              std::function<std::shared_ptr<T>(std::shared_ptr<T>, std::shared_ptr<T>)> merge_fn) {
            transition_map<rules::Symbol, T> result(left);
            for (auto &pair : right) {
                auto rule = pair.first;
                bool merged = false;
                for (auto &existing_pair : result) {
                    auto existing_rule = existing_pair.first;
                    if (existing_rule->operator==(*rule)) {
                        existing_pair.second = merge_fn(existing_pair.second, pair.second);
                        merged = true;
                        break;
                    }
                }
                if (!merged)
                    result.add(pair.first, pair.second);
            }
            return result;
        }
        
        template<typename T>
        transition_map<rules::CharacterSet, T>
        merge_char_transitions(const transition_map<rules::CharacterSet, T> &left,
                               const transition_map<rules::CharacterSet, T> &right,
                               std::function<std::shared_ptr<T>(std::shared_ptr<T>, std::shared_ptr<T>)> merge_fn) {
            transition_map<rules::CharacterSet, T> result(left);
            for (auto &pair : right) {
                auto rule = pair.first;
                for (auto &existing_pair : left) {
                    auto existing_rule = existing_pair.first;
                    auto intersection = existing_rule->remove_set(*rule);
                    if (!intersection.is_empty()) {
                        rule->remove_set(intersection);
                        result.add(std::make_shared<rules::CharacterSet>(intersection), merge_fn(existing_pair.second, pair.second));
                    }
                }
                result.add(rule, pair.second);
            }
            return result;
        }
    }
}

#endif
