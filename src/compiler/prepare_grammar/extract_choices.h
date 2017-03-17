#ifndef COMPILER_PREPARE_GRAMMAR_EXTRACT_CHOICES_H_
#define COMPILER_PREPARE_GRAMMAR_EXTRACT_CHOICES_H_

#include <vector>
#include "compiler/rule.h"

namespace tree_sitter {
namespace prepare_grammar {

std::vector<rules::Rule> extract_choices(const rules::Rule &);

}  // namespace prepare_grammar
}  // namespace tree_sitter

#endif  // COMPILER_PREPARE_GRAMMAR_EXTRACT_CHOICES_H_
