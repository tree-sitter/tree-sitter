#ifndef __TreeSitter__rules__
#define __TreeSitter__rules__

#include "rules/rule.h"

namespace tree_sitter {
    namespace rules {
        rule_ptr blank();
        rule_ptr sym(const std::string &name);
        rule_ptr character(char value);
        rule_ptr str(const std::string &value);
        rule_ptr pattern(const std::string &value);
        rule_ptr seq(const std::initializer_list<rule_ptr> &rules);
        rule_ptr choice(const std::initializer_list<rule_ptr> &rules);
    }
}

#endif
