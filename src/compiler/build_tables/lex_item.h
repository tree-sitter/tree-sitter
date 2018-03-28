#ifndef COMPILER_BUILD_TABLES_LEX_ITEM_H_
#define COMPILER_BUILD_TABLES_LEX_ITEM_H_

#include <unordered_set>
#include <map>
#include <utility>
#include <string>
#include "compiler/rule.h"
#include "compiler/precedence_range.h"

namespace tree_sitter {
namespace build_tables {

class LexItem {
 public:
  LexItem(const rules::Symbol &, const rules::Rule &);

  struct CompletionStatus {
    bool is_done;
    PrecedenceRange precedence;
  };

  bool operator==(const LexItem &other) const;
  CompletionStatus completion_status() const;
  bool is_in_separators() const;

  rules::Symbol lhs;
  rules::Rule rule;
};

}  // namespace build_tables
}  // namespace tree_sitter

namespace std {

template <>
struct hash<tree_sitter::build_tables::LexItem> {
  size_t operator()(const tree_sitter::build_tables::LexItem &) const;
};

}  // namespace std

namespace tree_sitter {
namespace build_tables {

class LexItemSet {
 public:
  LexItemSet();
  explicit LexItemSet(const std::unordered_set<LexItem> &);

  struct Transition;
  typedef std::map<rules::CharacterSet, Transition> TransitionMap;

  bool operator==(const LexItemSet &) const;
  TransitionMap transitions() const;
  bool has_items_in_separators() const;

  std::unordered_set<LexItem> entries;
};

struct LexItemSet::Transition {
  LexItemSet destination;
  PrecedenceRange precedence;
  bool in_main_token;

  bool operator==(const LexItemSet::Transition &) const;
};

}  // namespace build_tables
}  // namespace tree_sitter

namespace std {

template <>
struct hash<tree_sitter::build_tables::LexItemSet> {
  size_t operator()(const tree_sitter::build_tables::LexItemSet &) const;
};

}  // namespace std

#endif  // COMPILER_BUILD_TABLES_LEX_ITEM_H_
