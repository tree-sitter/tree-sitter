#include "compiler/prepared_grammar.h"
#include <vector>
#include <string>
#include <utility>
#include "compiler/rules/symbol.h"

namespace tree_sitter {
    using std::string;
    using std::pair;
    using std::ostream;
    using rules::rule_ptr;
    using rules::Symbol;

    PreparedGrammar::PreparedGrammar(const std::vector<std::pair<std::string, rules::rule_ptr>> &rules,
                                     const std::vector<std::pair<std::string, rules::rule_ptr>> &aux_rules) :
        Grammar(rules),
        aux_rules(aux_rules) {}

    PreparedGrammar::PreparedGrammar(const Grammar &grammar) :
        Grammar(grammar),
        aux_rules({}) {}

    const rule_ptr & PreparedGrammar::rule(const Symbol &symbol) const {
        return symbol.is_auxiliary() ?
            aux_rules[symbol.index].second :
            rules[symbol.index].second;
    }

    const string & PreparedGrammar::rule_name(const Symbol &symbol) const {
        return symbol.is_auxiliary() ?
            aux_rules[symbol.index].first :
            rules[symbol.index].first;
    }

    bool PreparedGrammar::operator==(const PreparedGrammar &other) const {
        if (!Grammar::operator==(other)) return false;
        if (other.aux_rules.size() != aux_rules.size()) return false;
        for (size_t i = 0; i < aux_rules.size(); i++) {
            auto &pair = aux_rules[i];
            auto &other_pair = other.aux_rules[i];
            if (other_pair.first != pair.first) return false;
            if (!other_pair.second->operator==(*pair.second)) return false;
        }
        return true;
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