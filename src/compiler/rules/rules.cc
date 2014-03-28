#include "tree_sitter/compiler.h"
#include "compiler/rules/rule.h"
#include "compiler/rules/blank.h"
#include "compiler/rules/symbol.h"
#include "compiler/rules/choice.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/string.h"
#include "compiler/rules/pattern.h"
#include "compiler/rules/character_set.h"
#include "compiler/rules/repeat.h"
#include "compiler/rules/built_in_symbols.h"

namespace tree_sitter {
    using std::make_shared;
    using std::string;
    using std::set;
    using std::vector;

    namespace rules {
        rule_ptr blank() {
            return make_shared<Blank>();
        }

        rule_ptr choice(const vector<rule_ptr> &rules) {
            return Choice::Build(rules);
        }

        rule_ptr repeat(const rule_ptr &content) {
            return std::make_shared<Repeat>(content);
        }

        rule_ptr seq(const vector<rule_ptr> &rules) {
            return Seq::Build(rules);
        }

        rule_ptr sym(const string &name) {
            return make_shared<Symbol>(name);
        }

        rule_ptr pattern(const string &value) {
            return make_shared<Pattern>(value);
        }

        rule_ptr str(const string &value) {
            return make_shared<String>(value);
        }

        rule_ptr err(const rule_ptr &rule) {
            return choice({ rule, ERROR().copy() });
        }
    }
}
