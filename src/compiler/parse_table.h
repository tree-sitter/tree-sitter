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
  static ParseAction Accept();
  static ParseAction Error();
  static ParseAction Shift(ParseStateId state_index);
  static ParseAction Recover();
  static ParseAction Reduce(rules::Symbol symbol, size_t child_count,
                            int precedence, int dynamic_precedence, rules::Associativity,
                            unsigned alias_sequence_id);
  static ParseAction ShiftExtra();
  bool operator==(const ParseAction &) const;
  bool operator<(const ParseAction &) const;

  ParseActionType type;
  ParseStateId state_index;
  rules::Symbol symbol;
  unsigned consumed_symbol_count;
  int precedence;
  int dynamic_precedence;
  rules::Associativity associativity;
  unsigned alias_sequence_id;
  bool extra;
  bool repetition;
};

struct ParseTableEntry {
  ParseTableEntry();
  ParseTableEntry(const std::vector<ParseAction> &, bool);
  bool operator==(const ParseTableEntry &other) const;
  inline bool operator!=(const ParseTableEntry &other) const {
    return !operator==(other);
  }

  std::vector<ParseAction> actions;
  bool reusable;
};

struct ParseState {
  ParseState();
  bool operator==(const ParseState &) const;
  bool merge(const ParseState &);
  void each_referenced_state(std::function<void(ParseStateId *)>);
  bool has_shift_action() const;
  bool has_terminal_entry(rules::Symbol) const;

  std::map<rules::Symbol, ParseTableEntry> terminal_entries;
  std::map<rules::Symbol::Index, ParseStateId> nonterminal_entries;
  LexStateId lex_state_id;
};

using AliasSequence = std::vector<rules::Alias>;

struct ParseTable {
  ParseAction &add_terminal_action(ParseStateId state_id, rules::Symbol, ParseAction);
  void set_nonterminal_action(ParseStateId, rules::Symbol::Index, ParseStateId);

  std::vector<ParseState> states;
  std::set<rules::Symbol> symbols;
  std::vector<AliasSequence> alias_sequences;
  unsigned max_alias_sequence_length = 0;
};

}  // namespace tree_sitter

#endif  // COMPILER_PARSE_TABLE_H_
