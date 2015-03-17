#include "compiler/build_tables/parse_conflict_manager.h"
#include "compiler/parse_table.h"
#include "compiler/rules/built_in_symbols.h"
#include <utility>
#include <algorithm>

namespace tree_sitter {
namespace build_tables {

using std::find;
using std::get;
using std::make_tuple;
using std::string;
using std::tuple;
using std::vector;

ParseConflictManager::ParseConflictManager(const SyntaxGrammar &syntax_grammar,
                                 const LexicalGrammar &lexical_grammar) :
  syntax_grammar(syntax_grammar),
  lexical_grammar(lexical_grammar) {}

tuple<bool, ConflictType, string>
ParseConflictManager::resolve(const ParseAction &new_action,
                         const ParseAction &old_action,
                         const rules::Symbol &symbol) const {
  if (new_action.type < old_action.type) {
    auto opposite = resolve(old_action, new_action, symbol);
    return make_tuple(!get<0>(opposite), get<1>(opposite), get<2>(opposite));
  }

  switch (old_action.type) {
    case ParseActionTypeError:
      return make_tuple(true, ConflictTypeNone, "");

    case ParseActionTypeShift:
      if (new_action.type == ParseActionTypeReduce) {
        int min_precedence = *old_action.precedence_values.begin();
        int max_precedence = *old_action.precedence_values.rbegin();
        int new_precedence = *new_action.precedence_values.rbegin();
        if (new_precedence < min_precedence)
          return make_tuple(false, ConflictTypeResolved, "");
        else if (new_precedence > max_precedence)
          return make_tuple(true, ConflictTypeResolved, "");
        else {

          // TODO: Add associativity annotations. In the event of a precedence
          // tie, return ConflictTypeError unless there is an associativity
          // annotation to break the tie.
          return make_tuple(false, ConflictTypeResolved, "");
        }
      }
      break;

    case ParseActionTypeReduce:
      if (new_action.type == ParseActionTypeReduce) {
        int old_precedence = *old_action.precedence_values.begin();
        int new_precedence = *new_action.precedence_values.begin();
        if (new_precedence > old_precedence) {
          return make_tuple(true, ConflictTypeResolved, "");
        } else if (new_precedence < old_precedence) {
          return make_tuple(false, ConflictTypeResolved, "");
        } else {
          string message =
            "Lookahead: " + symbol_name(symbol) + "\n" +
            "Possible Actions:\n"
            "* " + action_description(old_action) + "\n" +
            "* " + action_description(new_action) + "\n";
          return make_tuple(false, ConflictTypeError, message);
        }
      }

    default:
      break;
  }

  return make_tuple(false, ConflictTypeNone, "");
}

size_t ParseConflictManager::get_production_id(const vector<rules::Symbol> &symbols) {
  auto begin = productions.begin();
  auto end = productions.end();
  auto iter = find(begin, end, symbols);
  if (iter == end) {
    productions.push_back(symbols);
    return productions.size() - 1;
  }
  return iter - begin;
}

string ParseConflictManager::symbol_name(const rules::Symbol &symbol) const {
  if (symbol.is_built_in()) {
    if (symbol == rules::ERROR())
      return "ERROR";
    else if (symbol == rules::END_OF_INPUT())
      return "END_OF_INPUT";
    else
      return "";
  } else if (symbol.is_token())
    return lexical_grammar.rule_name(symbol);
  else
    return syntax_grammar.rule_name(symbol);
}

string ParseConflictManager::action_description(const ParseAction &action) const {
  string result = "Reduce";
  for (const rules::Symbol &symbol : productions[action.production_id])
    result += " " + symbol_name(symbol);
  result += " -> " + symbol_name(action.symbol);
  return result;
}

}  // namespace build_tables
}  // namespace tree_sitter
