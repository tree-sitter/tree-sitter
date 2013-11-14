#include "grammar.h"

namespace tree_sitter {
    Grammar::Grammar(const rule_map_init_list &rules) :
        rules(rules),
        start_rule_name(rules.begin()->first) {}

    const rules::rule_ptr Grammar::rule(const std::string &name) {
        auto iter = rules.find(name);
        return (iter == rules.end()) ?
            rules::rule_ptr(nullptr) :
            iter->second;
    }
}