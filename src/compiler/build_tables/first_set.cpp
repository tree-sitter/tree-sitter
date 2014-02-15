#include "first_set.h"
#include "rule_can_be_blank.h"
#include "grammar.h"


namespace tree_sitter {
    using std::set;
    using namespace rules;

    namespace build_tables {
        class FirstSetVisitor : Visitor {
            set<Symbol> value;
            const Grammar grammar;
            
            FirstSetVisitor(const Grammar &grammar) : grammar(grammar) {}
            
            set<Symbol> set_union(const set<Symbol> &left, const set<Symbol> &right) {
                set<Symbol> result = left;
                result.insert(right.begin(), right.end());
                return result;
            }
            
            void visit(const Symbol *rule) {
                if (grammar.has_definition(*rule)) {
                    value = apply(grammar.rule(*rule), grammar);
                } else {
                    value = set<Symbol>({ *rule });
                }
            }
            
            void visit(const Choice *rule) {
                value = set_union(apply(rule->left, grammar), apply(rule->right, grammar));
            }
            
            void visit(const Seq *rule) {
                value = apply(rule->left, grammar);
                if (rule_can_be_blank(rule->left, grammar)) {
                    value = set_union(value, apply(rule->right, grammar));
                }
            }

        public:
            static set<Symbol> apply(const rule_ptr rule, const Grammar &grammar) {
                FirstSetVisitor visitor(grammar);
                rule->accept(visitor);
                return visitor.value;
            }
        };
        
        set<Symbol> first_set(const rule_ptr &rule, const Grammar &grammar) {
            return FirstSetVisitor::apply(rule, grammar);
        }
    }
}