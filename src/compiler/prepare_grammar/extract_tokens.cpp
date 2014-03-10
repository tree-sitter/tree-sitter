#include "extract_tokens.h"
#include "tree_sitter/compiler.h"
#include "prepared_grammar.h"
#include "rules/visitor.h"
#include "rules/seq.h"
#include "rules/choice.h"
#include "rules/repeat.h"
#include "rules/blank.h"
#include "rules/symbol.h"
#include "rules/string.h"
#include "rules/pattern.h"
#include <map>

namespace tree_sitter {
    using std::pair;
    using std::string;
    using std::to_string;
    using std::map;
    using std::make_shared;
    using namespace rules;

    namespace prepare_grammar {
        class IsToken : public RuleFn<bool> {
            void default_visit(const Rule *rule) {
                value = false;
            }

            void visit(const String *rule) {
                value = true;
            }

            void visit(const Pattern *rule) {
                value = true;
            }
        };

        class TokenExtractor : public RuleFn<rule_ptr> {
            string add_token(const rule_ptr &rule) {
                for (auto pair : tokens)
                    if (*pair.second == *rule)
                        return pair.first;
                string name = "token" + to_string(tokens.size() + 1);
                tokens.insert({ name, rule });
                return name;
            }

            void default_visit(const Rule *rule) {
                auto result = rule->copy();
                if (IsToken().apply(result)) {
                    value = make_shared<Symbol>(add_token(result), SymbolTypeAuxiliary);
                } else {
                    value = result;
                }
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

        public:
            map<const string, const rule_ptr> tokens;
        };

        pair<PreparedGrammar, PreparedGrammar> extract_tokens(const PreparedGrammar &input_grammar) {
            map<const string, const rule_ptr> rules, tokens, aux_rules, aux_tokens;
            TokenExtractor extractor;

            for (auto &pair : input_grammar.rules) {
                string name = pair.first;
                rule_ptr rule = pair.second;
                if (IsToken().apply(rule))
                    tokens.insert({ name, rule });
                else
                    rules.insert({ name, extractor.apply(rule) });
            }

            for (auto &pair : input_grammar.aux_rules) {
                string name = pair.first;
                rule_ptr rule = pair.second;
                if (IsToken().apply(rule))
                    aux_tokens.insert({ name, rule });
                else
                    aux_rules.insert({ name, extractor.apply(rule) });
            }

            aux_tokens.insert(extractor.tokens.begin(), extractor.tokens.end());

            return {
                PreparedGrammar(input_grammar.start_rule_name, rules, aux_rules),
                PreparedGrammar("", tokens, aux_tokens)
            };
        }
    }
}
