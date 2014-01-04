#include "grammar.h"

using namespace std;

namespace tree_sitter {
    Grammar::Grammar(const std::initializer_list<std::pair<const std::string, const rules::rule_ptr>> &rules) :
        rules(rules),
        start_rule_name(rules.begin()->first) {}
    
    Grammar::Grammar(std::string start_rule_name, const std::unordered_map<std::string, const rules::rule_ptr> &rules) :
        rules(rules),
        start_rule_name(start_rule_name) {}


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
    
    bool Grammar::operator==(const Grammar &other) const {
        if (other.start_rule_name != start_rule_name) return false;
        if (other.rules.size() != rules.size()) return false;
        for (auto pair : rules) {
            auto other_pair = other.rules.find(pair.first);
            if (other_pair == other.rules.end()) return false;
            if (!other_pair->second->operator==(*pair.second)) return false;
        }
        return true;
    }
    
    bool Grammar::has_definition(const rules::Symbol &symbol) const {
        return rules.find(symbol.name) != rules.end();
    }
    
    std::ostream& operator<<(std::ostream &stream, const Grammar &grammar) {
        stream << string("#<grammar: ");
        bool started = false;
        for (auto pair : grammar.rules) {
            if (started) stream << string(", ");
            stream << pair.first;
            stream << string(" => ");
            stream << pair.second;
            started = true;
        }
        return stream << string(">");
    }
}
