#ifndef COMPILER_BUILD_TABLES_LEX_ITEM_TRANSITIONS_H_
#define COMPILER_BUILD_TABLES_LEX_ITEM_TRANSITIONS_H_

#include "compiler/build_tables/lex_item.h"

namespace tree_sitter {
namespace build_tables {

void lex_item_transitions(LexItemSet::TransitionMap *transitions, const LexItem &);

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_LEX_ITEM_TRANSITIONS_H_
