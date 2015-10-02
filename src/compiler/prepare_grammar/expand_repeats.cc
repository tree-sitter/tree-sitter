#include "compiler/prepare_grammar/expand_repeats.h"
#include <vector>
#include <string>
#include <utility>
#include "compiler/prepare_grammar/initial_syntax_grammar.h"
#include "compiler/rules/visitor.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/symbol.h"
#include "compiler/rules/choice.h"
#include "compiler/rules/blank.h"
#include "compiler/rules/repeat.h"

namespace tree_sitter {
namespace prepare_grammar {

using std::string;
using std::vector;
using std::pair;
using std::to_string;
using std::make_shared;
using rules::Blank;
using rules::Choice;
using rules::Repeat;
using rules::Seq;
using rules::Symbol;

class ExpandRepeats : public rules::IdentityRuleFn {
  string rule_name;
  size_t offset;
  size_t repeat_count;
  vector<pair<rule_ptr, Symbol>> existing_repeats;

  rule_ptr expand_repeat(const Repeat *rule) {
    for (const auto pair : existing_repeats) {
      if (pair.first->operator==(*rule))
        return pair.second.copy();
    }

    rule_ptr inner_rule = apply(rule->content);
    size_t index = aux_rules.size();
    string helper_rule_name =
      rule_name + string("_repeat") + to_string(++repeat_count);
    Symbol repeat_symbol(offset + index);
    existing_repeats.push_back({ rule->copy(), repeat_symbol });
    aux_rules.push_back(Variable(
      helper_rule_name, VariableTypeAuxiliary,
      Seq::build({ inner_rule, Choice::build({ repeat_symbol.copy(),
                                               make_shared<Blank>() }) })));
    return repeat_symbol.copy();
  }

  rule_ptr apply_to(const Repeat *rule) {
    return Choice::build({ expand_repeat(rule), make_shared<Blank>() });
  }

 public:
  explicit ExpandRepeats(size_t offset) : offset(offset) {}

  rule_ptr expand(const rule_ptr &rule, const string &name) {
    rule_name = name;
    repeat_count = 0;
    return apply(rule);
  }

  vector<Variable> aux_rules;
};

InitialSyntaxGrammar expand_repeats(const InitialSyntaxGrammar &grammar) {
  InitialSyntaxGrammar result;
  result.variables = grammar.variables;
  result.ubiquitous_tokens = grammar.ubiquitous_tokens;
  result.expected_conflicts = grammar.expected_conflicts;

  ExpandRepeats expander(result.variables.size());
  for (auto &variable : result.variables)
    variable.rule = expander.expand(variable.rule, variable.name);

  result.variables.insert(result.variables.end(), expander.aux_rules.begin(),
                          expander.aux_rules.end());
  return result;
}

}  // namespace prepare_grammar
}  // namespace tree_sitter
