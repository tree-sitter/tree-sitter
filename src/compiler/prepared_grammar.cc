#include "compiler/prepared_grammar.h"
#include <vector>
#include <string>
#include <utility>
#include "compiler/rules/symbol.h"

namespace tree_sitter {
    using std::string;
    using std::pair;
    using std::ostream;
    using std::vector;
    using rules::rule_ptr;
    using rules::Symbol;

    PreparedGrammar::PreparedGrammar() :
        rules_({}),
        aux_rules_({}),
        ubiquitous_tokens_({}) {}

    PreparedGrammar::PreparedGrammar(const std::vector<std::pair<std::string, rules::rule_ptr>> &rules,
                                     const std::vector<std::pair<std::string, rules::rule_ptr>> &aux_rules) :
        rules_(rules),
        aux_rules_(aux_rules),
        ubiquitous_tokens_({}) {}

    const rule_ptr & PreparedGrammar::rule(const Symbol &symbol) const {
        return symbol.is_auxiliary() ?
            aux_rules_[symbol.index].second :
            rules_[symbol.index].second;
    }

    const string & PreparedGrammar::rule_name(const Symbol &symbol) const {
        return symbol.is_auxiliary() ?
            aux_rules_[symbol.index].first :
            rules_[symbol.index].first;
    }

    bool PreparedGrammar::operator==(const PreparedGrammar &other) const {
        if (other.rules_.size() != rules_.size()) return false;

        for (size_t i = 0; i < rules_.size(); i++) {
            auto &pair = rules_[i];
            auto &other_pair = other.rules_[i];
            if (other_pair.first != pair.first) return false;
            if (!other_pair.second->operator==(*pair.second)) return false;
        }

        if (other.aux_rules_.size() != aux_rules_.size()) return false;
        for (size_t i = 0; i < aux_rules_
             .size(); i++) {
            auto &pair = aux_rules_[i];
            auto &other_pair = other.aux_rules_[i];
            if (other_pair.first != pair.first) return false;
            if (!other_pair.second->operator==(*pair.second)) return false;
        }

        return true;
    }

    const vector<pair<string, rule_ptr>> & PreparedGrammar::rules() const {
        return rules_;
    }

    const vector<pair<string, rule_ptr>> & PreparedGrammar::aux_rules() const {
        return aux_rules_;
    }

    const vector<Symbol> & PreparedGrammar::ubiquitous_tokens() const {
        return ubiquitous_tokens_;
    }

    const PreparedGrammar & PreparedGrammar::ubiquitous_tokens(const vector<Symbol> &ubiquitous_tokens) {
        ubiquitous_tokens_ = ubiquitous_tokens;
        return *this;
    }

    ostream& operator<<(ostream &stream, const PreparedGrammar &grammar) {
        stream << string("#<grammar");

        stream << string(" rules: {");
        bool started = false;
        for (auto pair : grammar.rules()) {
            if (started) stream << string(", ");
            stream << pair.first;
            stream << string(" => ");
            stream << pair.second;
            started = true;
        }
        stream << string("}");

        stream << string(" aux_rules: {");
        started = false;
        for (auto pair : grammar.aux_rules()) {
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
