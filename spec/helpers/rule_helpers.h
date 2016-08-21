#ifndef HELPERS_RULE_HELPERS_H_
#define HELPERS_RULE_HELPERS_H_

#include "tree_sitter/compiler.h"
#include "compiler/rules.h"
#include "compiler/rules/character_set.h"
#include "compiler/rules/metadata.h"
#include "compiler/grammar.h"

namespace tree_sitter {
  rule_ptr metadata(rule_ptr, std::map<rules::MetadataKey, int>);
  rule_ptr character(const std::set<uint32_t> &);
  rule_ptr character(const std::set<uint32_t> &, bool sign);
  rule_ptr i_sym(size_t index);
  rule_ptr i_token(size_t index);
  rule_ptr active_prec(int precedence, rule_ptr);

  bool operator==(const Variable &left, const Variable &right);
}

#endif  // HELPERS_RULE_HELPERS_H_
