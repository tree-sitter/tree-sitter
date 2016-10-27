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

ParseAction ParseAction::Recover(ParseStateId state_index) {
  return ParseAction(ParseActionTypeRecover, state_index, Symbol(-1), 0,
                     PrecedenceRange(), rules::AssociativityNone, nullptr);
}

ParseAction ParseAction::ShiftExtra() {
  ParseAction action;
  action.type = ParseActionTypeShift;
  action.extra = true;
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
          fragile == other.fragile && symbol == other.symbol &&
          state_index == other.state_index && production == other.production &&
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

ParseTableEntry::ParseTableEntry()
    : reusable(true), depends_on_lookahead(false) {}

ParseTableEntry::ParseTableEntry(const vector<ParseAction> &actions,
                                 bool reusable, bool depends_on_lookahead)
    : actions(actions),
      reusable(reusable),
      depends_on_lookahead(depends_on_lookahead) {}

bool ParseTableEntry::operator==(const ParseTableEntry &other) const {
  return actions == other.actions && reusable == other.reusable &&
         depends_on_lookahead == other.depends_on_lookahead;
}

ParseState::ParseState() : lex_state_id(-1) {}

bool ParseState::has_shift_action() const {
  for (const auto &pair : entries)
    if (pair.second.actions.size() > 0 &&
        pair.second.actions.back().type == ParseActionTypeShift)
      return true;
  return false;
}

set<Symbol> ParseState::expected_inputs() const {
  set<Symbol> result;
  for (auto &entry : entries)
    result.insert(entry.first);
  return result;
}

void ParseState::each_advance_action(function<void(ParseAction *)> fn) {
  for (auto &entry : entries)
    for (ParseAction &action : entry.second.actions)
      if (action.type == ParseActionTypeShift || ParseActionTypeRecover)
        fn(&action);
}

bool ParseState::operator==(const ParseState &other) const {
  return entries == other.entries;
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
  if (action.type == ParseActionTypeShift && action.extra)
    symbols[symbol].extra = true;
  else
    symbols[symbol].structural = true;

  states[id].entries[symbol].actions = { action };
  return *states[id].entries[symbol].actions.begin();
}

ParseAction &ParseTable::add_action(ParseStateId id, Symbol symbol,
                                    ParseAction action) {
  if (action.type == ParseActionTypeShift && action.extra)
    symbols[symbol].extra = true;
  else
    symbols[symbol].structural = true;

  ParseState &state = states[id];
  for (ParseAction &existing_action : state.entries[symbol].actions)
    if (existing_action == action)
      return existing_action;

  state.entries[symbol].actions.push_back(action);
  return *state.entries[symbol].actions.rbegin();
}

static bool has_entry(const ParseState &state, const ParseTableEntry &entry) {
  for (const auto &pair : state.entries)
    if (pair.second == entry)
      return true;
  return false;
}

bool ParseTable::merge_state(size_t i, size_t j) {
  ParseState &state = states[i];
  ParseState &other = states[j];

  for (auto &entry : state.entries) {
    const Symbol &symbol = entry.first;
    const vector<ParseAction> &actions = entry.second.actions;

    const auto &other_entry = other.entries.find(symbol);
    if (other_entry == other.entries.end()) {
      if (mergeable_symbols.count(symbol) == 0 && !symbol.is_built_in() && symbol.is_token)
        return false;
      if (actions.back().type != ParseActionTypeReduce)
        return false;
      if (!has_entry(other, entry.second))
        return false;
    } else if (entry.second != other_entry->second) {
      return false;
    }
  }

  set<Symbol> symbols_to_merge;

  for (auto &entry : other.entries) {
    const Symbol &symbol = entry.first;
    const vector<ParseAction> &actions = entry.second.actions;

    if (!state.entries.count(symbol)) {
      if (mergeable_symbols.count(symbol) == 0 && !symbol.is_built_in() && symbol.is_token)
        return false;
      if (actions.back().type != ParseActionTypeReduce)
        return false;
      if (!has_entry(state, entry.second))
        return false;
      symbols_to_merge.insert(symbol);
    }
  }

  for (const Symbol &symbol : symbols_to_merge)
    state.entries[symbol] = other.entries.find(symbol)->second;

  return true;
}

}  // namespace tree_sitter
