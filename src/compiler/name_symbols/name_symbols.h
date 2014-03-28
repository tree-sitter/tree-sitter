#ifndef COMPILER_NAME_SYMBOLS_NAME_SYMBOLS_H_
#define COMPILER_NAME_SYMBOLS_NAME_SYMBOLS_H_

#include <map>
#include <set>
#include <string>
#include "compiler/rules/symbol.h"

namespace tree_sitter {
    class PreparedGrammar;

    namespace name_symbols {
        std::map<rules::Symbol, std::string> name_symbols(const std::set<rules::Symbol> &symbols,
                                                          const PreparedGrammar &lexical_grammar);
    }
}

#endif  // COMPILER_NAME_SYMBOLS_NAME_SYMBOLS_H_
