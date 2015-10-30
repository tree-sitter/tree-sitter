#ifndef COMPILER_BUILD_TABLES_LEX_ITEM_H_
#define COMPILER_BUILD_TABLES_LEX_ITEM_H_

#include <unordered_set>
#include <map>
#include <utility>
#include <string>
#include "compiler/rules/character_set.h"
#include "compiler/rules/symbol.h"
#include "compiler/precedence_range.h"

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

class LexItemSet {
 public:
  LexItemSet();
  explicit LexItemSet(const std::unordered_set<LexItem, LexItem::Hash> &);

  typedef std::map<rules::CharacterSet, std::pair<LexItemSet, PrecedenceRange>>
    TransitionMap;

  bool operator==(const LexItemSet &) const;
  TransitionMap transitions() const;

  std::unordered_set<LexItem, LexItem::Hash> entries;

  struct Hash {
    size_t operator()(const LexItemSet &) const;
  };
};

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_LEX_ITEM_H_
