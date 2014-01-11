#ifndef __tree_sitter__compile__
#define __tree_sitter__compile__

#include <string>

namespace tree_sitter {
    class Grammar;

    std::string compile(const Grammar &grammar);
}

#endif
