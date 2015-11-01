#include "compiler/lex_table.h"
#include "compiler/rules/symbol.h"

namespace tree_sitter {

using std::string;
using std::to_string;
using std::map;
using std::set;
using rules::Symbol;
using rules::CharacterSet;

LexAction::LexAction()
    : type(LexActionTypeError),
      symbol(Symbol(-1)),
      state_index(-1),
      precedence_range({ 0, 0 }) {}

LexAction::LexAction(LexActionType type, size_t state_index, Symbol symbol,
                     PrecedenceRange precedence_range, bool is_string)
    : type(type),
      symbol(symbol),
      state_index(state_index),
      precedence_range(precedence_range),
      is_string(is_string) {}

LexAction LexAction::Error() {
  return LexAction(LexActionTypeError, -1, Symbol(-1), { 0, 0 }, false);
}

LexAction LexAction::Advance(size_t state_index,
                             PrecedenceRange precedence_range) {
  return LexAction(LexActionTypeAdvance, state_index, Symbol(-1),
                   precedence_range, false);
}

LexAction LexAction::Accept(Symbol symbol, int precedence, bool is_string) {
  return LexAction(LexActionTypeAccept, -1, symbol, { precedence, precedence }, is_string);
}

bool LexAction::operator==(const LexAction &other) const {
  return (type == other.type) && (state_index == other.state_index) &&
         (symbol == other.symbol);
}

LexState::LexState() : is_token_start(false) {}

set<CharacterSet> LexState::expected_inputs() const {
  set<CharacterSet> result;
  for (auto &pair : actions)
    result.insert(pair.first);
  return result;
}

LexStateId LexTable::add_state() {
  states.push_back(LexState());
  return states.size() - 1;
}

LexState &LexTable::state(LexStateId id) {
  if (id < 0)
    return error_state;
  else
    return states[id];
}

const LexStateId LexTable::ERROR_STATE_ID = -1;

}  // namespace tree_sitter
