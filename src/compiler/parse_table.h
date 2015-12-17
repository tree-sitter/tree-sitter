#ifndef COMPILER_PARSE_TABLE_H_
#define COMPILER_PARSE_TABLE_H_

#include <map>
#include <set>
#include <utility>
#include <vector>
#include "compiler/lex_table.h"
#include "compiler/rules/symbol.h"
#include "compiler/rules/metadata.h"
#include "compiler/precedence_range.h"
#include "compiler/syntax_grammar.h"

namespace tree_sitter {

typedef uint64_t ParseStateId;

typedef enum {
  ParseActionTypeError,
  ParseActionTypeShift,
  ParseActionTypeReduce,
  ParseActionTypeAccept,
} ParseActionType;

class ParseAction {
  ParseAction(ParseActionType type, ParseStateId state_index,
              rules::Symbol symbol, size_t consumed_symbol_count,
              PrecedenceRange range, rules::Associativity, const Production *);

 public:
  ParseAction();
  static ParseAction Accept();
  static ParseAction Error();
  static ParseAction Shift(ParseStateId state_index, PrecedenceRange precedence);
  static ParseAction Reduce(rules::Symbol symbol, size_t consumed_symbol_count,
                            int precedence, rules::Associativity,
                            const Production &);
  static ParseAction ShiftExtra();
  static ParseAction ReduceExtra(rules::Symbol symbol);
  bool operator==(const ParseAction &) const;
  bool operator<(const ParseAction &) const;

  ParseActionType type;
  bool extra;
  bool fragile;
  bool can_hide_split;
  rules::Symbol symbol;
  ParseStateId state_index;
  size_t consumed_symbol_count;
  PrecedenceRange precedence_range;
  rules::Associativity associativity;
  const Production *production;
};

}  // namespace tree_sitter

namespace std {

template <>
struct hash<tree_sitter::ParseAction> {
  size_t operator()(const tree_sitter::ParseAction &action) const {
    return (hash<int>()(action.type) ^
            hash<tree_sitter::rules::Symbol>()(action.symbol) ^
            hash<size_t>()(action.state_index) ^
            hash<size_t>()(action.consumed_symbol_count) ^
            hash<bool>()(action.extra) ^ hash<bool>()(action.fragile) ^
            hash<bool>()(action.can_hide_split) ^
            hash<int>()(action.associativity) ^
            hash<int>()(action.precedence_range.min) ^
            hash<int>()(action.precedence_range.max) ^
            hash<const void *>()(&action.production));
  }
};

}  // namespace std

namespace tree_sitter {

class ParseState {
 public:
  ParseState();
  std::map<rules::Symbol, std::vector<ParseAction>> actions;
  std::set<rules::Symbol> expected_inputs() const;
  LexStateId lex_state_id;
};

struct ParseTableSymbolMetadata {
  bool structural;
};

class ParseTable {
 public:
  std::set<rules::Symbol> all_symbols() const;
  ParseStateId add_state();
  ParseAction &set_action(ParseStateId state_id, rules::Symbol symbol,
                          ParseAction action);
  ParseAction &add_action(ParseStateId state_id, rules::Symbol symbol,
                          ParseAction action);

  std::vector<ParseState> states;
  std::map<rules::Symbol, ParseTableSymbolMetadata> symbols;
};

}  // namespace tree_sitter

#endif  // COMPILER_PARSE_TABLE_H_
