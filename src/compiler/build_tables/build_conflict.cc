#include "compiler/build_tables/build_conflict.h"
#include "compiler/rules/symbol.h"
#include "compiler/rules/built_in_symbols.h"
#include "compiler/lexical_grammar.h"
#include "compiler/syntax_grammar.h"
#include "compiler/build_tables/parse_item.h"
#include <algorithm>
#include <string>
#include <vector>

namespace tree_sitter {
namespace build_tables {

using std::sort;
using std::string;
using std::vector;
using rules::Symbol;

static string symbol_name(const Symbol &symbol, const SyntaxGrammar &grammar,
                          const LexicalGrammar &lex_grammar) {
  if (symbol.is_built_in()) {
    if (symbol == rules::ERROR())
      return "ERROR";
    else if (symbol == rules::END_OF_INPUT())
      return "END_OF_INPUT";
    else
      return "";
  }

  if (symbol.is_token())
    return lex_grammar.rule_name(symbol);
  else
    return grammar.rule_name(symbol);
}

static string action_description(const ParseAction &action,
                                 const ParseItemSet &item_set,
                                 const SyntaxGrammar &grammar,
                                 const LexicalGrammar &lex_grammar) {
  switch (action.type) {
    case ParseActionTypeShift: {
      string result("shift (");
      vector<string> symbol_names;
      for (const auto &item : item_set)
        if (!item.first.consumed_symbols.empty())
          symbol_names.push_back(symbol_name(item.first.lhs, grammar, lex_grammar));
      sort(symbol_names.begin(), symbol_names.end());
      for (string symbol_name : symbol_names)
        result += " " + symbol_name;
      return result + " )";
    }
    case ParseActionTypeReduce:
      return "reduce ( " + symbol_name(action.symbol, grammar, lex_grammar) +
             " )";
    default:
      return "";
  }
}

Conflict build_conflict(const ParseAction &left, const ParseAction &right,
                        const ParseItemSet &item_set, const Symbol &sym,
                        const SyntaxGrammar &grammar,
                        const LexicalGrammar &lex_grammar) {
  if (right < left)
    return build_conflict(right, left, item_set, sym, grammar, lex_grammar);

  return Conflict(symbol_name(sym, grammar, lex_grammar) + ": " +
                  action_description(left, item_set, grammar, lex_grammar) +
                  " / " +
                  action_description(right, item_set, grammar, lex_grammar));
}

}  // namespace build_tables
}  // namespace tree_sitter
