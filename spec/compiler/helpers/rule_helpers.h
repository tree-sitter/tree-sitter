#ifndef __tree_sitter__character_set_helpers__
#define __tree_sitter__character_set_helpers__

#include "tree_sitter/compiler.h"
#include "compiler/rules/character_set.h"
#include "compiler/rules/metadata.h"
#include "compiler/variable.h"

namespace tree_sitter {
  rule_ptr metadata(rule_ptr, std::map<rules::MetadataKey, int>);
  rule_ptr character(const std::set<uint32_t> &);
  rule_ptr character(const std::set<uint32_t> &, bool sign);
  rule_ptr i_sym(size_t index);
  rule_ptr i_token(size_t index);
  rule_ptr active_prec(int precedence, rule_ptr);

  bool operator==(const Variable &left, const Variable &right);
}

#endif
