#include "grammar.h"

namespace tree_sitter {
    using std::vector;
    using std::string;
    using std::pair;
    using std::initializer_list;
    using std::ostream;
    
    Grammar::Grammar(const initializer_list<pair<const string, const rules::rule_ptr>> &rules) :
        rules(rules),
        start_rule_name(rules.begin()->first) {}
    
    Grammar::Grammar(std::string start_rule_name, const rule_map &rules) :
        rules(rules),
        start_rule_name(start_rule_name) {}

    Grammar::Grammar(std::string start_rule_name, const rule_map &rules, const rule_map &aux_rules) :
        rules(rules),
        aux_rules(aux_rules),
        start_rule_name(start_rule_name) {}

    const rules::rule_ptr Grammar::rule(const rules::Symbol &symbol) const {
        auto map = symbol.is_auxiliary ? aux_rules : rules;
        auto iter = map.find(symbol.name);
        if (iter != map.end())
            return iter->second;
        else
            return rules::rule_ptr();
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
        if (other.aux_rules.size() != aux_rules.size()) return false;

        for (auto pair : rules) {
            auto other_pair = other.rules.find(pair.first);
            if (other_pair == other.rules.end()) return false;
            if (!other_pair->second->operator==(*pair.second)) return false;
        }
        for (auto pair : aux_rules) {
            auto other_pair = other.aux_rules.find(pair.first);
            if (other_pair == other.aux_rules.end()) return false;
            if (!other_pair->second->operator==(*pair.second)) return false;
        }
        
        return true;
    }
    
    bool Grammar::has_definition(const rules::Symbol &symbol) const {
        return rule(symbol).get() != nullptr;
    }
    
    ostream& operator<<(ostream &stream, const Grammar &grammar) {
        stream << string("#<grammar");

        stream << string(" rules: {");
        bool started = false;
        for (auto pair : grammar.rules) {
            if (started) stream << string(", ");
            stream << pair.first;
            stream << string(" => ");
            stream << pair.second;
            started = true;
        }
        stream << string("}");

        stream << string(" aux_rules: {");
        started = false;
        for (auto pair : grammar.aux_rules) {
            if (started) stream << string(", ");
            stream << pair.first;
            stream << string(" => ");
            stream << pair.second;
            started = true;
        }
        stream << string("}");

        return stream << string(">");
    }
}
