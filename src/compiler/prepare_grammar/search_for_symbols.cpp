#include "search_for_symbols.h"
#include "rules/visitor.h"
#include "rules/choice.h"
#include "rules/seq.h"
#include "rules/repeat.h"

namespace tree_sitter {
    using namespace rules;
    
    namespace prepare_grammar {
        class SymbolSearcher :  rules::Visitor {
        public:
            bool value;
            
            bool apply(const rule_ptr rule) {
                rule->accept(*this);
                return value;
            }
            
            void default_visit(const Rule *rule) {
                value = false;
            }
            
            void visit(const Symbol *symbol) {
                value = true;
            }
            
            void visit(const Choice *choice) {
                value = apply(choice->left) || apply(choice->right);
            }
            
            void visit(const Seq *seq) {
                value = apply(seq->left) || apply(seq->right);
            }
            
            void visit(const Repeat *rule) {
                value = apply(rule->content);
            }
        };
        
        bool search_for_symbols(const rule_ptr &rule) {
            return SymbolSearcher().apply(rule);
        }
    }
}