#include "compiler/rules/choice.h"
#include "compiler/rule.h"

namespace tree_sitter {
namespace rules {

bool Choice::operator==(const Choice &other) const {
  return elements == other.elements;
}

}  // namespace rules
}  // namespace tree_sitter
