#ifndef COMPILER_RULES_BUILT_IN_SYMBOLS_H_
#define COMPILER_RULES_BUILT_IN_SYMBOLS_H_

#include "compiler/rules/interned_symbol.h"

namespace tree_sitter {
    namespace rules {
        ISymbol ERROR();
        ISymbol START();
        ISymbol END_OF_INPUT();
    }
}

#endif  // COMPILER_RULES_BUILT_IN_SYMBOLS_H_
