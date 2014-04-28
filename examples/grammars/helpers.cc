#include "tree_sitter/compiler.h"

namespace tree_sitter_examples {
    using namespace tree_sitter::rules;
    
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
    
    rule_ptr infix(int precedence, std::string op) {
        return prec(precedence, seq({
            sym("expression"),
            str(op),
            sym("expression") }));
    }
    
    rule_ptr prefix(int precedence, std::string op) {
        return prec(precedence, seq({
            str(op),
            sym("expression") }));
    }
}
