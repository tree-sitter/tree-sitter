#include "compiler/parse_table.h"
#include <string>
#include "compiler/precedence_range.h"
#include "compiler/rule.h"

namespace tree_sitter {

using std::string;
using std::to_string;
using std::vector;
using std::function;
using rules::Symbol;

ParseAction::ParseAction()
  : production(nullptr),
    consumed_symbol_count(0),
    symbol(rules::NONE()),
    type(ParseActionTypeError),
    extra(false),
    fragile(false),
    state_index(-1),
    rename_sequence_id(0) {}

ParseAction ParseAction::Error() {
  return ParseAction();
}

ParseAction ParseAction::Accept() {
  ParseAction action;
  action.type = ParseActionTypeAccept;
  return action;
}

ParseAction ParseAction::Shift(ParseStateId state_index) {
  ParseAction result;
  result.type = ParseActionTypeShift;
  result.state_index = state_index;
  return result;
}

ParseAction ParseAction::Recover(ParseStateId state_index) {
  ParseAction result;
  result.type = ParseActionTypeRecover;
  result.state_index = state_index;
  return result;
}

ParseAction ParseAction::ShiftExtra() {
  ParseAction action;
  action.type = ParseActionTypeShift;
  action.extra = true;
  return action;
}

ParseAction ParseAction::Reduce(Symbol symbol, size_t consumed_symbol_count,
                                const Production &production) {
  ParseAction result;
  result.type = ParseActionTypeReduce;
  result.symbol = symbol;
  result.consumed_symbol_count = consumed_symbol_count;
  result.production = &production;
  result.dynamic_precedence = production.dynamic_precedence;
  return result;
}

bool ParseAction::operator==(const ParseAction &other) const {
  return
    type == other.type &&
    extra == other.extra &&
    fragile == other.fragile &&
    symbol == other.symbol &&
    state_index == other.state_index &&
    production == other.production &&
    consumed_symbol_count == other.consumed_symbol_count &&
    rename_sequence_id == other.rename_sequence_id;
}

bool ParseAction::operator<(const ParseAction &other) const {
  if (type < other.type) return true;
  if (other.type < type) return false;
  if (extra && !other.extra) return true;
  if (other.extra && !extra) return false;
  if (fragile && !other.fragile) return true;
  if (other.fragile && !fragile) return false;
  if (symbol < other.symbol) return true;
  if (other.symbol < symbol) return false;
  if (state_index < other.state_index) return true;
  if (other.state_index < state_index) return false;
  if (production < other.production) return true;
  if (other.production < production) return false;
  if (consumed_symbol_count < other.consumed_symbol_count) return true;
  if (other.consumed_symbol_count < consumed_symbol_count) return false;
  return rename_sequence_id < other.rename_sequence_id;
}

ParseTableEntry::ParseTableEntry()
  : reusable(true), depends_on_lookahead(false) {}

ParseTableEntry::ParseTableEntry(const vector<ParseAction> &actions,
                                 bool reusable, bool depends_on_lookahead)
  : actions(actions),
    reusable(reusable),
    depends_on_lookahead(depends_on_lookahead) {}

bool ParseTableEntry::operator==(const ParseTableEntry &other) const {
  return
    actions == other.actions &&
    reusable == other.reusable &&
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
      if ((action.type == ParseActionTypeShift && !action.extra) || action.type == ParseActionTypeRecover)
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
