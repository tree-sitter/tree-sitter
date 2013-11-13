#include "rules.h"

namespace tree_sitter {
    namespace rules {
        rule_ptr blank() {
            return rule_ptr(new Blank());
        }
        
        rule_ptr sym(const std::string &name) {
            return rule_ptr(new Symbol(name));
        }
        
        rule_ptr character(char value) {
            return rule_ptr(new Char(value));
        }
        
        rule_ptr str(const std::string &value) {
            return rule_ptr(new String(value));
        }
        
        rule_ptr pattern(const std::string &value) {
            return rule_ptr(new Pattern(value));
        }
        
        template <typename RuleClass>
        rule_ptr build_binary_tree(const std::initializer_list<rule_ptr> &rules) {
            rule_ptr result(nullptr);
            for (auto it = rules.end() - 1; it >= rules.begin(); --it)
                result = result.get() ? rule_ptr(new RuleClass(*it, result)) : *it;
            return result;
        }
        
        rule_ptr seq(const std::initializer_list<rule_ptr> &rules) {
            return build_binary_tree<Seq>(rules);
        }
        
        rule_ptr choice(const std::initializer_list<rule_ptr> &rules) {
            return build_binary_tree<Choice>(rules);
        }
    }
}