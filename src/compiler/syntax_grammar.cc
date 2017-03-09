#include "compiler/syntax_grammar.h"
#include <vector>
#include <string>
#include <utility>
#include "compiler/rules/symbol.h"
#include "compiler/rules/built_in_symbols.h"

namespace tree_sitter {

bool ExternalToken::operator==(const ExternalToken &other) const {
  return name == other.name && type == other.type &&
    corresponding_internal_token == other.corresponding_internal_token;
}

bool ProductionStep::operator==(const ProductionStep &other) const {
  return symbol == other.symbol && precedence == other.precedence &&
         associativity == other.associativity;
}

}  // namespace tree_sitter
