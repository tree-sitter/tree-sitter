#include "grammar.h"

using namespace std;

namespace tree_sitter {
    Grammar::Grammar(const rule_map &rules, const std::string &start_rule_name) :
        rules(rules),
        start_rule_name(start_rule_name) {};
    
    Grammar::Grammar(const initializer_list<string> &rule_names,
                     const initializer_list<rules::rule_ptr> &rule_vals) {
        rules = rule_map();
        auto rule_name_i = rule_names.begin();
        auto rule_i = rule_vals.begin();
        start_rule_name = *rule_name_i;   
        for (; rule_i != rule_vals.end(); rule_i++ && rule_name_i++) {
            rules[*rule_name_i] = *rule_i;
        }
    }
}