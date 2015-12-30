#ifndef COMPILER_LEX_TABLE_H_
#define COMPILER_LEX_TABLE_H_

#include <map>
#include <vector>
#include <set>
#include <string>
#include "compiler/precedence_range.h"
#include "compiler/rules/symbol.h"
#include "compiler/rules/character_set.h"

namespace tree_sitter {

typedef enum {
  LexActionTypeError,
  LexActionTypeAccept,
  LexActionTypeAcceptFragile,
  LexActionTypeAdvance
} LexActionType;

class LexAction {
  LexAction(LexActionType type, size_t state_index, rules::Symbol symbol,
            PrecedenceRange precedence_range, bool is_string);

 public:
  LexAction();
  static LexAction Accept(rules::Symbol symbol, int precedence, bool is_string);
  static LexAction Error();
  static LexAction Advance(size_t state_index, PrecedenceRange precedence_range);
  bool operator==(const LexAction &action) const;

  LexActionType type;
  rules::Symbol symbol;
  size_t state_index;
  PrecedenceRange precedence_range;
  bool is_string;
};

}  // namespace tree_sitter

namespace std {

template <>
struct hash<tree_sitter::LexAction> {
  size_t operator()(const tree_sitter::LexAction &action) const {
    return (hash<int>()(action.type) ^
            hash<tree_sitter::rules::Symbol>()(action.symbol) ^
            hash<size_t>()(action.state_index));
  }
};

}  // namespace std

namespace tree_sitter {

class LexState {
 public:
  LexState();
  std::set<rules::CharacterSet> expected_inputs() const;
  bool operator==(const LexState &) const;
  void each_action(std::function<void(LexAction *)>);

  std::map<rules::CharacterSet, LexAction> actions;
  LexAction default_action;
  bool is_token_start;
};

typedef int64_t LexStateId;

class LexTable {
 public:
  LexStateId add_state();
  LexState &state(LexStateId state_id);
  std::vector<LexState> states;
};

}  // namespace tree_sitter

#endif  // COMPILER_LEX_TABLE_H_
