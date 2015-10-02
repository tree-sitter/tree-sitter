#include "compiler/variable.h"
#include <string>

namespace tree_sitter {

using std::string;

Variable::Variable(const string &name, VariableType type, const rule_ptr &rule)
    : name(name), rule(rule), type(type) {}

}  // namespace tree_sitter
