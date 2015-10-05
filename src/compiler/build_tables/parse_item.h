#ifndef COMPILER_BUILD_TABLES_PARSE_ITEM_H_
#define COMPILER_BUILD_TABLES_PARSE_ITEM_H_

#include <map>
#include "compiler/build_tables/lookahead_set.h"
#include "compiler/rules/symbol.h"
#include "compiler/syntax_grammar.h"

namespace tree_sitter {
namespace build_tables {

class ParseItem {
 public:
  ParseItem(const rules::Symbol &, unsigned int, unsigned int, int);

  bool operator==(const ParseItem &other) const;
  bool operator<(const ParseItem &other) const;
  rules::Symbol lhs() const;

  int variable_index;
  unsigned int production_index;
  unsigned int step_index;
  int rule_id;
};

typedef std::map<ParseItem, LookaheadSet> ParseItemSet;

struct ParseItemSetHash {
  size_t operator()(const ParseItemSet &) const;
};

std::map<rules::Symbol, ParseItemSet> parse_item_set_transitions(
  const ParseItemSet &, const SyntaxGrammar &);

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_PARSE_ITEM_H_
