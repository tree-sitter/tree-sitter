#ifndef COMPILER_LEX_TABLE_H_
#define COMPILER_LEX_TABLE_H_

#include <map>
#include <vector>
#include <set>
#include <string>
#include "compiler/precedence_range.h"
#include "compiler/rule.h"

namespace tree_sitter {

typedef int64_t LexStateId;

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

struct LexState {
  bool operator==(const LexState &) const;

  std::map<rules::CharacterSet, AdvanceAction> advance_actions;
  AcceptTokenAction accept_action;
};

struct LexTable {
  std::vector<LexState> states;
};

}  // namespace tree_sitter

#endif  // COMPILER_LEX_TABLE_H_
