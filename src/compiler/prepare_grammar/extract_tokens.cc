#include "compiler/prepare_grammar/extract_tokens.h"
#include <map>
#include <vector>
#include <string>
#include "tree_sitter/compiler.h"
#include "compiler/prepared_grammar.h"
#include "compiler/rules/visitor.h"
#include "compiler/rules/symbol.h"
#include "compiler/rules/string.h"
#include "compiler/rules/metadata.h"
#include "compiler/rules/pattern.h"
#include "compiler/prepare_grammar/token_description.h"

namespace tree_sitter {
    using std::pair;
    using std::string;
    using std::map;
    using std::to_string;
    using std::vector;
    using std::make_shared;
    using rules::rule_ptr;
    using rules::Symbol;

    namespace prepare_grammar {
        class IsToken : public rules::RuleFn<bool> {
            bool apply_to(const rules::String *rule) { return true; }
            bool apply_to(const rules::Pattern *rule) { return true; }
            bool apply_to(const rules::Metadata *rule) { return rule->value_for(rules::IS_TOKEN); }
        };

        class SymbolInliner : public rules::IdentityRuleFn {
            map<Symbol, Symbol> replacements;
            using rules::IdentityRuleFn::apply_to;

            int new_index_for_symbol(const Symbol &symbol) {
                int result = symbol.index;
                for (const auto &pair : replacements)
                    if (pair.first.index < symbol.index &&
                        pair.first.is_auxiliary() == symbol.is_auxiliary())
                        result--;
                return result;
            }

            rule_ptr apply_to(const Symbol *rule) {
                return replace_symbol(*rule).copy();
            }

        public:
            Symbol replace_symbol(const Symbol &rule) {
                if (rule.is_built_in()) return rule;
                auto replacement_pair = replacements.find(rule);
                if (replacement_pair != replacements.end())
                    return replacement_pair->second;
                else
                    return Symbol(new_index_for_symbol(rule), rule.options);
            }

            SymbolInliner(const map<Symbol, Symbol> &replacements) : replacements(replacements) {}
        };
        
        const rules::SymbolOption SymbolOptionAuxToken = rules::SymbolOption(rules::SymbolOptionToken|rules::SymbolOptionAuxiliary);

        class TokenExtractor : public rules::IdentityRuleFn {
            rule_ptr apply_to_token(const rules::Rule *input) {
                auto rule = input->copy();
                for (size_t i = 0; i < tokens.size(); i++)
                    if (tokens[i].second->operator==(*rule))
                        return make_shared<Symbol>(i, SymbolOptionAuxToken);
                size_t index = tokens.size();
                tokens.push_back({ token_description(rule), rule });
                return make_shared<Symbol>(index, SymbolOptionAuxToken);

            }
            
            rule_ptr default_apply(const rules::Rule *rule) {
                auto result = rule->copy();
                if (IsToken().apply(rule->copy())) {
                    return apply_to_token(rule);
                } else {
                    return result;
                }
            }
            
            rule_ptr apply_to(const rules::Metadata *rule) {
                auto result = rule->copy();
                if (IsToken().apply(rule->copy())) {
                    return apply_to_token(rule);
                } else {
                    return rules::IdentityRuleFn::apply_to(rule);
                }
            }

        public:
            vector<pair<string, rule_ptr>> tokens;
        };

        pair<PreparedGrammar, PreparedGrammar> extract_tokens(const PreparedGrammar &input_grammar) {
            vector<pair<string, rule_ptr>> rules, tokens, aux_rules, aux_tokens;
            vector<Symbol> ubiquitous_tokens;

            TokenExtractor extractor;
            map<Symbol, Symbol> symbol_replacements;

            for (size_t i = 0; i < input_grammar.rules.size(); i++) {
                auto pair = input_grammar.rules[i];
                if (IsToken().apply(pair.second)) {
                    tokens.push_back(pair);
                    symbol_replacements.insert({
                        Symbol(i),
                        Symbol(tokens.size() - 1, rules::SymbolOptionToken)
                    });
                } else {
                    rules.push_back({ pair.first, extractor.apply(pair.second) });
                }
            }

            for (size_t i = 0; i < input_grammar.aux_rules.size(); i++) {
                auto pair = input_grammar.aux_rules[i];
                if (IsToken().apply(pair.second)) {
                    aux_tokens.push_back(pair);
                    symbol_replacements.insert({
                        Symbol(i, rules::SymbolOptionAuxiliary),
                        Symbol(aux_tokens.size() - 1, rules::SymbolOption(rules::SymbolOptionAuxiliary|rules::SymbolOptionToken))
                    });
                } else {
                    aux_rules.push_back({ pair.first, extractor.apply(pair.second) });
                }
            }

            aux_tokens.insert(aux_tokens.end(), extractor.tokens.begin(), extractor.tokens.end());

            SymbolInliner inliner(symbol_replacements);
            for (auto &pair : rules)
                pair.second = inliner.apply(pair.second);
            for (auto &pair : aux_rules)
                pair.second = inliner.apply(pair.second);
            for (auto &symbol : input_grammar.options.ubiquitous_tokens)
                ubiquitous_tokens.push_back(inliner.replace_symbol(symbol));

            PreparedGrammarOptions parse_options(input_grammar.options);
            parse_options.ubiquitous_tokens = ubiquitous_tokens;

            return {
                PreparedGrammar(rules, aux_rules, parse_options),
                PreparedGrammar(tokens, aux_tokens)
            };
        }
    }
}
