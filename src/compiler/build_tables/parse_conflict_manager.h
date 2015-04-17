#ifndef COMPILER_BUILD_TABLES_PARSE_CONFLICT_MANAGER_H_
#define COMPILER_BUILD_TABLES_PARSE_CONFLICT_MANAGER_H_

#include <utility>
#include "tree_sitter/compiler.h"
#include "compiler/syntax_grammar.h"
#include "compiler/lexical_grammar.h"
#include "compiler/build_tables/parse_item.h"

namespace tree_sitter {

class ParseAction;
namespace rules { class Symbol; }

namespace build_tables {

enum ConflictType {
  ConflictTypeNone,
  ConflictTypeResolved,
  ConflictTypeError
};

class ParseConflictManager {
  const SyntaxGrammar syntax_grammar;
  const LexicalGrammar lexical_grammar;
  std::vector<std::vector<rules::Symbol>> productions;

 public:
  ParseConflictManager(const SyntaxGrammar &, const LexicalGrammar &);
  size_t get_production_id(const std::vector<rules::Symbol> &);
  std::tuple<bool, ConflictType, std::string> resolve(
    const ParseAction &, const ParseAction &, const rules::Symbol &, const ParseItemSet &) const;

 private:
  std::string symbol_name(const rules::Symbol &) const;
  std::string item_set_description(const ParseItemSet &) const;
  std::string action_description(const ParseAction &) const;
  std::string conflict_description(const ParseAction &, const ParseAction &, const rules::Symbol &, const ParseItemSet &) const;
};

}  // namespace build_tables
}  // namespace tree_sitter

#endif  // COMPILER_BUILD_TABLES_PARSE_CONFLICT_MANAGER_H_
