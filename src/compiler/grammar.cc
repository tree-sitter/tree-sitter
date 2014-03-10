#include "tree_sitter/compiler.h"
#include "compiler/rules/rule.h"

namespace tree_sitter {
    using std::string;
    using std::map;
    using std::ostream;
    using rules::rule_ptr;

    Grammar::Grammar(std::string start_rule_name, const map<const string, const rule_ptr> &rules) :
        start_rule_name(start_rule_name),
        rules(rules) {}

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
        return stream << string("}>");
    }
}
