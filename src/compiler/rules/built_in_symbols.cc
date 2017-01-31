#include "compiler/rules/built_in_symbols.h"

namespace tree_sitter {
namespace rules {

Symbol END_OF_INPUT() {
  return Symbol(-1, Symbol::Terminal);
}

Symbol START() {
  return Symbol(-2, Symbol::NonTerminal);
}

Symbol NONE() {
  return Symbol(-3, Symbol::Type(-1));
}

}  // namespace rules
}  // namespace tree_sitter
