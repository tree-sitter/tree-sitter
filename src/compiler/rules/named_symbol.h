#ifndef COMPILER_RULES_NAMED_SYMBOL_H_
#define COMPILER_RULES_NAMED_SYMBOL_H_

#include <string>

namespace tree_sitter {
namespace rules {

struct NamedSymbol {
  std::string value;

  inline bool operator==(const NamedSymbol &other) const {
    return value == other.value;
  }
};

}  // namespace rules
}  // namespace tree_sitter

#endif  // COMPILER_RULES_NAMED_SYMBOL_H_