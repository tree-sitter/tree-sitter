#include "grammar.h"

using namespace std;

namespace tree_sitter {
    Grammar::Grammar(const rule_map_init_list &rules) :
        rules(rules),
        start_rule_name(rules.begin()->first) {}

    const rules::rule_ptr Grammar::rule(const std::string &name) const {
        auto iter = rules.find(name);
        return (iter == rules.end()) ?
            rules::rule_ptr(nullptr) :
            iter->second;
    }
    
    vector<string> Grammar::rule_names() const {
        vector<string> result;
        for (auto pair : rules) {
            result.push_back(pair.first);
        }
        return result;
    }
    
}