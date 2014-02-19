#include "prepared_grammar.h"
#include "rules/symbol.h"

namespace tree_sitter {
    using std::string;
    using std::initializer_list;
    using std::pair;
    using std::map;
    using std::ostream;
    using rules::rule_ptr;
    using rules::Symbol;

    PreparedGrammar::PreparedGrammar(std::string start_rule_name,
                                     const map<const string, const rule_ptr> &rules,
                                     const map<const string, const rule_ptr> &aux_rules) :
        Grammar(start_rule_name, rules),
        aux_rules(aux_rules) {}
    
    PreparedGrammar::PreparedGrammar(std::string start_rule_name,
                                     const initializer_list<pair<const string, const rule_ptr>> &rules,
                                     const initializer_list<pair<const string, const rule_ptr>> &aux_rules) :
        Grammar(start_rule_name, rules),
        aux_rules(aux_rules) {}

    PreparedGrammar::PreparedGrammar(const Grammar &grammar) :
        Grammar(grammar),
        aux_rules({}) {}

    const rule_ptr PreparedGrammar::rule(const Symbol &symbol) const {
        auto map = symbol.is_auxiliary() ? aux_rules : rules;
        auto iter = map.find(symbol.name);
        if (iter != map.end())
            return iter->second;
        else
            return rule_ptr();
    }

    bool PreparedGrammar::operator==(const PreparedGrammar &other) const {
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
    
    bool PreparedGrammar::has_definition(const Symbol &symbol) const {
        return rule(symbol).get() != nullptr;
    }
    
    ostream& operator<<(ostream &stream, const PreparedGrammar &grammar) {
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