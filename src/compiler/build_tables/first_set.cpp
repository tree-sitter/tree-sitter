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
            
            bool can_be_blank(const rule_ptr &rule) {
                if (rule_can_be_blank(rule)) return true;
                auto symbol = std::dynamic_pointer_cast<const Symbol>(rule);
                return (symbol.get() && grammar.has_definition(*symbol) && rule_can_be_blank(grammar.rule(*symbol)));
            }
            
            void visit(const Seq *rule) {
                value = apply(rule->left, grammar);
                if (can_be_blank(rule->left)) {
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