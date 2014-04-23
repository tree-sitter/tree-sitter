#ifndef COMPILER_BUILD_TABLES_MERGE_TRANSITIONS_H_
#define COMPILER_BUILD_TABLES_MERGE_TRANSITIONS_H_

#include <map>
#include "compiler/rules/character_set.h"
#include "compiler/rules/interned_symbol.h"

namespace tree_sitter {
    namespace build_tables {

        /*
         *  Merges two transition maps with symbol keys. If both maps
         *  contain values for the same symbol, the new value for that
         *  symbol will be computed by merging the two previous values
         *  using the given function.
         */
        template<typename T>
        std::map<rules::ISymbol, T>
        merge_sym_transitions(const std::map<rules::ISymbol, T> &left,
                              const std::map<rules::ISymbol, T> &right,
                              std::function<T(T, T)> merge_fn) {
            std::map<rules::ISymbol, T> result(left);
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
                rules::CharacterSet new_char_set = new_pair.first;
                T new_value = new_pair.second;

                std::map<rules::CharacterSet, T> pairs_to_insert;

                auto iter = result.begin();
                while (iter != result.end()) {
                    rules::CharacterSet char_set = iter->first;
                    T value = iter->second;

                    rules::CharacterSet intersection = char_set.remove_set(new_char_set);
                    if (!intersection.is_empty()) {
                        new_char_set.remove_set(intersection);
                        if (!char_set.is_empty())
                            pairs_to_insert.insert({ char_set, value });
                        pairs_to_insert.insert({ intersection, merge_fn(value, new_value) });
                        result.erase(iter++);
                    } else {
                        ++iter;
                    }
                }

                result.insert(pairs_to_insert.begin(), pairs_to_insert.end());

                if (!new_char_set.is_empty())
                    result.insert({ new_char_set, new_pair.second });
            }
            return result;
        }
    }
}

#endif  // COMPILER_BUILD_TABLES_MERGE_TRANSITIONS_H_
