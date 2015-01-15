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

  rule_ptr apply_to(const Repeat *rule) {
    rule_ptr inner_rule = apply(rule->content);
    size_t index = aux_rules.size();
    string helper_rule_name = rule_name + string("_repeat") + to_string(index);
    rule_ptr repeat_symbol =
        make_shared<Symbol>(offset + index, rules::SymbolOptionAuxiliary);
    aux_rules.push_back(
        { helper_rule_name,
          Seq::build({ inner_rule, Choice::build({ repeat_symbol,
                                                   make_shared<Blank>() }) }) });
    return Choice::build({ repeat_symbol, make_shared<Blank>() });
  }

 public:
  ExpandRepeats(string rule_name, size_t offset)
      : rule_name(rule_name), offset(offset) {}

  size_t offset;
  vector<pair<string, rules::rule_ptr>> aux_rules;
};

SyntaxGrammar expand_repeats(const SyntaxGrammar &grammar) {
  vector<pair<string, rules::rule_ptr>> rules, aux_rules(grammar.aux_rules);

  for (auto &pair : grammar.rules) {
    ExpandRepeats expander(pair.first, aux_rules.size());
    rules.push_back({ pair.first, expander.apply(pair.second) });
    aux_rules.insert(aux_rules.end(), expander.aux_rules.begin(),
                     expander.aux_rules.end());
  }

  return SyntaxGrammar(rules, aux_rules, grammar.ubiquitous_tokens);
}

}  // namespace prepare_grammar
}  // namespace tree_sitter
