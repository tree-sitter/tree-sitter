#ifndef COMPILER_LEX_TABLE_H_
#define COMPILER_LEX_TABLE_H_

#include <map>
#include <vector>
#include <set>
#include <string>
#include "compiler/rules/symbol.h"
#include "compiler/rules/character_set.h"

namespace tree_sitter {

typedef enum {
  LexActionTypeError,
  LexActionTypeAccept,
  LexActionTypeAdvance
} LexActionType;

class LexAction {
  LexAction(LexActionType type, size_t state_index, rules::Symbol symbol,
            std::set<int> precedence_values);

 public:
  LexAction();
  static LexAction Accept(rules::Symbol symbol, int precedence);
  static LexAction Error();
  static LexAction Advance(size_t state_index, std::set<int> precedence_values);
  bool operator==(const LexAction &action) const;

  LexActionType type;
  rules::Symbol symbol;
  size_t state_index;
  std::set<int> precedence_values;
};

std::ostream &operator<<(std::ostream &stream, const LexAction &item);

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
  std::map<rules::CharacterSet, LexAction> actions;
  LexAction default_action;
  std::set<rules::CharacterSet> expected_inputs() const;
  bool is_token_start;
};

typedef int64_t LexStateId;

class LexTable {
 public:
  static const LexStateId ERROR_STATE_ID;
  LexStateId add_state();
  LexState &state(LexStateId state_id);

  std::vector<LexState> states;
  LexState error_state;
};

}  // namespace tree_sitter

#endif  // COMPILER_LEX_TABLE_H_
