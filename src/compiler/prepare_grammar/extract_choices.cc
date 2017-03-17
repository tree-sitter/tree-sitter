#include "compiler/prepare_grammar/extract_choices.h"
#include <vector>
#include <memory>
#include "compiler/rule.h"

namespace tree_sitter {
namespace prepare_grammar {

using std::vector;
using rules::Rule;

vector<Rule> extract_choices(const Rule &rule) {
  return rule.match(
    [](const rules::Seq &sequence) {
      vector<Rule> result;
      for (auto &left_entry : extract_choices(*sequence.left)) {
        for (auto &right_entry : extract_choices(*sequence.right)) {
          result.push_back(rules::Rule::seq({left_entry, right_entry}));
        }
      }
      return result;
    },

    [](const rules::Metadata &rule) {
      vector<Rule> result;
      for (auto &entry : extract_choices(*rule.rule)) {
        result.push_back(rules::Metadata{entry, rule.params});
      }
      return result;
    },

    [](const rules::Choice &choice) {
      vector<Rule> result;
      for (auto &element : choice.elements) {
        for (auto &entry : extract_choices(element)) {
          result.push_back(entry);
        }
      }
      return result;
    },

    [](const auto &rule) {
      return vector<Rule>({rule});
    }
  );
}

}  // namespace prepare_grammar
}  // namespace tree_sitter
