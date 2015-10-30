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

  bool operator==(const ParseItem &other) const;
  bool operator<(const ParseItem &other) const;
  rules::Symbol lhs() const;
  std::pair<int, int> remaining_rule_id() const;
  bool is_done() const;
  int precedence() const;
  rules::Associativity associativity() const;

  int variable_index;
  const Production *production;
  unsigned int step_index;

  struct Hash {
    size_t operator()(const ParseItem &) const;
  };
};

class ParseItemSet {
 public:
  ParseItemSet();
  explicit ParseItemSet(const std::map<ParseItem, LookaheadSet> &);

  typedef std::map<rules::Symbol, std::pair<ParseItemSet, PrecedenceRange>> TransitionMap;

  TransitionMap transitions() const;
  bool operator==(const ParseItemSet &) const;

  std::map<ParseItem, LookaheadSet> entries;

  struct Hash {
    size_t operator()(const ParseItemSet &) const;
  };
};

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_PARSE_ITEM_H_
