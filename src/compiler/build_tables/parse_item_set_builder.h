#ifndef COMPILER_BUILD_TABLES_PARSE_ITEM_SET_BUILDER_H_
#define COMPILER_BUILD_TABLES_PARSE_ITEM_SET_BUILDER_H_

#include "compiler/build_tables/parse_item.h"
#include "compiler/rules/symbol.h"
#include <map>

namespace tree_sitter {

struct SyntaxGrammar;
struct LexicalGrammar;

namespace build_tables {

class ParseItemSetBuilder {
  const SyntaxGrammar *grammar;
  std::map<rules::Symbol, LookaheadSet> first_sets;
  std::vector<std::tuple<ParseItem, LookaheadSet, bool>> items_to_process;

 public:
  ParseItemSetBuilder(const SyntaxGrammar &, const LexicalGrammar &);
  void apply_transitive_closure(ParseItemSet *);
  LookaheadSet get_first_set(rules::Symbol &) const;
};

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_PARSE_ITEM_SET_BUILDER_H_
