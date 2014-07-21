#ifndef COMPILER_BUILD_TABLES_RULE_TRANSITIONS_H_
#define COMPILER_BUILD_TABLES_RULE_TRANSITIONS_H_

#include <map>
#include "compiler/rules/character_set.h"
#include "compiler/rules/symbol.h"

namespace tree_sitter {
namespace build_tables {

std::map<rules::CharacterSet, rules::rule_ptr> char_transitions(
    const rules::rule_ptr &rule);

std::map<rules::Symbol, rules::rule_ptr> sym_transitions(
    const rules::rule_ptr &rule);

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_RULE_TRANSITIONS_H_
