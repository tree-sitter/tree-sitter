#include "extract_tokens.h"
#include "search_for_symbols.h"
#include <unordered_map>

using std::pair;
using std::string;
using std::to_string;
using std::unordered_map;

namespace tree_sitter {
    namespace prepare_grammar {
        class TokenExtractor : rules::Visitor {
        public:
            rules::rule_ptr value;
            size_t anonymous_token_count = 0;
            unordered_map<string, const rules::rule_ptr> tokens;
            
            rules::rule_ptr initial_apply(string name, const rules::rule_ptr rule) {
                auto result = apply(rule);
                auto symbol = std::dynamic_pointer_cast<const rules::Symbol>(result);
                if (symbol && *symbol != *rule) {
                    tokens.insert({ name, tokens[symbol->name] });
                    tokens.erase(symbol->name);
                    anonymous_token_count--;
                    return rules::rule_ptr();
                } else {
                    return result;
                }
            }
            
            rules::rule_ptr apply(const rules::rule_ptr rule) {
                if (search_for_symbols(rule)) {
                    rule->accept(*this);
                    return value;
                } else {
                    string token_name = add_token(rule);
                    return rules::sym(token_name);
                }
            }
            
            string add_token(const rules::rule_ptr &rule) {
                for (auto pair : tokens)
                    if (*pair.second == *rule)
                        return pair.first;
                string name = to_string(++anonymous_token_count);
                tokens.insert({ name, rule });
                return name;
            }
            
            void default_visit(const rules::Rule *rule) {
                value = rule->copy();
            }
            
            void visit(const rules::Choice *choice) {
                value = rules::choice({ apply(choice->left), apply(choice->right) });
            }
            
            void visit(const rules::Seq *seq) {
                value = rules::seq({ apply(seq->left), apply(seq->right) });
            }
        };
        
        pair<Grammar, Grammar> extract_tokens(const Grammar &input_grammar) {
            TokenExtractor extractor;
            unordered_map<string, const rules::rule_ptr> rules;
            
            for (auto pair : input_grammar.rules) {
                string name = pair.first;
                auto new_rule = extractor.initial_apply(name, pair.second);
                if (new_rule.get())
                    rules.insert({ name, new_rule });
            }
            
            return { 
                Grammar(input_grammar.start_rule_name, rules),
                Grammar("", extractor.tokens)
            };
        }
    }
}
