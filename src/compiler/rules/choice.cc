#include "compiler/rules/choice.h"
#include "compiler/rule.h"

namespace tree_sitter {
namespace rules {

static inline void add_choice_element(std::vector<Rule> *elements, const Rule &new_rule) {
  new_rule.match(
    [elements](Choice choice) {
      for (auto &element : choice.elements) {
        add_choice_element(elements, element);
      }
    },

    [elements](auto rule) {
      for (auto &element : *elements) {
        if (element == rule) return;
      }
      elements->push_back(rule);
    }
  );
}

std::shared_ptr<Rule> Choice::build(const std::vector<Rule> &rules) {
  std::vector<Rule> elements;
  for (auto &element : rules) {
    add_choice_element(&elements, element);
  }
  return std::make_shared<Rule>(
    (elements.size() == 1) ? elements.front() : Choice{elements}
  );
}

bool Choice::operator==(const Choice &other) const {
  return elements == other.elements;
}

}  // namespace rules
}  // namespace tree_sitter
