#include "compiler/lexical_grammar.h"

namespace tree_sitter {

using std::string;

LexicalVariable::LexicalVariable(
  const string &name, VariableType type, const rule_ptr &rule, bool is_string)
    : name(name), rule(rule), type(type), is_string(is_string) {}

}  // namespace tree_sitter
