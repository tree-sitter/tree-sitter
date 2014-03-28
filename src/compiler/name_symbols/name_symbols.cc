#include "compiler/name_symbols/name_symbols.h"
#include "compiler/prepared_grammar.h"
#include "compiler/rules/rule.h"
#include "compiler/rules/visitor.h"
#include "compiler/rules/pattern.h"
#include "compiler/rules/string.h"
#include "compiler/util/string_helpers.h"

namespace tree_sitter {
    namespace name_symbols {
        using std::map;
        using std::set;
        using std::string;

        class TokenName : public rules::RuleFn<string> {
        protected:
            virtual void visit(const rules::Pattern *rule) {
                value = "/" + util::escape_string(rule->value) + "/";
            }

            virtual void visit(const rules::String *rule) {
                value = "'" + util::escape_string(rule->value) + "'";
            }
        };

        map<rules::Symbol, string> name_symbols(const set<rules::Symbol> &symbols,
                                                const PreparedGrammar &lexical_grammar) {
            map<rules::Symbol, string> result;
            for (auto &symbol : symbols) {
                string name = (symbol.is_auxiliary() && lexical_grammar.has_definition(symbol)) ?
                    TokenName().apply(lexical_grammar.rule(symbol)) :
                    symbol.name;
                result.insert({ symbol, name });
            }
            return result;
        }
    }
}
