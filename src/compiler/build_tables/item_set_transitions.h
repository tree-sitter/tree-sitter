#ifndef __tree_sitter__item_set_transitions__
#define __tree_sitter__item_set_transitions__

#include <map>
#include "compiler/build_tables/item.h"

namespace tree_sitter {
    class PreparedGrammar;
    namespace rules {
        class CharacterSet;
        class Symbol;
    }

    namespace build_tables {
        std::map<rules::CharacterSet, LexItemSet> char_transitions(const LexItemSet &item_set, const PreparedGrammar &grammar);
        std::map<rules::Symbol, ParseItemSet> sym_transitions(const ParseItemSet &item_set, const PreparedGrammar &grammar);
    }
}

#endif
