#ifndef COMPILER_BUILD_TABLES_PARSE_ITEM_SET_BUILDER_H_
#define COMPILER_BUILD_TABLES_PARSE_ITEM_SET_BUILDER_H_

#include "compiler/build_tables/parse_item.h"
#include "compiler/rule.h"
#include <map>

namespace tree_sitter {

struct SyntaxGrammar;
struct LexicalGrammar;

namespace build_tables {

class ParseItemSetBuilder {
  struct ParseItemSetComponent {
    ParseItem item;
    LookaheadSet lookaheads;
    bool propagates_lookaheads;
  };

  std::map<rules::Symbol, LookaheadSet> first_sets;
  std::map<rules::Symbol::Index, std::vector<ParseItemSetComponent>> component_cache;
  std::vector<std::pair<ParseItem, LookaheadSet>> item_set_buffer;

 public:
  ParseItemSetBuilder(const SyntaxGrammar &, const LexicalGrammar &);
  void apply_transitive_closure(ParseItemSet *);
  LookaheadSet get_first_set(const rules::Symbol &) const;
};

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_PARSE_ITEM_SET_BUILDER_H_
