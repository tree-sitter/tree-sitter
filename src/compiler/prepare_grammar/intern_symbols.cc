#include "compiler/prepare_grammar/intern_symbols.h"
#include <memory>
#include <vector>
#include <set>
#include "tree_sitter/compiler.h"
#include "compiler/prepare_grammar/interned_grammar.h"
#include "compiler/prepared_grammar.h"
#include "compiler/rules/visitor.h"
#include "compiler/rules/named_symbol.h"
#include "compiler/rules/symbol.h"

namespace tree_sitter {
    using std::string;
    using rules::rule_ptr;
    using std::vector;
    using std::set;
    using std::pair;
    using std::make_shared;

    namespace prepare_grammar {
        class InternSymbols : public rules::IdentityRuleFn {
            using rules::IdentityRuleFn::apply_to;

            rule_ptr apply_to(const rules::NamedSymbol *rule)  {
                auto result = symbol_for_rule_name(rule->name);
                if (!result.get()) missing_rule_name = rule->name;
                return result;
            }

        public:
            std::shared_ptr<rules::Symbol> symbol_for_rule_name(string rule_name) {
                for (size_t i = 0; i < grammar.rules().size(); i++)
                    if (grammar.rules()[i].first == rule_name)
                        return make_shared<rules::Symbol>(i);
                return nullptr;
            }

            explicit InternSymbols(const Grammar &grammar) : grammar(grammar) {}
            const Grammar grammar;
            string missing_rule_name;
        };

        pair<InternedGrammar, const GrammarError *> missing_rule_error(string rule_name) {
            InternedGrammar grammar;
            return {
                grammar,
                new GrammarError(GrammarErrorTypeUndefinedSymbol,
                                 "Undefined rule '" + rule_name + "'")
            };
        }

        pair<InternedGrammar, const GrammarError *> intern_symbols(const Grammar &grammar) {
            InternSymbols interner(grammar);
            vector<pair<string, rule_ptr>> rules;

            for (auto &pair : grammar.rules()) {
                auto new_rule = interner.apply(pair.second);
                if (!interner.missing_rule_name.empty())
                    return missing_rule_error(interner.missing_rule_name);
                rules.push_back({ pair.first, new_rule });
            }

            set<rules::Symbol> ubiquitous_tokens;
            for (auto &name : grammar.ubiquitous_tokens()) {
                auto token = interner.symbol_for_rule_name(name);
                if (!token.get())
                    return missing_rule_error(name);
                ubiquitous_tokens.insert(*token);
            }

            InternedGrammar result;
            result.rules = rules;
            result.ubiquitous_tokens = ubiquitous_tokens;
            result.separators = grammar.separators();

            return { result, nullptr };
        }
    }
}
