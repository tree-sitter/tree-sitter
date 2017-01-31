#ifndef COMPILER_GRAMMAR_H_
#define COMPILER_GRAMMAR_H_

#include <vector>
#include <string>
#include <utility>
#include "compiler/rule.h"

namespace tree_sitter {

struct Grammar {
  std::vector<std::pair<std::string, rule_ptr>> rules;
  std::vector<rule_ptr> extra_tokens;
  std::vector<std::vector<std::string>> expected_conflicts;
  std::vector<std::string> external_tokens;
};

}  // namespace tree_sitter

#endif  // COMPILER_GRAMMAR_H_
