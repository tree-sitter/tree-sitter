#ifndef COMPILER_BUILD_TABLES_RULE_TRANSITIONS_H_
#define COMPILER_BUILD_TABLES_RULE_TRANSITIONS_H_

#include <map>
#include <set>
#include "compiler/rules/character_set.h"
#include "compiler/rules/symbol.h"
#include "compiler/build_tables/lex_item.h"

namespace tree_sitter {
namespace build_tables {

void lex_item_transitions(std::map<rules::CharacterSet, LexItemSet> *transitions,
                          const LexItem &);

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_RULE_TRANSITIONS_H_
