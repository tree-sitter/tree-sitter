#include "compiler/rules/choice.h"
#include <string>
#include <set>
#include "compiler/rules/visitor.h"
#include "compiler/util/hash_combine.h"

namespace tree_sitter {
namespace rules {

using std::string;
using std::make_shared;
using std::vector;
using std::set;
using util::symmetric_hash_combine;

Choice::Choice(const vector<rule_ptr> &elements) : elements(elements) {}

void add_choice_element(vector<rule_ptr> *vec, const rule_ptr new_rule) {
  auto choice = new_rule->as<Choice>();
  if (choice) {
    for (auto &child : choice->elements)
      add_choice_element(vec, child);
  } else {
    for (auto &element : *vec)
      if (element->operator==(*new_rule))
        return;
    vec->push_back(new_rule);
  }
}

rule_ptr Choice::build(const vector<rule_ptr> &inputs) {
  vector<rule_ptr> elements;
  for (auto &el : inputs)
    add_choice_element(&elements, el);
  if (elements.size() == 1)
    return elements.front();
  else
    return make_shared<Choice>(elements);
}

bool Choice::operator==(const Rule &rule) const {
  const Choice *other = rule.as<Choice>();
  if (!other)
    return false;
  size_t size = elements.size();
  if (size != other->elements.size())
    return false;
  for (size_t i = 0; i < size; i++)
    if (!elements[i]->operator==(*other->elements[i]))
      return false;
  return true;
}

size_t Choice::hash_code() const {
  size_t result = 0;
  symmetric_hash_combine(&result, elements.size());
  for (const auto &element : elements)
    symmetric_hash_combine(&result, element);
  return result;
}

rule_ptr Choice::copy() const {
  return std::make_shared<Choice>(*this);
}

string Choice::to_string() const {
  string result = "(choice";
  for (const auto &element : elements)
    result += " " + element->to_string();
  return result + ")";
}

void Choice::accept(Visitor *visitor) const {
  visitor->visit(this);
}

}  // namespace rules
}  // namespace tree_sitter
