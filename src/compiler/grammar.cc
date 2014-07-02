#include "tree_sitter/compiler.h"
#include "compiler/rules/rule.h"

namespace tree_sitter {
    using std::ostream;
    using std::pair;
    using std::set;
    using std::string;
    using std::vector;
    using rules::rule_ptr;

    Grammar::Grammar(const std::vector<std::pair<std::string, rules::rule_ptr>> &rules) :
        rules_(rules),
        ubiquitous_tokens_({}),
        separators_({ ' ', '\r', '\t', '\n' }) {}

    bool Grammar::operator==(const Grammar &other) const {
        if (other.rules_.size() != rules_.size()) return false;

        for (size_t i = 0; i < rules_.size(); i++) {
            auto &pair = rules_[i];
            auto &other_pair = other.rules_[i];
            if (other_pair.first != pair.first) return false;
            if (!other_pair.second->operator==(*pair.second)) return false;
        }

        return true;
    }

    string Grammar::start_rule_name() const {
        return rules_.front().first;
    }

    ostream& operator<<(ostream &stream, const Grammar &grammar) {
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
        return stream << string("}>");
    }

    GrammarError::GrammarError(GrammarErrorType type, std::string message) :
        type(type),
        message(message) {}

    bool GrammarError::operator==(const GrammarError &other) const {
        return type == other.type && message == other.message;
    }

    ostream& operator<<(ostream &stream, const GrammarError *error) {
        if (error)
            return stream << (string("#<grammar-error '") + error->message + "'>");
        else
            return stream << string("#<null>");
    }

    const set<string> & Grammar::ubiquitous_tokens() const {
        return ubiquitous_tokens_;
    }

    Grammar & Grammar::ubiquitous_tokens(const set<string> &ubiquitous_tokens) {
        ubiquitous_tokens_ = ubiquitous_tokens;
        return *this;
    }

    const set<char> & Grammar::separators() const {
        return separators_;
    }

    Grammar & Grammar::separators(const set<char> &separators) {
        separators_ = separators;
        return *this;
    }

    const vector<pair<string, rule_ptr>> & Grammar::rules() const {
        return rules_;
    }
}
