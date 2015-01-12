#ifndef COMPILER_BUILD_TABLES_PARSE_ITEM_H_
#define COMPILER_BUILD_TABLES_PARSE_ITEM_H_

#include <set>
#include <unordered_map>
#include "compiler/build_tables/item.h"
#include "compiler/rules/symbol.h"

namespace tree_sitter {
namespace build_tables {

class ParseItem {
 public:
  ParseItem(const rules::Symbol &lhs, size_t production_index,
            int rule_id, size_t consumed_symbol_count);
  bool operator==(const ParseItem &other) const;

  rules::Symbol lhs;
  size_t production_index;
  int rule_id;
  size_t consumed_symbol_count;
};

std::ostream &operator<<(std::ostream &stream, const ParseItem &item);

typedef std::unordered_map<ParseItem, std::set<rules::Symbol>> ParseItemSet;

}  // namespace build_tables
}  // namespace tree_sitter

namespace std {

template <>
struct hash<tree_sitter::build_tables::ParseItem> {
  size_t operator()(const tree_sitter::build_tables::ParseItem &item) const {
    return hash<tree_sitter::rules::Symbol>()(item.lhs) ^
      hash<int>()(item.rule_id) ^
      hash<size_t>()(item.consumed_symbol_count);
  }
};

template <>
struct hash<const tree_sitter::build_tables::ParseItemSet> {
  size_t operator()(const tree_sitter::build_tables::ParseItemSet &set) const {
    size_t result = hash<size_t>()(set.size());
    for (auto &pair : set) {
      result ^= hash<tree_sitter::build_tables::ParseItem>()(pair.first);
      result ^= hash<size_t>()(pair.second.size());
      for (auto &symbol : pair.second)
        result ^= hash<tree_sitter::rules::Symbol>()(symbol);
    }
    return result;
  }
};

}  // namespace std

#endif  // COMPILER_BUILD_TABLES_PARSE_ITEM_H_
