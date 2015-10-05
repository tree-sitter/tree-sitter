#ifndef COMPILER_BUILD_TABLES_LEX_ITEM_H_
#define COMPILER_BUILD_TABLES_LEX_ITEM_H_

#include <unordered_set>
#include <map>
#include <string>
#include "compiler/rules/character_set.h"
#include "compiler/rules/symbol.h"

namespace tree_sitter {
namespace build_tables {

class LexItem {
 public:
  LexItem(const rules::Symbol &lhs, rule_ptr rule);
  bool operator==(const LexItem &other) const;
  bool is_token_start() const;

  rules::Symbol lhs;
  rule_ptr rule;

  struct Hash {
    size_t operator()(const LexItem &) const;
  };
};

typedef std::unordered_set<LexItem, LexItem::Hash> LexItemSet;

struct LexItemSetHash {
  size_t operator()(const LexItemSet &) const;
};

std::map<rules::CharacterSet, LexItemSet> lex_item_set_transitions(
  const LexItemSet &);

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_LEX_ITEM_H_
