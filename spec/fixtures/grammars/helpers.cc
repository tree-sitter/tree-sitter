#include "tree_sitter/compiler.h"

namespace tree_sitter_examples {

using namespace tree_sitter;

rule_ptr comma_sep1(rule_ptr element) {
  return seq({ element, repeat(seq({ str(","), element })) });
}

rule_ptr comma_sep(rule_ptr element) {
  return choice({ comma_sep1(element), blank() });
}

rule_ptr optional(rule_ptr rule) {
  return choice({ rule, blank() });
}

rule_ptr in_parens(rule_ptr rule) {
  return seq({ str("("), rule, str(")") });
}

rule_ptr in_braces(rule_ptr rule) {
  return seq({ str("{"), rule, str("}") });
}

rule_ptr in_brackets(rule_ptr rule) {
  return seq({ str("["), rule, str("]") });
}

rule_ptr infix_op(std::string op, std::string rule_name, int precedence) {
  return prec(precedence, seq({
    sym(rule_name),
    str(op),
    sym(rule_name) }));
}

rule_ptr prefix_op(std::string op, std::string rule_name, int precedence) {
  return prec(precedence, seq({
    str(op),
    sym(rule_name) }));
}

rule_ptr postfix_op(std::string op, std::string rule_name, int precedence) {
  return prec(precedence, seq({
    sym(rule_name),
    str(op) }));
}

rule_ptr delimited(std::string delimiter) {
  return token(seq({
    str(delimiter),
    repeat(choice({
      pattern("[^" + delimiter + "]"),
      seq({ str("\\"), str(delimiter) }) })),
    str(delimiter) }));
}

}  // namespace tree_sitter_examples
