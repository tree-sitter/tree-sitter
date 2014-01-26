#include "extract_tokens.h"
#include "search_for_symbols.h"
#include <unordered_map>

using std::pair;
using std::string;
using std::to_string;
using std::unordered_map;
using namespace tree_sitter::rules;

namespace tree_sitter {
    namespace prepare_grammar {
        class TokenExtractor : Visitor {
        public:
            rule_ptr value;
            unordered_map<string, const rule_ptr> tokens;
            
            rule_ptr initial_apply(const rule_ptr rule) {
                if (!search_for_symbols(rule)) {
                    return rule_ptr();
                } else {
                    return apply(rule);
                }
            }
            
            rule_ptr apply(const rule_ptr rule) {
                if (search_for_symbols(rule)) {
                    rule->accept(*this);
                    return value;
                } else {
                    string token_name = add_token(rule);
                    return sym(token_name);
                }
            }
            
            string add_token(const rule_ptr &rule) {
                for (auto pair : tokens)
                    if (*pair.second == *rule)
                        return pair.first;
                string name = to_string(tokens.size() + 1);
                tokens.insert({ name, rule });
                return name;
            }
            
            void default_visit(const Rule *rule) {
                value = rule->copy();
            }
            
            void visit(const Choice *rule) {
                value = choice({ apply(rule->left), apply(rule->right) });
            }
            
            void visit(const Seq *rule) {
                value = seq({ apply(rule->left), apply(rule->right) });
            }
        };
        
        pair<Grammar, Grammar> extract_tokens(const Grammar &input_grammar) {
            TokenExtractor extractor;
            unordered_map<string, const rule_ptr> rules;
            unordered_map<string, const rule_ptr> tokens;
            
            for (auto pair : input_grammar.rules) {
                string name = pair.first;
                rule_ptr rule = pair.second;
                auto new_rule = extractor.initial_apply(rule);
                if (new_rule.get())
                    rules.insert({ name, new_rule });
                else
                    tokens.insert({ name, rule });
            }
            
            for (auto pair : extractor.tokens)
                tokens.insert(pair);
            
            return { 
                Grammar(input_grammar.start_rule_name, rules),
                Grammar("", tokens)
            };
        }
    }
}
