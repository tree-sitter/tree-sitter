#ifndef COMPILER_PARSE_TABLE_H_
#define COMPILER_PARSE_TABLE_H_

#include <map>
#include <set>
#include <utility>
#include <vector>
#include "compiler/lex_table.h"
#include "compiler/rule.h"
#include "compiler/precedence_range.h"
#include "compiler/syntax_grammar.h"

namespace tree_sitter {

typedef size_t ParseStateId;

enum ParseActionType {
  ParseActionTypeError,
  ParseActionTypeShift,
  ParseActionTypeReduce,
  ParseActionTypeAccept,
  ParseActionTypeRecover,
};

struct ParseAction {
  ParseAction();
  ParseAction(ParseActionType type, ParseStateId state_index,
              rules::Symbol symbol, size_t consumed_symbol_count,
              const Production *);
  static ParseAction Accept();
  static ParseAction Error();
  static ParseAction Shift(ParseStateId state_index);
  static ParseAction Recover(ParseStateId state_index);
  static ParseAction Reduce(rules::Symbol symbol, size_t consumed_symbol_count,
                            const Production &);
  static ParseAction ShiftExtra();
  bool operator==(const ParseAction &) const;
  bool operator<(const ParseAction &) const;
  rules::Associativity associativity() const;
  int precedence() const;

  ParseActionType type;
  bool extra;
  bool fragile;
  ParseStateId state_index;
  rules::Symbol symbol;
  size_t consumed_symbol_count;
  const Production *production;
};

struct ParseTableEntry {
  ParseTableEntry();
  ParseTableEntry(const std::vector<ParseAction> &, bool, bool);
  bool operator==(const ParseTableEntry &other) const;
  inline bool operator!=(const ParseTableEntry &other) const {
    return !operator==(other);
  }

  std::vector<ParseAction> actions;
  bool reusable;
  bool depends_on_lookahead;
};

struct ParseState {
  ParseState();
  bool operator==(const ParseState &) const;
  bool merge(const ParseState &);
  void each_referenced_state(std::function<void(ParseStateId *)>);
  bool has_shift_action() const;

  std::map<rules::Symbol, ParseTableEntry> terminal_entries;
  std::map<rules::Symbol::Index, ParseStateId> nonterminal_entries;
  LexStateId lex_state_id;
  size_t shift_actions_signature;
};

struct ParseTableSymbolMetadata {
  bool extra;
  bool structural;
};

struct ParseTable {
  ParseAction &add_terminal_action(ParseStateId state_id, rules::Symbol, ParseAction);
  void set_nonterminal_action(ParseStateId, rules::Symbol::Index, ParseStateId);

  std::vector<ParseState> states;
  std::map<rules::Symbol, ParseTableSymbolMetadata> symbols;
};

}  // namespace tree_sitter

#endif  // COMPILER_PARSE_TABLE_H_
