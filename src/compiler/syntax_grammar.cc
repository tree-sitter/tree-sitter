#include "compiler/syntax_grammar.h"

namespace tree_sitter {

bool ProductionStep::operator==(const ProductionStep &other) const {
  return symbol == other.symbol &&
    precedence == other.precedence &&
    associativity == other.associativity &&
    alias == other.alias;
}

bool ProductionStep::operator!=(const ProductionStep &other) const {
  return !operator==(other);
}

bool ProductionStep::operator<(const ProductionStep &other) const {
 if (symbol < other.symbol) return true;
 if (other.symbol < symbol) return false;
 if (precedence < other.precedence) return true;
 if (other.precedence < precedence) return false;
 if (associativity < other.associativity) return true;
 if (other.associativity < associativity) return false;
 return alias < other.alias;
}

bool Production::operator==(const Production &other) const {
  return steps == other.steps && dynamic_precedence == other.dynamic_precedence;
}

bool ExternalToken::operator==(const ExternalToken &other) const {
  return name == other.name &&
    type == other.type &&
    corresponding_internal_token == other.corresponding_internal_token;
}

}  // namespace tree_sitter
