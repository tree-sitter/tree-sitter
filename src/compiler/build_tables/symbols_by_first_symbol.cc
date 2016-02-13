#include "compiler/build_tables/symbols_by_first_symbol.h"
#include "compiler/syntax_grammar.h"
#include "compiler/rules/symbol.h"

namespace tree_sitter {
namespace build_tables {

using std::map;
using std::set;
using rules::Symbol;

map<Symbol, set<Symbol>> symbols_by_first_symbol(const SyntaxGrammar &grammar) {
  map<Symbol, set<Symbol>> result;

  size_t variable_index = -1;
  for (const SyntaxVariable &variable : grammar.variables) {
    variable_index++;
    Symbol symbol(variable_index);
    result[symbol].insert(symbol);
    for (const Production &production : variable.productions)
      if (!production.empty()) {
        Symbol first_symbol = production[0].symbol;
        result[first_symbol].insert(symbol);
        result[first_symbol].insert(first_symbol);
      }
  }

  bool done = false;
  while (!done) {
    done = true;
    for (auto &entry : result) {
      set<Symbol> new_symbols;
      for (const Symbol &symbol : entry.second)
        for (const Symbol &other_symbol : result[symbol])
          new_symbols.insert(other_symbol);

      for (const Symbol &new_symbol : new_symbols)
        if (entry.second.insert(new_symbol).second)
          done = false;
    }
  }

  for (auto iter = result.begin(), end = result.end(); iter != end;) {
    if (!iter->first.is_token) {
      result.erase(iter++);
    } else {
      iter++;
    }
  }

  return result;
}

}  // namespace build_tables
}  // namespace tree_sitter
