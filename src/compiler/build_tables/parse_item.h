#ifndef COMPILER_BUILD_TABLES_PARSE_ITEM_H_
#define COMPILER_BUILD_TABLES_PARSE_ITEM_H_

#include <map>
#include <utility>
#include "compiler/build_tables/lookahead_set.h"
#include "compiler/rule.h"
#include "compiler/syntax_grammar.h"
#include "compiler/precedence_range.h"

namespace tree_sitter {
namespace build_tables {

struct ParseItem {
  ParseItem();
  ParseItem(const rules::Symbol &, const Production &, unsigned int);

  struct CompletionStatus {
    bool is_done;
    int precedence;
    rules::Associativity associativity;
  };

  bool operator==(const ParseItem &other) const;
  bool operator<(const ParseItem &other) const;
  rules::Symbol lhs() const;
  rules::Symbol next_symbol() const;
  int precedence() const;
  int dynamic_precedence() const;
  rules::Associativity associativity() const;
  bool is_done() const;

  int variable_index;
  const Production *production;
  unsigned int step_index;
};

struct ParseItemSet {
  bool operator==(const ParseItemSet &) const;
  void add(const ParseItemSet &);
  size_t unfinished_item_signature() const;

  std::map<ParseItem, LookaheadSet> entries;
};

}  // namespace build_tables
}  // namespace tree_sitter

namespace std {

using tree_sitter::build_tables::ParseItemSet;

template <>
struct hash<tree_sitter::build_tables::ParseItemSet> {
  size_t operator()(const ParseItemSet &item_set) const;
};

}  // namespace std

#endif  // COMPILER_BUILD_TABLES_PARSE_ITEM_H_
