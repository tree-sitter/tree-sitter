#include "built_in_symbols.h"

namespace tree_sitter {
    namespace rules {
        const Symbol ERROR("error", SymbolTypeBuiltIn);
        const Symbol START("start", SymbolTypeBuiltIn);
        const Symbol END_OF_INPUT("end", SymbolTypeBuiltIn);
    }
}