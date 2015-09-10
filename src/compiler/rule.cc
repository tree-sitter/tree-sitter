#include "compiler/rule.h"
#include <set>

namespace tree_sitter {

using std::ostream;
using std::string;

bool Rule::operator!=(const Rule &other) const {
  return !this->operator==(other);
}

Rule::~Rule() {}

}  // namespace tree_sitter
