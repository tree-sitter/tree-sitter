#include "compiler/syntax_grammar.h"
#include <vector>
#include <string>
#include <utility>
#include "compiler/rules/symbol.h"
#include "compiler/rules/built_in_symbols.h"

namespace tree_sitter {

using std::string;
using std::to_string;
using std::pair;
using std::vector;
using std::set;

static const vector<Production> NO_PRODUCTIONS;

SyntaxVariable::SyntaxVariable(const string &name, VariableType type,
                               const vector<Production> &productions)
    : internal_name(name),
      external_name(name),
      productions(productions),
      type(type) {}

SyntaxVariable::SyntaxVariable(const string &internal_name,
                               const string &external_name, VariableType type,
                               const vector<Production> &productions)
    : internal_name(internal_name),
      external_name(external_name),
      productions(productions),
      type(type) {}

ProductionStep::ProductionStep(const rules::Symbol &symbol, int precedence,
                               rules::Associativity associativity)
    : symbol(symbol), precedence(precedence), associativity(associativity) {}

bool ProductionStep::operator==(const ProductionStep &other) const {
  return symbol == other.symbol && precedence == other.precedence &&
         associativity == other.associativity;
}

const vector<Production> &SyntaxGrammar::productions(
  const rules::Symbol &symbol) const {
  if (symbol.is_built_in() || symbol.is_token) {
    return NO_PRODUCTIONS;
  } else {
    return variables[symbol.index].productions;
  }
}

}  // namespace tree_sitter
