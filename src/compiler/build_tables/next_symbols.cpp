#include "next_symbols.h"
#include "rule_transitions.h"
#include "grammar.h"
#include <vector>

using std::set;
using std::vector;
using std::dynamic_pointer_cast;
using namespace tree_sitter::rules;

namespace tree_sitter {
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
                    value = apply(grammar.rule(rule->name), grammar);
                } else {
                    value = set<Symbol>({ *rule });
                }
            }
            
            void visit(const Choice *rule) {
                value = set_union(apply(rule->left, grammar), apply(rule->right, grammar));
            }
            
            void visit(const Seq *rule) {
                value = apply(rule->left, grammar);
            }

        public:
            static set<Symbol> apply(const rule_ptr rule, const Grammar &grammar) {
                FirstSetVisitor visitor(grammar);
                rule->accept(visitor);
                return visitor.value;
            }
        };
        
        template<bool isTerminal>
        set<rules::Symbol> next_symbols(const rules::rule_ptr &rule, const Grammar &grammar) {
            set<rules::Symbol> result;
            for (auto pair : rule_transitions(rule)) {
                auto symbol = dynamic_pointer_cast<const rules::Symbol>(pair.first);
                if (symbol && (grammar.has_definition(*symbol) == !isTerminal))
                    result.insert(*symbol);
            }
            return result;
        }
        
        set<rules::Symbol> next_terminals(const rules::rule_ptr &rule, const Grammar &grammar) {
            return FirstSetVisitor::apply(rule, grammar);
        }

        set<rules::Symbol> next_non_terminals(const rules::rule_ptr &rule, const Grammar &grammar) {
            return next_symbols<false>(rule, grammar);
        }

        set<rules::Symbol> next_terminals(const ParseItem &item, const Grammar &grammar) {
            return next_terminals(item.rule, grammar);
        }

        set<rules::Symbol> next_non_terminals(const ParseItem &item, const Grammar &grammar) {
            return next_non_terminals(item.rule, grammar);
        }

        set<rules::Symbol> next_terminals(const ParseItemSet &item_set, const Grammar &grammar) {
            set<rules::Symbol> result;
            for (auto item : item_set)
                for (rules::Symbol symbol : next_terminals(item, grammar))
                    result.insert(symbol);
            return result;
        }
    }
}