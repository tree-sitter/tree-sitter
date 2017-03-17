#include "compiler/prepare_grammar/token_description.h"
#include "compiler/rule.h"
#include "compiler/util/string_helpers.h"

namespace tree_sitter {
namespace prepare_grammar {

using std::string;
using rules::Rule;

class TokenDescription {
  bool is_trivial;

  string apply(const Rule &rule) {
    return rule.match(
      [&](const rules::Blank) -> string {
        return "";
      },

      [&](const rules::Symbol) {
        return "";
      },

      [&](const rules::Pattern &rule) {
        is_trivial = false;
        return rule.value;
      },

      [&](const rules::String &rule) {
        return rule.value;
      },

      [&](const rules::Metadata &rule) {
        return apply(*rule.rule);
      },

      [&](const rules::Seq &rule) {
        is_trivial = false;
        return apply(*rule.left) + apply(*rule.right);
      },

      [&](const rules::Repeat &rule) {
        is_trivial = false;
        return apply(*rule.rule) + "+";
      },

      [&](const rules::Choice &rule) {
        is_trivial = false;
        string result = "(";
        bool started = false;
        for (auto &element : rule.elements) {
          if (started) result += "|";
          result += apply(element);
          started = true;
        }
        return result + ")";
      },

      [](auto) {
        return "";
      }
    );
  }

 public:
  string describe(const Rule &rule) {
    string result = apply(rule);
    if (is_trivial) {
      return result;
    } else {
      return "/" + result + "/";
    }
  }

  TokenDescription() : is_trivial(true) {}
};

string token_description(const Rule &rule) {
  return TokenDescription().describe(rule);
}

}  // namespace prepare_grammar
}  // namespace tree_sitter
