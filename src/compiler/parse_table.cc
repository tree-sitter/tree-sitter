#include "compiler/parse_table.h"
#include <string>
#include "compiler/precedence_range.h"

namespace tree_sitter {

using std::string;
using std::ostream;
using std::to_string;
using std::set;
using std::vector;
using std::function;
using rules::Symbol;

ParseAction::ParseAction(ParseActionType type, ParseStateId state_index,
                         Symbol symbol, size_t consumed_symbol_count,
                         PrecedenceRange precedence_range,
                         rules::Associativity associativity,
                         const Production *production)
    : type(type),
      extra(false),
      fragile(false),
      can_hide_split(false),
      symbol(symbol),
      state_index(state_index),
      consumed_symbol_count(consumed_symbol_count),
      precedence_range(precedence_range),
      associativity(associativity),
      production(production) {}

ParseAction::ParseAction()
    : type(ParseActionTypeError),
      extra(false),
      fragile(false),
      can_hide_split(false),
      symbol(Symbol(-1)),
      state_index(-1),
      consumed_symbol_count(0),
      associativity(rules::AssociativityNone),
      production(nullptr) {}

ParseAction ParseAction::Error() {
  return ParseAction();
}

ParseAction ParseAction::Accept() {
  ParseAction action;
  action.type = ParseActionTypeAccept;
  return action;
}

ParseAction ParseAction::Shift(ParseStateId state_index,
                               PrecedenceRange precedence_range) {
  return ParseAction(ParseActionTypeShift, state_index, Symbol(-1), 0,
                     precedence_range, rules::AssociativityNone, nullptr);
}

ParseAction ParseAction::ShiftExtra() {
  ParseAction action;
  action.type = ParseActionTypeShift;
  action.extra = true;
  return action;
}

ParseAction ParseAction::ReduceExtra(Symbol symbol) {
  ParseAction action;
  action.type = ParseActionTypeReduce;
  action.extra = true;
  action.symbol = symbol;
  action.consumed_symbol_count = 1;
  return action;
}

ParseAction ParseAction::Reduce(Symbol symbol, size_t consumed_symbol_count,
                                int precedence,
                                rules::Associativity associativity,
                                const Production &production) {
  return ParseAction(ParseActionTypeReduce, 0, symbol, consumed_symbol_count,
                     { precedence, precedence }, associativity, &production);
}

bool ParseAction::operator==(const ParseAction &other) const {
  return (type == other.type && extra == other.extra &&
          fragile == other.fragile && can_hide_split == other.can_hide_split &&
          symbol == other.symbol && state_index == other.state_index &&
          production == other.production &&
          consumed_symbol_count == other.consumed_symbol_count);
}

bool ParseAction::operator<(const ParseAction &other) const {
  if (type < other.type)
    return true;
  if (other.type < type)
    return false;
  if (extra && !other.extra)
    return true;
  if (other.extra && !extra)
    return false;
  if (fragile && !other.fragile)
    return true;
  if (other.fragile && !fragile)
    return false;
  if (can_hide_split && !other.can_hide_split)
    return true;
  if (other.can_hide_split && !can_hide_split)
    return false;
  if (symbol < other.symbol)
    return true;
  if (other.symbol < symbol)
    return false;
  if (state_index < other.state_index)
    return true;
  if (other.state_index < state_index)
    return false;
  if (production < other.production)
    return true;
  if (other.production < production)
    return false;
  return consumed_symbol_count < other.consumed_symbol_count;
}

ParseState::ParseState() : lex_state_id(-1) {}

set<Symbol> ParseState::expected_inputs() const {
  set<Symbol> result;
  for (auto &pair : actions)
    result.insert(pair.first);
  return result;
}

void ParseState::each_advance_action(function<void(ParseAction *)> fn) {
  for (auto &entry : actions)
    for (ParseAction &action : entry.second)
      if (action.type == ParseActionTypeShift)
        fn(&action);
}

bool ParseState::operator==(const ParseState &other) const {
  return actions == other.actions;
}

set<Symbol> ParseTable::all_symbols() const {
  set<Symbol> result;
  for (auto &pair : symbols)
    result.insert(pair.first);
  return result;
}

ParseStateId ParseTable::add_state() {
  states.push_back(ParseState());
  return states.size() - 1;
}

ParseAction &ParseTable::set_action(ParseStateId id, Symbol symbol,
                                    ParseAction action) {
  if (action.extra)
    symbols[symbol];
  else
    symbols[symbol].structural = true;
  states[id].actions[symbol] = vector<ParseAction>({ action });
  return *states[id].actions[symbol].begin();
}

ParseAction &ParseTable::add_action(ParseStateId id, Symbol symbol,
                                    ParseAction action) {
  if (action.extra)
    symbols[symbol];
  else
    symbols[symbol].structural = true;

  for (ParseAction &existing_action : states[id].actions[symbol])
    if (existing_action == action)
      return existing_action;

  states[id].actions[symbol].push_back(action);
  return *states[id].actions[symbol].rbegin();
}

}  // namespace tree_sitter
