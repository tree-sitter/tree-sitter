#include "compiler/parse_table.h"
#include <string>
#include "compiler/precedence_range.h"
#include "compiler/rule.h"

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
                         const Production *production)
    : type(type),
      extra(false),
      fragile(false),
      state_index(state_index),
      symbol(symbol),
      consumed_symbol_count(consumed_symbol_count),
      production(production) {}

ParseAction::ParseAction()
    : type(ParseActionTypeError),
      extra(false),
      fragile(false),
      state_index(-1),
      symbol(rules::NONE()),
      consumed_symbol_count(0),
      production(nullptr) {}

ParseAction ParseAction::Error() {
  return ParseAction();
}

ParseAction ParseAction::Accept() {
  ParseAction action;
  action.type = ParseActionTypeAccept;
  return action;
}

ParseAction ParseAction::Shift(ParseStateId state_index) {
  return ParseAction(ParseActionTypeShift, state_index, rules::NONE(), 0, nullptr);
}

ParseAction ParseAction::Recover(ParseStateId state_index) {
  return ParseAction(ParseActionTypeRecover, state_index, rules::NONE(), 0,
                     nullptr);
}

ParseAction ParseAction::ShiftExtra() {
  ParseAction action;
  action.type = ParseActionTypeShift;
  action.extra = true;
  return action;
}

ParseAction ParseAction::Reduce(Symbol symbol, size_t consumed_symbol_count,
                                const Production &production) {
  return ParseAction(ParseActionTypeReduce, 0, symbol, consumed_symbol_count,
                     &production);
}

int ParseAction::precedence() const {
  if (consumed_symbol_count >= production->size()) {
    if (production->empty()) {
      return 0;
    } else {
      return production->back().precedence;
    }
  } else {
    return production->at(consumed_symbol_count).precedence;
  }
}

rules::Associativity ParseAction::associativity() const {
  if (consumed_symbol_count >= production->size()) {
    if (production->empty()) {
      return rules::AssociativityNone;
    } else {
      return production->back().associativity;
    }
  } else {
    return production->at(consumed_symbol_count).associativity;
  }
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
  for (const auto &pair : terminal_entries)
    if (pair.second.actions.size() > 0 &&
        pair.second.actions.back().type == ParseActionTypeShift)
      return true;
  return (!nonterminal_entries.empty());
}

void ParseState::each_referenced_state(function<void(ParseStateId *)> fn) {
  for (auto &entry : terminal_entries)
    for (ParseAction &action : entry.second.actions)
      if (action.type == ParseActionTypeShift || ParseActionTypeRecover)
        fn(&action.state_index);
  for (auto &entry : nonterminal_entries)
    fn(&entry.second);
}

bool ParseState::operator==(const ParseState &other) const {
  return terminal_entries == other.terminal_entries &&
    nonterminal_entries == other.nonterminal_entries;
}

ParseAction &ParseTable::add_terminal_action(ParseStateId state_id,
                                             Symbol lookahead,
                                             ParseAction action) {
  if (action.type == ParseActionTypeShift && action.extra)
    symbols[lookahead].extra = true;
  else
    symbols[lookahead].structural = true;

  ParseTableEntry &entry = states[state_id].terminal_entries[lookahead];
  entry.actions.push_back(action);
  return *entry.actions.rbegin();
}

void ParseTable::set_nonterminal_action(ParseStateId state_id,
                                        Symbol::Index lookahead,
                                        ParseStateId next_state_id) {
  symbols[Symbol::non_terminal(lookahead)].structural = true;
  states[state_id].nonterminal_entries[lookahead] = next_state_id;
}

}  // namespace tree_sitter
