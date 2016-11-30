#ifndef COMPILER_RULES_H_
#define COMPILER_RULES_H_

#include <string>
#include <vector>
#include <memory>
#include "compiler/rule.h"

namespace tree_sitter {

rule_ptr blank();
rule_ptr choice(const std::vector<rule_ptr> &);
rule_ptr repeat(const rule_ptr &);
rule_ptr repeat1(const rule_ptr &);
rule_ptr seq(const std::vector<rule_ptr> &);
rule_ptr sym(const std::string &);
rule_ptr pattern(const std::string &);
rule_ptr str(const std::string &);
rule_ptr prec(int precedence, const rule_ptr &);
rule_ptr prec_left(const rule_ptr &);
rule_ptr prec_left(int precedence, const rule_ptr &);
rule_ptr prec_right(const rule_ptr &);
rule_ptr prec_right(int precedence, const rule_ptr &);
rule_ptr token(const rule_ptr &rule);
rule_ptr external_token(const std::string &);

}  // namespace std

#endif  // COMPILER_RULES_H_
