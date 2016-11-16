#ifndef COMPILER_PARSE_TABLE_H_
#define COMPILER_PARSE_TABLE_H_

#include <map>
#include <set>
#include <utility>
#include <vector>
#include "compiler/util/hash_combine.h"
#include "compiler/lex_table.h"
#include "compiler/rules/symbol.h"
#include "compiler/rules/metadata.h"
#include "compiler/precedence_range.h"
#include "compiler/syntax_grammar.h"

namespace tree_sitter {

typedef int64_t ParseStateId;

enum ParseActionType {
  ParseActionTypeError,
  ParseActionTypeShift,
  ParseActionTypeReduce,
  ParseActionTypeAccept,
  ParseActionTypeRecover,
};

class ParseAction {
  ParseAction(ParseActionType type, ParseStateId state_index,
              rules::Symbol symbol, size_t consumed_symbol_count,
              PrecedenceRange range, rules::Associativity, const Production *);

 public:
  ParseAction();
  static ParseAction Accept();
  static ParseAction Error();
  static ParseAction Shift(ParseStateId state_index, PrecedenceRange precedence);
  static ParseAction Recover(ParseStateId state_index);
  static ParseAction Reduce(rules::Symbol symbol, size_t consumed_symbol_count,
                            int precedence, rules::Associativity,
                            const Production &);
  static ParseAction ShiftExtra();
  bool operator==(const ParseAction &) const;
  bool operator<(const ParseAction &) const;

  ParseActionType type;
  bool extra;
  bool fragile;
  rules::Symbol symbol;
  ParseStateId state_index;
  size_t consumed_symbol_count;

  PrecedenceRange precedence_range;
  rules::Associativity associativity;
  const Production *production;
};

struct ParseTableEntry {
  std::vector<ParseAction> actions;
  bool reusable;
  bool depends_on_lookahead;

  ParseTableEntry();
  ParseTableEntry(const std::vector<ParseAction> &, bool, bool);
  bool operator==(const ParseTableEntry &other) const;

  inline bool operator!=(const ParseTableEntry &other) const {
    return !operator==(other);
  }
};

class ParseState {
 public:
  ParseState();
  std::set<rules::Symbol> expected_inputs() const;
  bool operator==(const ParseState &) const;
  bool merge(const ParseState &);
  void each_referenced_state(std::function<void(ParseStateId *)>);
  bool has_shift_action() const;
  void compute_shift_actions_signature();

  std::map<rules::Symbol::Index, ParseTableEntry> terminal_entries;
  std::map<rules::Symbol::Index, ParseStateId> nonterminal_entries;
  LexStateId lex_state_id;
  size_t shift_actions_signature;
};

struct ParseTableSymbolMetadata {
  bool extra;
  bool structural;
};

class ParseTable {
 public:
  std::set<rules::Symbol> all_symbols() const;
  ParseStateId add_state();
  ParseAction &add_terminal_action(ParseStateId state_id, int, ParseAction);
  ParseAction &set_terminal_action(ParseStateId state_id, int index, ParseAction);
  void set_nonterminal_action(ParseStateId state_id, int index, ParseStateId);
  bool merge_state(size_t i, size_t j);

  std::vector<ParseState> states;
  std::map<rules::Symbol, ParseTableSymbolMetadata> symbols;

  std::set<rules::Symbol::Index> mergeable_symbols;
};

}  // namespace tree_sitter

namespace std {

using tree_sitter::util::hash_combine;

template <>
struct hash<tree_sitter::ParseAction> {
  size_t operator()(const tree_sitter::ParseAction &action) const {
    size_t result = 0;
    hash_combine<int>(&result, action.type);
    hash_combine(&result, action.extra);
    hash_combine(&result, action.fragile);
    hash_combine(&result, action.symbol);
    hash_combine(&result, action.state_index);
    hash_combine(&result, action.consumed_symbol_count);
    return result;
  }
};

template <>
struct hash<tree_sitter::ParseTableEntry> {
  size_t operator()(const tree_sitter::ParseTableEntry &entry) const {
    size_t result = 0;
    hash_combine(&result, entry.actions.size());
    for (const tree_sitter::ParseAction &action : entry.actions) {
      hash_combine(&result, action);
    }
    hash_combine(&result, entry.reusable);
    hash_combine(&result, entry.depends_on_lookahead);
    return result;
  }
};

}

#endif  // COMPILER_PARSE_TABLE_H_
