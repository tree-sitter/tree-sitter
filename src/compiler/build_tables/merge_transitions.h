#ifndef COMPILER_BUILD_TABLES_MERGE_TRANSITIONS_H_
#define COMPILER_BUILD_TABLES_MERGE_TRANSITIONS_H_

#include <map>
#include "compiler/rules/character_set.h"
#include "compiler/rules/symbol.h"

namespace tree_sitter {
    namespace build_tables {

        /*
         *  Merges two transition maps with symbol keys. If both maps
         *  contain values for the same symbol, the new value for that
         *  symbol will be computed by merging the two previous values
         *  using the given function.
         */
        template<typename T>
        std::map<rules::Symbol, T>
        merge_sym_transitions(const std::map<rules::Symbol, T> &left,
                              const std::map<rules::Symbol, T> &right,
                              std::function<T(T, T)> merge_fn) {
            std::map<rules::Symbol, T> result(left);
            for (auto &pair : right) {
                auto rule = pair.first;
                bool merged = false;
                for (auto &existing_pair : result) {
                    auto existing_rule = existing_pair.first;
                    if (existing_rule == rule) {
                        existing_pair.second = merge_fn(existing_pair.second, pair.second);
                        merged = true;
                        break;
                    }
                }
                if (!merged)
                    result.insert({ pair.first, pair.second });
            }
            return result;
        }

        /*
         *  Merges two transition maps with character set keys. If the
         *  two maps contain values for overlapping character sets, the
         *  new value for the two sets' intersection will be computed by
         *  merging the two previous values using the given function.
         */
        template<typename T>
        std::map<rules::CharacterSet, T>
        merge_char_transitions(const std::map<rules::CharacterSet, T> &left,
                               const std::map<rules::CharacterSet, T> &right,
                               std::function<T(T, T)> merge_fn) {
            std::map<rules::CharacterSet, T> result(left);
            for (auto &new_pair : right) {
                rules::CharacterSet new_rule = new_pair.first;
                T new_value = new_pair.second;
                
                for (auto &existing_pair : left) {
                    rules::CharacterSet existing_rule = existing_pair.first;
                    T existing_value = existing_pair.second;
                    
                    rules::CharacterSet intersection = existing_rule.remove_set(new_rule);
                    if (!intersection.is_empty()) {
                        result.erase(existing_pair.first);
                        if (!existing_rule.is_empty())
                            result.insert({ existing_rule, existing_value });
                        result.insert({ intersection, merge_fn(existing_value, new_value) });
                        new_rule.remove_set(intersection);
                    }
                }
                if (!new_rule.is_empty())
                    result.insert({ new_rule, new_pair.second });
            }
            return result;
        }
    }
}

#endif  // COMPILER_BUILD_TABLES_MERGE_TRANSITIONS_H_
