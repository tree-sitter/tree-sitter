#include "tree_sitter/compiler.h"
#include "./rule.h"
#include "./blank.h"
#include "./symbol.h"
#include "./choice.h"
#include "./seq.h"
#include "./string.h"
#include "./pattern.h"
#include "./character_set.h"
#include "./repeat.h"
#include "./built_in_symbols.h"

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

        rule_ptr _sym(const string &name) {
            return make_shared<Symbol>(name, SymbolTypeHidden);
        }

        rule_ptr pattern(const string &value) {
            return make_shared<Pattern>(value);
        }

        rule_ptr str(const string &value) {
            return make_shared<String>(value);
        }

        rule_ptr err(const rule_ptr &rule) {
            return choice({ rule, ERROR.copy() });
        }
    }
}
