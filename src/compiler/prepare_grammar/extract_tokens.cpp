#include "extract_tokens.h"
#include "search_for_symbols.h"
#include "tree_sitter/compiler.h"
#include "prepared_grammar.h"
#include "rules/visitor.h"
#include "rules/seq.h"
#include "rules/choice.h"
#include "rules/repeat.h"
#include "rules/blank.h"
#include "rules/symbol.h"
#include <map>

namespace tree_sitter {
    using std::pair;
    using std::string;
    using std::to_string;
    using std::map;
    using std::make_shared;
    using namespace rules;

    namespace prepare_grammar {
        class TokenExtractor : Visitor {
        public:
            rule_ptr value;
            map<const string, const rule_ptr> tokens;
            
            rule_ptr initial_apply(const rule_ptr rule) {
                if (!search_for_symbols(rule)) {
                    return rule_ptr();
                } else {
                    return apply(rule);
                }
            }
            
            rule_ptr apply(const rule_ptr rule) {
                if (search_for_symbols(rule) || rule->operator==(Blank())) {
                    rule->accept(*this);
                    return value;
                } else {
                    string token_name = add_token(rule);
                    return make_shared<Symbol>(token_name, SymbolTypeAuxiliary);
                }
            }
            
            string add_token(const rule_ptr &rule) {
                for (auto pair : tokens)
                    if (*pair.second == *rule)
                        return pair.first;
                string name = "token" + to_string(tokens.size() + 1);
                tokens.insert({ name, rule });
                return name;
            }
            
            void default_visit(const Rule *rule) {
                value = rule->copy();
            }
            
            void visit(const Choice *rule) {
                value = Choice::Build({ apply(rule->left), apply(rule->right) });
            }
            
            void visit(const Seq *rule) {
                value = Seq::Build({ apply(rule->left), apply(rule->right) });
            }
            
            void visit(const Repeat *rule) {
                value = make_shared<Repeat>(apply(rule->content));
            }
        };
        
        pair<PreparedGrammar, PreparedGrammar> extract_tokens(const PreparedGrammar &input_grammar) {
            TokenExtractor extractor;
            map<const string, const rule_ptr> rules;
            map<const string, const rule_ptr> tokens;
            map<const string, const rule_ptr> aux_rules;
            map<const string, const rule_ptr> aux_tokens;
            
            for (auto pair : input_grammar.rules) {
                string name = pair.first;
                rule_ptr rule = pair.second;
                rule_ptr new_rule = extractor.initial_apply(rule);
                if (new_rule.get())
                    rules.insert({ name, new_rule });
                else
                    tokens.insert({ name, rule });
            }

            for (auto pair : input_grammar.aux_rules) {
                string name = pair.first;
                rule_ptr rule = pair.second;
                rule_ptr new_rule = extractor.initial_apply(rule);
                if (new_rule.get())
                    aux_rules.insert({ name, new_rule });
                else
                    aux_tokens.insert({ name, rule });
            }
            
            aux_tokens.insert(extractor.tokens.begin(), extractor.tokens.end());
            
            return { 
                PreparedGrammar(input_grammar.start_rule_name, rules, aux_rules),
                PreparedGrammar("", tokens, aux_tokens)
            };
        }
    }
}
