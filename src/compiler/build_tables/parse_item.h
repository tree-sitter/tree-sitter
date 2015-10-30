#ifndef COMPILER_BUILD_TABLES_PARSE_ITEM_H_
#define COMPILER_BUILD_TABLES_PARSE_ITEM_H_

#include <map>
#include <utility>
#include "compiler/build_tables/lookahead_set.h"
#include "compiler/rules/symbol.h"
#include "compiler/rules/metadata.h"
#include "compiler/syntax_grammar.h"
#include "compiler/precedence_range.h"

namespace tree_sitter {
namespace build_tables {

class ParseItem {
 public:
  ParseItem(const rules::Symbol &, const Production &, unsigned int);

  struct CompletionStatus {
    bool is_done;
    int precedence;
    rules::Associativity associativity;
  };

  struct Hash {
    size_t operator()(const ParseItem &) const;
  };

  bool operator==(const ParseItem &other) const;
  bool operator<(const ParseItem &other) const;
  rules::Symbol lhs() const;
  std::pair<int, int> remaining_rule_id() const;
  int precedence() const;
  rules::Associativity associativity() const;
  CompletionStatus completion_status() const;

  int variable_index;
  const Production *production;
  unsigned int step_index;

};

class ParseItemSet {
 public:
  ParseItemSet();
  explicit ParseItemSet(const std::map<ParseItem, LookaheadSet> &);

  typedef std::map<rules::Symbol, std::pair<ParseItemSet, PrecedenceRange>>
    TransitionMap;

  struct Hash {
    size_t operator()(const ParseItemSet &) const;
  };

  TransitionMap transitions() const;
  bool operator==(const ParseItemSet &) const;

  std::map<ParseItem, LookaheadSet> entries;
};

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_PARSE_ITEM_H_
