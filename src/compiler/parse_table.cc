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

ParseAction::ParseAction() :
  type(ParseActionTypeError),
  state_index(-1),
  symbol(rules::NONE()),
  consumed_symbol_count(0),
  precedence(0),
  dynamic_precedence(0),
  associativity(rules::AssociativityNone),
  alias_sequence_id(0),
  extra(false),
  repetition(false) {}

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

ParseAction ParseAction::Recover() {
  ParseAction result;
  result.type = ParseActionTypeRecover;
  return result;
}

ParseAction ParseAction::ShiftExtra() {
  ParseAction action;
  action.type = ParseActionTypeShift;
  action.extra = true;
  return action;
}

ParseAction ParseAction::Reduce(Symbol symbol, size_t consumed_symbol_count,
                                int precedence, int dynamic_precedence,
                                rules::Associativity associativity, unsigned alias_sequence_id) {
  ParseAction result;
  result.type = ParseActionTypeReduce;
  result.symbol = symbol;
  result.consumed_symbol_count = consumed_symbol_count;
  result.precedence = precedence;
  result.dynamic_precedence = dynamic_precedence;
  result.associativity = associativity;
  result.alias_sequence_id = alias_sequence_id;
  return result;
}

bool ParseAction::operator==(const ParseAction &other) const {
  return
    type == other.type &&
    state_index == other.state_index &&
    symbol == other.symbol &&
    consumed_symbol_count == other.consumed_symbol_count &&
    precedence == other.precedence &&
    dynamic_precedence == other.dynamic_precedence &&
    associativity == other.associativity &&
    alias_sequence_id == other.alias_sequence_id &&
    extra == other.extra &&
    repetition == other.repetition;
}

bool ParseAction::operator<(const ParseAction &other) const {
  if (type < other.type) return true;
  if (other.type < type) return false;
  if (state_index < other.state_index) return true;
  if (other.state_index < state_index) return false;
  if (symbol < other.symbol) return true;
  if (other.symbol < symbol) return false;
  if (consumed_symbol_count < other.consumed_symbol_count) return true;
  if (other.consumed_symbol_count < consumed_symbol_count) return false;
  if (precedence < other.precedence) return true;
  if (other.precedence < precedence) return false;
  if (dynamic_precedence < other.dynamic_precedence) return true;
  if (other.dynamic_precedence < dynamic_precedence) return false;
  if (associativity < other.associativity) return true;
  if (other.associativity < associativity) return false;
  if (extra && !other.extra) return true;
  if (other.extra && !extra) return false;
  if (repetition && !other.repetition) return true;
  if (other.repetition && !repetition) return false;
  return alias_sequence_id < other.alias_sequence_id;
}

ParseTableEntry::ParseTableEntry() : reusable(true) {}

ParseTableEntry::ParseTableEntry(const vector<ParseAction> &actions, bool reusable)
  : actions(actions),
    reusable(reusable) {}

bool ParseTableEntry::operator==(const ParseTableEntry &other) const {
  return actions == other.actions && reusable == other.reusable;
}

ParseState::ParseState() : lex_state_id(-1) {}

bool ParseState::has_shift_action() const {
  for (const auto &pair : terminal_entries)
    if (pair.second.actions.size() > 0 &&
        pair.second.actions.back().type == ParseActionTypeShift)
      return true;
  return (!nonterminal_entries.empty());
}

bool ParseState::has_terminal_entry(rules::Symbol symbol) const {
  return terminal_entries.find(symbol) != terminal_entries.end();
}

void ParseState::each_referenced_state(function<void(ParseStateId *)> fn) {
  for (auto &entry : terminal_entries)
    for (ParseAction &action : entry.second.actions)
      if (action.type == ParseActionTypeShift && !action.extra)
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
  ParseTableEntry &entry = states[state_id].terminal_entries[lookahead];
  entry.actions.push_back(action);
  return *entry.actions.rbegin();
}

void ParseTable::set_nonterminal_action(ParseStateId state_id,
                                        Symbol::Index lookahead,
                                        ParseStateId next_state_id) {
  symbols.insert(Symbol::non_terminal(lookahead));
  states[state_id].nonterminal_entries[lookahead] = next_state_id;
}

}  // namespace tree_sitter
