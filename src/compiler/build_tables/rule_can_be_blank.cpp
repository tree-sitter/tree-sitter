#include "rule_can_be_blank.h"
#include "tree_sitter/compiler.h"
#include "prepared_grammar.h"
#include "rules/symbol.h"
#include "rules/visitor.h"
#include "rules/seq.h"
#include "rules/choice.h"
#include "rules/blank.h"

namespace tree_sitter  {
    using namespace rules;

    namespace build_tables {
        class EpsilonVisitor : public rules::Visitor {
        public:
            bool value;
            
            void default_visit(const Rule *) {
                value = false;
            }
            
            void visit(const Blank *) {
                value = true;
            }
            
            void visit(const Choice *rule) {
                value = rule_can_be_blank(rule->left) || rule_can_be_blank(rule->right);
            }
            
            void visit(const Seq *rule) {
                value = rule_can_be_blank(rule->left) && rule_can_be_blank(rule->right);
            }
            
            void visit(const Repeat *rule) {
                value = true;
            }
        };
        
        bool rule_can_be_blank(const rule_ptr &rule) {
            EpsilonVisitor visitor;
            rule->accept(visitor);
            return visitor.value;
        }
        
        bool rule_can_be_blank(const rule_ptr &rule, const PreparedGrammar &grammar) {
            if (rule_can_be_blank(rule)) return true;
            auto symbol = std::dynamic_pointer_cast<const Symbol>(rule);
            return (symbol.get() && grammar.has_definition(*symbol) && rule_can_be_blank(grammar.rule(*symbol), grammar));
        }
    }
}
