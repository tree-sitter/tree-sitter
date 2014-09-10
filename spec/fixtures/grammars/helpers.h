#ifndef TREESITTER_EXAMPLES_HELPERS_
#define TREESITTER_EXAMPLES_HELPERS_

#include "tree_sitter/compiler.h"

namespace tree_sitter_examples {

using namespace tree_sitter::rules;

rule_ptr comma_sep1(rule_ptr element);
rule_ptr comma_sep(rule_ptr element);
rule_ptr optional(rule_ptr rule);
rule_ptr in_parens(rule_ptr rule);
rule_ptr in_braces(rule_ptr rule);
rule_ptr in_brackets(rule_ptr rule);
rule_ptr infix_op(std::string op, std::string rule_name, int precedence);
rule_ptr prefix_op(std::string op, std::string rule_name, int precedence);
rule_ptr postfix_op(std::string op, std::string rule_name, int precedence);
rule_ptr delimited(std::string delimiter);

}  // namespace tree_sitter_examples

#endif  // TREESITTER_EXAMPLES_HELPERS_
