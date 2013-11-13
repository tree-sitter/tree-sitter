#include "grammar.h"

using namespace std;

namespace tree_sitter {
    Grammar::Grammar(const rule_map &rules, const std::string &start_rule_name) :
        rules(rules),
        start_rule_name(start_rule_name) {};

    std::unordered_map<std::string, rules::rule_ptr> build_rule_map(const initializer_list<string> &rule_names,
                            const initializer_list<rules::rule_ptr> &rule_vals) {
        std::unordered_map<std::string, rules::rule_ptr> result;
        auto rule_name_i = rule_names.begin();
        auto rule_i = rule_vals.begin();
        while (rule_i != rule_vals.end()) {
            result[*rule_name_i] = *rule_i;
            rule_i++;
            rule_name_i++;
        }
        return result;
    }
    
    Grammar::Grammar(const initializer_list<string> &names, const initializer_list<rules::rule_ptr> &values) :
        rules(build_rule_map(names, values)),
        start_rule_name(*names.begin()) {}
}