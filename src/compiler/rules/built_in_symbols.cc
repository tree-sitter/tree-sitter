#include "compiler/rules/built_in_symbols.h"

namespace tree_sitter {
namespace rules {

Symbol END_OF_INPUT() {
  return Symbol(-1, true);
}

Symbol ERROR() {
  return Symbol(-2, true);
}

Symbol START() {
  return Symbol(-3);
}

Symbol NONE() {
  return Symbol(-4);
}

}  // namespace rules
}  // namespace tree_sitter
