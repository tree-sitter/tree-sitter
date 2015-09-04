#ifndef COMPILER_BUILD_TABLES_LEX_ITEM_H_
#define COMPILER_BUILD_TABLES_LEX_ITEM_H_

#include <unordered_set>
#include <string>
#include "compiler/build_tables/item.h"

namespace tree_sitter {
namespace build_tables {

class LexItem : public Item {
 public:
  LexItem(const rules::Symbol &lhs, rule_ptr rule);
  bool operator==(const LexItem &other) const;
  bool is_token_start() const;
};

std::ostream &operator<<(std::ostream &stream, const LexItem &item);

typedef std::unordered_set<LexItem> LexItemSet;

}  // namespace build_tables
}  // namespace tree_sitter

namespace std {

template <>
struct hash<tree_sitter::build_tables::LexItem> {
  size_t operator()(const tree_sitter::build_tables::Item &item) const {
    return hash<tree_sitter::rules::Symbol>()(item.lhs) ^
           hash<tree_sitter::rule_ptr>()(item.rule);
  }
};

template <>
struct hash<const tree_sitter::build_tables::LexItemSet> {
  size_t operator()(const tree_sitter::build_tables::LexItemSet &set) const {
    size_t result = hash<size_t>()(set.size());
    for (auto item : set)
      result ^= hash<tree_sitter::build_tables::LexItem>()(item);
    return result;
  }
};

}  // namespace std

#endif  // COMPILER_BUILD_TABLES_LEX_ITEM_H_
