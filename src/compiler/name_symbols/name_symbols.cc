#include "compiler/name_symbols/name_symbols.h"
#include "compiler/prepared_grammar.h"
#include "compiler/rules/rule.h"
#include "compiler/rules/visitor.h"
#include "compiler/rules/pattern.h"
#include "compiler/rules/string.h"
#include "compiler/util/string_helpers.h"
#include "compiler/rules/built_in_symbols.h"

namespace tree_sitter {
    namespace name_symbols {
        using std::map;
        using std::set;
        using std::string;
        using rules::Symbol;
        using rules::SymbolTypeNormal;
        using rules::SymbolTypeAuxiliary;

        class TokenName : public rules::RuleFn<string> {
        protected:
            string apply_to(const rules::Pattern *rule) {
                return "/" + util::escape_string(rule->value) + "/";
            }

            string apply_to(const rules::String *rule) {
                return "'" + util::escape_string(rule->value) + "'";
            }
        };

        map<rules::Symbol, string> name_symbols(const PreparedGrammar &syntactic_grammar,
                                                const PreparedGrammar &lexical_grammar) {
            map<rules::Symbol, string> result;

            for (const auto &pair : syntactic_grammar.rules)
                result.insert({ Symbol(pair.first, SymbolTypeNormal), pair.first });
            for (const auto &pair : lexical_grammar.rules)
                result.insert({ Symbol(pair.first, SymbolTypeNormal), pair.first });
            for (const auto &pair : syntactic_grammar.aux_rules)
                result.insert({ Symbol(pair.first, SymbolTypeAuxiliary), pair.first });
            for (const auto &pair : lexical_grammar.aux_rules)
                result.insert({
                    Symbol(pair.first, SymbolTypeAuxiliary),
                    TokenName().apply(pair.second)
                });
            
            result.insert({ rules::END_OF_INPUT(), "EOF" });
            result.insert({ rules::ERROR(), "ERROR" });

            return result;
        }
    }
}
