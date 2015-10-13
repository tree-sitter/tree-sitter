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

static const vector<Production> START_PRODUCTIONS_TOKEN_ONLY({
  Production({ ProductionStep(rules::Symbol(0, true), 0,
                              rules::AssociativityNone) }),
});

static const vector<Production> START_PRODUCTIONS({
  Production({ ProductionStep(rules::Symbol(0), 0, rules::AssociativityNone) }),
});

static const vector<Production> NO_PRODUCTIONS({});

SyntaxVariable::SyntaxVariable(const string &name, VariableType type,
                               const vector<Production> &productions)
    : name(name), productions(productions), type(type) {}

ProductionStep::ProductionStep(const rules::Symbol &symbol, int precedence,
                               rules::Associativity associativity)
    : symbol(symbol),
      precedence(precedence),
      associativity(associativity),
      rule_id(0) {}

ProductionStep::ProductionStep(const rules::Symbol &symbol, int precedence,
                               rules::Associativity associativity, int rule_id)
    : symbol(symbol),
      precedence(precedence),
      associativity(associativity),
      rule_id(rule_id) {}

bool ProductionStep::operator==(const ProductionStep &other) const {
  return symbol == other.symbol && precedence == other.precedence &&
         rule_id == other.rule_id && associativity == other.associativity;
}

const vector<Production> &SyntaxGrammar::productions(
  const rules::Symbol &symbol) const {
  if (symbol == rules::START()) {
    if (variables.empty())
      return START_PRODUCTIONS_TOKEN_ONLY;
    else
      return START_PRODUCTIONS;
  } else if (symbol.is_built_in() || symbol.is_token) {
    return NO_PRODUCTIONS;
  } else {
    return variables[symbol.index].productions;
  }
}

}  // namespace tree_sitter
