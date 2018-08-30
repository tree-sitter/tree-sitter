#include "compiler/prepare_grammar/extract_simple_aliases.h"
#include "compiler/lexical_grammar.h"
#include "compiler/syntax_grammar.h"
#include <unordered_map>
#include <vector>

namespace tree_sitter {
namespace prepare_grammar {

using std::pair;
using std::vector;
using std::unordered_map;
using rules::Alias;
using rules::Symbol;

template <typename T>
static void apply_alias(T *variable, Alias alias) {
  if (!alias.value.empty()) {
    variable->name = alias.value;
    variable->type = alias.is_named ? VariableTypeNamed : VariableTypeAnonymous;
  }
}

std::unordered_map<rules::Symbol, rules::Alias>
extract_simple_aliases(SyntaxGrammar *syntax_grammar, LexicalGrammar *lexical_grammar) {
  struct SymbolStatus {
    Alias alias;
    bool eligible = true;
  };

  vector<SymbolStatus> terminal_status_list(lexical_grammar->variables.size());
  vector<SymbolStatus> non_terminal_status_list(syntax_grammar->variables.size());
  vector<SymbolStatus> external_status_list(syntax_grammar->external_tokens.size());

  for (const SyntaxVariable &variable : syntax_grammar->variables) {
    for (const Production &production : variable.productions) {
      for (const ProductionStep &step : production.steps) {
        SymbolStatus *status;
        if (step.symbol.is_built_in())  {
          continue;
        } else if (step.symbol.is_external()) {
          status = &external_status_list[step.symbol.index];
        } else if (step.symbol.is_terminal()) {
          status = &terminal_status_list[step.symbol.index];
        } else {
          status = &non_terminal_status_list[step.symbol.index];
        }

        if (step.alias.value.empty()) {
          status->alias = Alias();
          status->eligible = false;
        }

        if (status->eligible) {
          if (status->alias.value.empty()) {
            status->alias = step.alias;
          } else if (status->alias != step.alias) {
            status->alias = Alias();
            status->eligible = false;
          }
        }
      }
    }
  }

  for (SyntaxVariable &variable : syntax_grammar->variables) {
    for (Production &production : variable.productions) {
      for (ProductionStep &step : production.steps) {
        SymbolStatus *status;
        if (step.symbol.is_built_in())  {
          continue;
        } else if (step.symbol.is_external()) {
          status = &external_status_list[step.symbol.index];
        } else if (step.symbol.is_terminal()) {
          status = &terminal_status_list[step.symbol.index];
        } else {
          status = &non_terminal_status_list[step.symbol.index];
        }

        if (!status->alias.value.empty()) {
          step.alias = Alias();
        }
      }
    }
  }

  unordered_map<Symbol, Alias> result;

  for (unsigned i = 0, n = terminal_status_list.size(); i < n; i++) {
    if (!terminal_status_list[i].alias.value.empty()) {
      result[Symbol::terminal(i)] = terminal_status_list[i].alias;
    }
  }

  for (unsigned i = 0, n = non_terminal_status_list.size(); i < n; i++) {
    if (!non_terminal_status_list[i].alias.value.empty()) {
      result[Symbol::non_terminal(i)] = non_terminal_status_list[i].alias;
    }
  }

  for (unsigned i = 0, n = external_status_list.size(); i < n; i++) {
    if (!external_status_list[i].alias.value.empty()) {
      result[Symbol::external(i)] = external_status_list[i].alias;
    }
  }

  return result;
}

}  // namespace prepare_grammar
}  // namespace tree_sitter
