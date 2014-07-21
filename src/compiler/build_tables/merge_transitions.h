#ifndef COMPILER_BUILD_TABLES_MERGE_TRANSITIONS_H_
#define COMPILER_BUILD_TABLES_MERGE_TRANSITIONS_H_

#include <map>
#include <utility>
#include "compiler/rules/character_set.h"
#include "compiler/rules/symbol.h"

namespace tree_sitter {
namespace build_tables {

/*
 *  Merges a new transition into a map with symbol keys.
 *  If the symbol already exists in the map, the new value for that
 *  symbol will be computed by merging the old and new values
 *  using the given function.
 */
template <typename T>
void merge_sym_transition(std::map<rules::Symbol, T> *left,
                          const std::pair<rules::Symbol, T> &new_pair,
                          std::function<void(T *, const T *)> merge_fn) {
  auto new_symbol = new_pair.first;
  for (auto &existing_pair : *left) {
    auto existing_symbol = existing_pair.first;
    if (new_symbol < existing_symbol)
      break;
    if (existing_symbol == new_symbol) {
      merge_fn(&existing_pair.second, &new_pair.second);
      return;
    }
  }
  left->insert(new_pair);
}

/*
 *  Merges two transition maps with character set keys. If the
 *  two maps contain values for overlapping character sets, the
 *  new value for the two sets' intersection will be computed by
 *  merging the old and new values using the given function.
 */
template <typename T>
void merge_char_transition(std::map<rules::CharacterSet, T> *left,
                           const std::pair<rules::CharacterSet, T> &new_pair,
                           std::function<void(T *, const T *)> merge_fn) {
  rules::CharacterSet new_char_set = new_pair.first;
  T new_value = new_pair.second;

  std::map<rules::CharacterSet, T> pairs_to_insert;

  auto iter = left->begin();
  while (iter != left->end()) {
    rules::CharacterSet char_set = iter->first;
    T value = iter->second;

    rules::CharacterSet intersection = char_set.remove_set(new_char_set);
    if (!intersection.is_empty()) {
      new_char_set.remove_set(intersection);
      if (!char_set.is_empty())
        pairs_to_insert.insert({ char_set, value });
      merge_fn(&value, &new_value);
      pairs_to_insert.insert({ intersection, value });
      left->erase(iter++);
    } else {
      ++iter;
    }
  }

  left->insert(pairs_to_insert.begin(), pairs_to_insert.end());

  if (!new_char_set.is_empty())
    left->insert({ new_char_set, new_pair.second });
}

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_MERGE_TRANSITIONS_H_
