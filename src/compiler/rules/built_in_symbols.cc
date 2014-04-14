#include "compiler/rules/built_in_symbols.h"

namespace tree_sitter {
    namespace rules {
        Symbol ERROR() { return Symbol("error", SymbolTypeBuiltIn); }
        Symbol START() { return Symbol("start", SymbolTypeBuiltIn); }
        Symbol END_OF_INPUT() { return Symbol("end", SymbolTypeBuiltIn); }
    }
}
