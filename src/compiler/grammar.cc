#include "compiler/grammar.h"
#include <string>

namespace tree_sitter {

using std::string;

Variable::Variable(const string &name, VariableType type, const rule_ptr &rule)
    : internal_name(name), external_name(name), rule(rule), type(type) {}

Variable::Variable(const string &internal_name, const string &external_name,
                   VariableType type, const rule_ptr &rule)
    : internal_name(internal_name),
      external_name(external_name),
      rule(rule),
      type(type) {}

}  // namespace tree_sitter
