#ifndef HELPERS_RULE_HELPERS_H_
#define HELPERS_RULE_HELPERS_H_

#include "tree_sitter/compiler.h"
#include "compiler/rules.h"
#include "compiler/rules/character_set.h"
#include "compiler/rules/metadata.h"
#include "compiler/variable.h"

namespace tree_sitter {
  rule_ptr metadata(rule_ptr, rules::MetadataParams params);
  rule_ptr character(const std::set<uint32_t> &);
  rule_ptr character(const std::set<uint32_t> &, bool sign);
  rule_ptr i_sym(size_t index);
  rule_ptr i_token(size_t index);
  rule_ptr active_prec(int precedence, rule_ptr);

  struct Variable;
  struct LexicalVariable;

  bool operator==(const Variable &left, const Variable &right);
  bool operator==(const LexicalVariable &left, const LexicalVariable &right);
}

#endif  // HELPERS_RULE_HELPERS_H_
