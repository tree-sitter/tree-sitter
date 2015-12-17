#include "tree_sitter/compiler.h"
#include "compiler/rule.h"

namespace tree_sitter {

using std::ostream;
using std::pair;
using std::string;
using std::vector;

Grammar::Grammar(const vector<pair<string, rule_ptr>> &rules)
    : rules_(rules), extra_tokens_({}) {}

const vector<pair<string, rule_ptr>> &Grammar::rules() const {
  return rules_;
}

const vector<rule_ptr> &Grammar::extra_tokens() const {
  return extra_tokens_;
}

const vector<vector<string>> &Grammar::expected_conflicts() const {
  return expected_conflicts_;
}

Grammar &Grammar::extra_tokens(const vector<rule_ptr> &extra_tokens) {
  extra_tokens_ = extra_tokens;
  return *this;
}

Grammar &Grammar::expected_conflicts(
  const vector<vector<string>> &expected_conflicts) {
  expected_conflicts_ = expected_conflicts;
  return *this;
}

GrammarError::GrammarError(GrammarErrorType type, string message)
    : type(type), message(message) {}

bool GrammarError::operator==(const GrammarError &other) const {
  return type == other.type && message == other.message;
}

}  // namespace tree_sitter
