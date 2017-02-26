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

typedef int64_t LexStateId;

typedef enum {
  LexActionTypeError,
  LexActionTypeAccept,
  LexActionTypeAcceptFragile,
  LexActionTypeAdvance
} LexActionType;

struct AdvanceAction {
  AdvanceAction();
  AdvanceAction(size_t, PrecedenceRange, bool);

  bool operator==(const AdvanceAction &other) const;

  LexStateId state_index;
  PrecedenceRange precedence_range;
  bool in_main_token;
};

struct AcceptTokenAction {
  AcceptTokenAction();
  AcceptTokenAction(rules::Symbol, int, bool);

  bool is_present() const;
  bool operator==(const AcceptTokenAction &action) const;

  rules::Symbol symbol;
  int precedence;
  bool is_string;
};

}  // namespace tree_sitter

namespace std {}  // namespace std

namespace tree_sitter {

class LexState {
 public:
  LexState();
  std::set<rules::CharacterSet> expected_inputs() const;
  bool operator==(const LexState &) const;

  std::map<rules::CharacterSet, AdvanceAction> advance_actions;
  AcceptTokenAction accept_action;
  bool is_token_start;
};

class LexTable {
 public:
  LexStateId add_state();
  LexState &state(LexStateId state_id);
  std::vector<LexState> states;
};

}  // namespace tree_sitter

#endif  // COMPILER_LEX_TABLE_H_
