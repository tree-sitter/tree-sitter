#include "compiler/prepare_grammar/expand_repeats.h"
#include <vector>
#include <string>
#include <utility>
#include "compiler/syntax_grammar.h"
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
using rules::rule_ptr;
using rules::Blank;
using rules::Choice;
using rules::Repeat;
using rules::Rule;
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
    Symbol repeat_symbol(offset + index, rules::SymbolOptionAuxiliary);
    existing_repeats.push_back({ rule->copy(), repeat_symbol });
    aux_rules.push_back(
      { helper_rule_name,
        Seq::build({ inner_rule, Choice::build({ repeat_symbol.copy(),
                                                 make_shared<Blank>() }) }) });
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

  vector<pair<string, rules::rule_ptr>> aux_rules;
};

SyntaxGrammar expand_repeats(const SyntaxGrammar &grammar) {
  SyntaxGrammar result;
  result.aux_rules = grammar.aux_rules;
  result.ubiquitous_tokens = grammar.ubiquitous_tokens;
  result.expected_conflicts = grammar.expected_conflicts;

  ExpandRepeats expander(result.aux_rules.size());
  for (auto &pair : grammar.rules)
    result.rules.push_back(
      { pair.first, expander.expand(pair.second, pair.first) });

  result.aux_rules.insert(result.aux_rules.end(), expander.aux_rules.begin(),
                          expander.aux_rules.end());
  return result;
}

}  // namespace prepare_grammar
}  // namespace tree_sitter
