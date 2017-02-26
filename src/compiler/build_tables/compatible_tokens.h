#ifndef COMPILER_BUILD_TABLES_COMPATIBLE_TOKENS_H_
#define COMPILER_BUILD_TABLES_COMPATIBLE_TOKENS_H_

#include "compiler/rule.h"
#include "compiler/rules/symbol.h"
#include <map>
#include <set>

namespace tree_sitter {

struct LexicalGrammar;

namespace build_tables {

struct CompatibleTokensResult {
  std::set<rules::Symbol> recovery_tokens;
  std::map<rules::Symbol, std::set<rules::Symbol>> unmergeable_pairs;
};

CompatibleTokensResult get_compatible_tokens(const LexicalGrammar &);

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_COMPATIBLE_TOKENS_H_
