#include "compiler/build_tables/lex_item.h"
#include "compiler/build_tables/rule_can_be_blank.h"
#include "compiler/rules/symbol.h"
#include "compiler/rules/metadata.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/visitor.h"

namespace tree_sitter {
    using std::string;
    using std::ostream;
    using std::vector;

    namespace build_tables {
        LexItem::LexItem(const rules::Symbol &lhs, const rules::rule_ptr rule) :
            Item(lhs, rule) {}

        bool LexItem::operator==(const LexItem &other) const {
            return (other.lhs == lhs) && other.rule->operator==(*rule);
        }

        bool LexItem::is_token_start() const {
            class IsTokenStart : public rules::RuleFn<bool> {
                bool apply_to(const rules::Seq *rule) {
                    bool result = apply(rule->left);
                    if (!result && rule_can_be_blank(rule->left))
                        result = apply(rule->right);
                    return result;
                }

                bool apply_to(const rules::Metadata *rule) {
                    auto pair = rule->value.find(rules::START_TOKEN);
                    return (pair != rule->value.end()) && pair->second;
                }
            };

            return IsTokenStart().apply(rule);
        }

        ostream& operator<<(ostream &stream, const LexItem &item) {
            return stream <<
            string("#<item ") <<
            item.lhs <<
            string(" ") <<
            *item.rule <<
            string(">");
        }
    }
}

