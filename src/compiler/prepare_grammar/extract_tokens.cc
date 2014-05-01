#include "compiler/prepare_grammar/extract_tokens.h"
#include <map>
#include <vector>
#include <string>
#include "tree_sitter/compiler.h"
#include "compiler/prepared_grammar.h"
#include "compiler/rules/visitor.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/choice.h"
#include "compiler/rules/repeat.h"
#include "compiler/rules/blank.h"
#include "compiler/rules/symbol.h"
#include "compiler/rules/string.h"
#include "compiler/rules/metadata.h"
#include "compiler/rules/pattern.h"

namespace tree_sitter {
    using std::pair;
    using std::string;
    using std::map;
    using std::to_string;
    using std::vector;
    using std::make_shared;
    using rules::rule_ptr;
    using rules::Symbol;
    using std::dynamic_pointer_cast;

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
                auto replacement_pair = replacements.find(*rule);
                if (replacement_pair != replacements.end())
                    return replacement_pair->second.copy();
                else if (rule->is_built_in())
                    return rule->copy();
                else
                    return make_shared<Symbol>(new_index_for_symbol(*rule), rule->options);
            }

        public:
            SymbolInliner(const map<Symbol, Symbol> &replacements, size_t rule_count, size_t aux_rule_count) :
                replacements(replacements)
                {}
        };

        class TokenExtractor : public rules::IdentityRuleFn {
            size_t add_token(rule_ptr rule) {
                for (size_t i = 0; i < tokens.size(); i++)
                    if (tokens[i].second->operator==(*rule))
                        return i;
                size_t index = tokens.size();
                tokens.push_back({ "token" + to_string(index), rule });
                return index;
            }

            rule_ptr apply_to_token(const rules::rule_ptr rule) {
                size_t index = add_token(rule);
                return make_shared<rules::Symbol>(index, rules::SymbolOption(rules::SymbolOptionToken|rules::SymbolOptionAuxiliary));
            }

            rule_ptr default_apply(const rules::Rule *rule) {
                auto result = rule->copy();
                if (IsToken().apply(result)) {
                    return apply_to_token(result);
                } else {
                    return result;
                }
            }

            rule_ptr apply_to(const rules::Metadata *rule) {
                if (rule->value_for(rules::IS_TOKEN)) {
                    return apply_to_token(rule->copy());
                } else {
                    return make_shared<rules::Metadata>(apply(rule->rule), rule->value);
                }
            }

        public:
            vector<pair<string, rule_ptr>> tokens;
        };

        pair<PreparedGrammar, PreparedGrammar> extract_tokens(const PreparedGrammar &input_grammar) {
            vector<pair<string, rule_ptr>> rules, tokens, aux_rules, aux_tokens;
            TokenExtractor extractor;
            map<Symbol, Symbol> symbol_replacements;

            for (size_t i = 0; i < input_grammar.rules.size(); i++) {
                auto pair = input_grammar.rules[i];
                if (IsToken().apply(pair.second)) {
                    tokens.push_back(pair);
                    symbol_replacements.insert({
                        Symbol(i),
                        Symbol(tokens.size() - 1, rules::SymbolOption(rules::SymbolOptionToken))
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

            SymbolInliner inliner(symbol_replacements, input_grammar.rules.size(), input_grammar.aux_rules.size());
            for (auto &pair : rules)
                pair.second = inliner.apply(pair.second);
            for (auto &pair : aux_rules)
                pair.second = inliner.apply(pair.second);

            return {
                PreparedGrammar(rules, aux_rules),
                PreparedGrammar(tokens, aux_tokens)
            };
        }
    }
}
