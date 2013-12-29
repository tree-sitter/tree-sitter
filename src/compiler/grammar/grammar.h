#ifndef __TreeSitter__grammar__
#define __TreeSitter__grammar__

#include <unordered_map>
#include <vector>
#include "rules.h"

namespace tree_sitter {
    class Grammar {
        typedef std::initializer_list<std::pair<const std::string, rules::rule_ptr>> rule_map_init_list;
    public:
        Grammar(const rule_map_init_list &rules);
        const rules::rule_ptr rule(const std::string &) const;
        const std::string start_rule_name;
        std::vector<std::string> rule_names() const;

        const std::unordered_map<std::string, rules::rule_ptr> rules;
    };
}

#endif
