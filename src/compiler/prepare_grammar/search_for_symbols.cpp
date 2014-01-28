#include "search_for_symbols.h"

namespace tree_sitter {
    namespace prepare_grammar {
        class SymbolSearcher : rules::Visitor {
        public:
            bool value;
            
            bool apply(const rules::rule_ptr rule) {
                rule->accept(*this);
                return value;
            }
            
            void default_visit(const rules::Rule *rule) {
                value = false;
            }
            
            void visit(const rules::Symbol *symbol) {
                value = true;
            }
            
            void visit(const rules::Choice *choice) {
                value = apply(choice->left) || apply(choice->right);
            }
            
            void visit(const rules::Seq *seq) {
                value = apply(seq->left) || apply(seq->right);
            }
            
            void visit(const rules::Repeat *rule) {
                value = apply(rule->content);
            }
        };
        
        bool search_for_symbols(const rules::rule_ptr &rule) {
            return SymbolSearcher().apply(rule);
        }
    }
}