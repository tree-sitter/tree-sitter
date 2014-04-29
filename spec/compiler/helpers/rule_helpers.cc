#include "rule_helpers.h"
#include <memory>
#include "compiler/rules/symbol.h"

namespace tree_sitter {
    using std::make_shared;
    using std::set;

    namespace rules {
        rule_ptr character(const set<CharacterRange> &ranges) {
            return make_shared<CharacterSet>(ranges);
        }

        rule_ptr character(const set<CharacterRange> &ranges, bool sign) {
            if (sign)
                return character(ranges);
            else
                return CharacterSet(ranges).complement().copy();
        }

        rule_ptr i_sym(size_t index) {
            return make_shared<rules::Symbol>(index);
        }

        rule_ptr i_aux_sym(size_t index) {
            return make_shared<rules::Symbol>(index, SymbolOptionAuxiliary);
        }

        rule_ptr i_token(size_t index) {
            return make_shared<rules::Symbol>(index, SymbolOptionToken);
        }

        rule_ptr i_aux_token(size_t index) {
            return make_shared<rules::Symbol>(index, SymbolOption(SymbolOptionAuxiliary|SymbolOptionToken));
        }
    }
}
