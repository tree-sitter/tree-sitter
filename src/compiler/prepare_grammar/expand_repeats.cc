#include "compiler/prepare_grammar/expand_repeats.h"
#include <vector>
#include <string>
#include <utility>
#include <cassert>
#include "compiler/grammar.h"
#include "compiler/rule.h"

namespace tree_sitter {
namespace prepare_grammar {

using std::string;
using std::vector;
using std::pair;
using std::to_string;
using rules::Rule;
using rules::Symbol;

class ExpandRepeats {
  string rule_name;
  size_t offset;
  size_t repeat_count;
  vector<pair<Rule, Symbol>> existing_repeats;

  Rule apply(Rule rule) {
    return rule.match(
      [&](const rules::Blank &blank) -> Rule { return blank; },
      [&](const rules::Symbol &symbol) { return symbol; },

      [&](const rules::Choice &choice) {
        vector<Rule> elements;
        for (const auto &element : choice.elements) {
          elements.push_back(apply(element));
        }
        return Rule::choice(elements);
      },

      [&](const rules::Seq &sequence) {
        auto left = apply(*sequence.left);
        auto right = apply(*sequence.right);
        return rules::Seq{left, right};
      },

      [&](const rules::Repeat &repeat) {
        for (const auto pair : existing_repeats) {
          if (pair.first == rule) {
            return pair.second;
          }
        }

        Rule inner_rule = apply(*repeat.rule);
        size_t index = aux_rules.size();
        string helper_rule_name = rule_name + "_repeat" + to_string(++repeat_count);
        Symbol repeat_symbol = Symbol::non_terminal(offset + index);
        existing_repeats.push_back({repeat, repeat_symbol});
        aux_rules.push_back({
          helper_rule_name,
          VariableTypeAuxiliary,
          rules::Choice{{
            rules::Seq{repeat_symbol, repeat_symbol},
            inner_rule,
          }}
        });
        return repeat_symbol;
      },

      [&](const rules::Metadata &metadata) {
        return rules::Metadata{apply(*metadata.rule), metadata.params};
      },

      [](auto) {
        assert(!"Unexpected rule type");
        return rules::Blank{};
      }
    );
  }

 public:
  explicit ExpandRepeats(size_t offset) : offset(offset) {}

  Rule expand(const Rule &rule, const string &name) {
    rule_name = name;
    repeat_count = 0;
    return apply(rule);
  }

  vector<Variable> aux_rules;
};

InitialSyntaxGrammar expand_repeats(const InitialSyntaxGrammar &grammar) {
  InitialSyntaxGrammar result;
  result.variables = grammar.variables;
  result.extra_tokens = grammar.extra_tokens;
  result.expected_conflicts = grammar.expected_conflicts;
  result.external_tokens = grammar.external_tokens;
  result.variables_to_inline = grammar.variables_to_inline;

  ExpandRepeats expander(result.variables.size());
  for (auto &variable : result.variables) {
    variable.rule = expander.expand(variable.rule, variable.name);
  }

  result.variables.insert(
    result.variables.end(),
    expander.aux_rules.begin(),
    expander.aux_rules.end()
  );

  result.word_token = grammar.word_token;
  return result;
}

}  // namespace prepare_grammar
}  // namespace tree_sitter
