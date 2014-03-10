#ifndef __tree_sitter__merge_transitions__
#define __tree_sitter__merge_transitions__

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
            for (auto &pair : right) {
                auto rule = pair.first;
                for (auto &existing_pair : left) {
                    auto existing_rule = existing_pair.first;
                    auto intersection = existing_rule.remove_set(rule);
                    if (!intersection.is_empty()) {
                        result.erase(existing_pair.first);
                        result.insert({ existing_rule, existing_pair.second });
                        rule.remove_set(intersection);
                        result.insert({ intersection, merge_fn(existing_pair.second, pair.second) });
                    }
                }
                result.insert({ rule, pair.second });
            }
            return result;
        }
    }
}

#endif
