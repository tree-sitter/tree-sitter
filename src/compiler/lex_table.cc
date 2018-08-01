#include "compiler/lex_table.h"
#include "compiler/rule.h"

namespace tree_sitter {

using std::function;
using std::string;
using std::to_string;
using std::map;
using std::set;
using rules::Symbol;
using rules::CharacterSet;

AdvanceAction::AdvanceAction() : state_index(-1) {}

AdvanceAction::AdvanceAction(size_t state_index,
                             PrecedenceRange precedence_range,
                             bool in_main_token)
  : state_index(state_index),
    precedence_range(precedence_range),
    in_main_token(in_main_token) {}

bool AdvanceAction::operator==(const AdvanceAction &other) const {
  return (state_index == other.state_index) &&
         (precedence_range == other.precedence_range);
}

AcceptTokenAction::AcceptTokenAction()
  : symbol(rules::NONE()), precedence(0), implicit_precedence(0) {}

AcceptTokenAction::AcceptTokenAction(Symbol symbol, int precedence)
  : symbol(symbol), precedence(precedence), implicit_precedence(0) {}

bool AcceptTokenAction::is_present() const {
  return symbol != rules::NONE();
}

bool AcceptTokenAction::operator==(const AcceptTokenAction &other) const {
  return (
    symbol == other.symbol &&
    precedence == other.precedence &&
    implicit_precedence == other.implicit_precedence
  );
}

bool LexState::operator==(const LexState &other) const {
  return advance_actions == other.advance_actions &&
         accept_action == other.accept_action;
}

}  // namespace tree_sitter
