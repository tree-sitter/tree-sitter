#ifndef COMPILER_BUILD_TABLES_ITEM_SET_TRANSITIONS_H_
#define COMPILER_BUILD_TABLES_ITEM_SET_TRANSITIONS_H_

#include <map>
#include "compiler/build_tables/lex_item.h"
#include "compiler/build_tables/parse_item.h"

namespace tree_sitter {

struct SyntaxGrammar;

namespace rules {
class CharacterSet;
class Symbol;
}

namespace build_tables {

std::map<rules::Symbol, ParseItemSet> sym_transitions(
  const ParseItemSet &item_set, const SyntaxGrammar &grammar);

std::map<rules::CharacterSet, LexItemSet> char_transitions(
  const LexItemSet &item_set);

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_ITEM_SET_TRANSITIONS_H_
