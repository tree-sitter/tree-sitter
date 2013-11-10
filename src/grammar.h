#ifndef __TreeSitter__grammar__
#define __TreeSitter__grammar__

#include <unordered_map>
#include "rules.h"

namespace tree_sitter {
    class Grammar {
        typedef std::unordered_map<std::string, rules::rule_ptr> rule_map;
    public:
        Grammar(const rule_map &rules, const std::string &start_rule_name);
        Grammar(const std::initializer_list<std::string> &rule_names,
                const std::initializer_list<rules::rule_ptr> &rules);
        rule_map rules;
        std::string start_rule_name;
    };
}

#endif
