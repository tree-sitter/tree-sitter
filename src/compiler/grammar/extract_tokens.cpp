#include "extract_tokens.h"
#include "search_for_symbols.h"
#include <unordered_map>

using std::pair;
using std::string;
using std::to_string;
using std::unordered_map;

namespace tree_sitter {
    class TokenExtractor : rules::Visitor {
    public:
        rules::rule_ptr value;
        unordered_map<string, const rules::rule_ptr> tokens;

        rules::rule_ptr apply(const rules::rule_ptr rule) {
            if (search_for_symbols(rule)) {
                rule->accept(*this);
                return value;
            } else {
                string token_name = add_token(rule);
                return rules::token(token_name);
            }
        }
        
        string add_token(const rules::rule_ptr &rule) {
            string name = to_string(tokens.size() + 1);
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
            rules.insert({ pair.first, extractor.apply(pair.second) });
        }
        
        return { 
            Grammar(input_grammar.start_rule_name, rules),
            Grammar("", extractor.tokens)
        };
    }
}
