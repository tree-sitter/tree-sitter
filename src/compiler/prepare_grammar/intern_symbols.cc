#include "compiler/prepare_grammar/intern_symbols.h"
#include <memory>
#include "tree_sitter/compiler.h"
#include "compiler/prepared_grammar.h"
#include "compiler/rules/visitor.h"
#include "compiler/rules/symbol.h"
#include "compiler/rules/interned_symbol.h"

namespace tree_sitter {
    using std::string;
    using rules::rule_ptr;
    using std::vector;
    using std::pair;
    using std::make_shared;
    using std::exception;

    GrammarError::GrammarError(string rule_name) : rule_name(rule_name) {}
        
    string GrammarError::message() const {
        return "Undefined rule '" + rule_name + "'";
    }
        
    namespace prepare_grammar {
        class InternSymbols : public rules::IdentityRuleFn {
            const Grammar grammar;
            using rules::IdentityRuleFn::apply_to;
            
            long index_of(string rule_name) {
                for (size_t i = 0; i < grammar.rules.size(); i++)
                    if (grammar.rules[i].first == rule_name)
                        return i;
                return -1;
            }
            
            rule_ptr apply_to(const rules::Symbol *rule)  {
                long index = index_of(rule->name);
                if (index == -1)
                    missing_rule_name = rule->name;
                return make_shared<rules::ISymbol>(index);
            }

        public:
            InternSymbols(const Grammar &grammar) : grammar(grammar) {}

            string missing_rule_name;
        };
        
        pair<PreparedGrammar, const GrammarError *> intern_symbols(const Grammar &grammar) {
            InternSymbols interner(grammar);
            vector<pair<string, rule_ptr>> rules;

            for (auto &pair : grammar.rules) {
                auto new_rule = interner.apply(pair.second);
                if (!interner.missing_rule_name.empty())
                    return {
                        PreparedGrammar(rules),
                        new GrammarError(interner.missing_rule_name)
                    };
                rules.push_back({ pair.first, new_rule });
            }
            
            return { PreparedGrammar(rules), nullptr };
        }
    }
}
