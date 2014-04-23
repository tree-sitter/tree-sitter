#include "compiler/rules/built_in_symbols.h"

namespace tree_sitter {
    namespace rules {
        ISymbol END_OF_INPUT() { return ISymbol(-1, SymbolOptionToken); }
        ISymbol ERROR() { return ISymbol(-2, SymbolOptionToken); }
        ISymbol START() { return ISymbol(-3); }
    }
}
