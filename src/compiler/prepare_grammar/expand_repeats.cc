#include "compiler/prepare_grammar/expand_repeats.h"
#include <vector>
#include <string>
#include <utility>
#include "compiler/prepared_grammar.h"
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
    aux_rules.push_back({
      helper_rule_name,
      Seq::build({ inner_rule, Choice::build({ repeat_symbol.copy(),
                                               make_shared<Blank>() }) }),
      RuleEntryTypeHidden,
    });
    return repeat_symbol.copy();
  }

  rule_ptr apply_to(const Repeat *rule) {
    return Choice::build({ expand_repeat(rule), make_shared<Blank>() });
  }

 public:
  ExpandRepeats(size_t offset) : offset(offset) {}

  rule_ptr expand(const rule_ptr &rule, const string &name) {
    rule_name = name;
    repeat_count = 0;
    return apply(rule);
  }

  vector<RuleEntry> aux_rules;
};

SyntaxGrammar expand_repeats(const SyntaxGrammar &grammar) {
  SyntaxGrammar result;
  result.rules = grammar.rules;
  result.ubiquitous_tokens = grammar.ubiquitous_tokens;
  result.expected_conflicts = grammar.expected_conflicts;

  ExpandRepeats expander(result.rules.size());
  for (auto &rule_entry : result.rules)
    rule_entry.rule = expander.expand(rule_entry.rule, rule_entry.name);

  result.rules.insert(result.rules.end(), expander.aux_rules.begin(),
                      expander.aux_rules.end());
  return result;
}

}  // namespace prepare_grammar
}  // namespace tree_sitter
