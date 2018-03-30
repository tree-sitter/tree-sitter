#include "compiler/prepare_grammar/expand_tokens.h"
#include <vector>
#include <string>
#include <utility>
#include "compiler/lexical_grammar.h"
#include "compiler/rule.h"
#include "compiler/prepare_grammar/parse_regex.h"
#include "utf8proc.h"

namespace tree_sitter {
namespace prepare_grammar {

using std::string;
using std::vector;
using rules::Rule;

ExpandTokenResult expand_token(const rules::Rule &rule) {
  return rule.match(
    [](const rules::Blank &blank) -> ExpandTokenResult { return Rule(blank); },

    [](const rules::String &string) {
      vector<Rule> elements;
      const uint8_t *iter = reinterpret_cast<const uint8_t *>(string.value.data());
      const uint8_t *end = iter + string.value.size();

      while (iter < end) {
        int32_t el;
        size_t size = utf8proc_iterate(iter, (end - iter), &el);
        if (!size)
          break;
        iter += size;

        elements.push_back(rules::CharacterSet().include(el));
      }

      return Rule::seq(elements);
    },

    [](const rules::Pattern &pattern) -> ExpandTokenResult {
      auto result = parse_regex(pattern.value);
      if (result.second) return result.second;
      return result.first;
    },

    [](const rules::Repeat &rule) -> ExpandTokenResult {
      auto result = expand_token(*rule.rule);
      if (result.error) return result.error;
      return Rule::repeat(result.rule);
    },

    [](const rules::Metadata &rule) -> ExpandTokenResult {
      auto result = expand_token(*rule.rule);
      if (result.error) return result.error;
      return Rule(rules::Metadata{result.rule, rule.params});
    },

    [](const rules::Seq &rule) -> ExpandTokenResult {
      auto left_result = expand_token(*rule.left);
      if (left_result.error) return left_result.error;
      auto right_result = expand_token(*rule.right);
      if (right_result.error) return right_result.error;
      return Rule(rules::Seq{left_result.rule, right_result.rule});
    },

    [](const rules::Choice &rule) -> ExpandTokenResult {
      std::vector<Rule> elements;
      for (const auto &element : rule.elements) {
        auto result = expand_token(element);
        if (result.error) return result.error;
        elements.push_back(result.rule);
      }
      return Rule(rules::Choice{elements});
    },

    [](auto) { return CompileError(TSCompileErrorTypeInvalidTokenContents, "Symbols inside tokens are not allowed."); }
  );
};

}  // namespace prepare_grammar
}  // namespace tree_sitter
