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

SyntaxVariable::SyntaxVariable(const string &name, VariableType type,
                               const vector<Production> &productions)
    : name(name), productions(productions), type(type) {}

ProductionStep::ProductionStep(const rules::Symbol &symbol, int precedence,
                               rules::Associativity associativity)
    : symbol(symbol), precedence(precedence), associativity(associativity) {}

bool ExternalToken::operator==(const ExternalToken &other) const {
  return name == other.name && type == other.type &&
    corresponding_internal_token == other.corresponding_internal_token;
}

bool ProductionStep::operator==(const ProductionStep &other) const {
  return symbol == other.symbol && precedence == other.precedence &&
         associativity == other.associativity;
}

}  // namespace tree_sitter
