#include "compiler/build_tables/recovery_tokens.h"
#include "compiler/lexical_grammar.h"
#include "compiler/rules/choice.h"
#include "compiler/rules/character_set.h"
#include "compiler/rules/repeat.h"
#include "compiler/rules/visitor.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/metadata.h"

namespace tree_sitter {
namespace build_tables {

using rules::Symbol;
using std::vector;

template <bool left, bool right>
class CharacterAggregator : public rules::RuleFn<void> {
  void apply_to(const rules::Seq *rule) {
    if (left)
      apply(rule->left);
    if (right)
      apply(rule->right);
  }

  void apply_to(const rules::Choice *rule) {
    for (const rule_ptr &element : rule->elements)
      apply(element);
  }

  void apply_to(const rules::Repeat *rule) {
    apply(rule->content);
  }

  void apply_to(const rules::Metadata *rule) {
    apply(rule->rule);
  }

  void apply_to(const rules::CharacterSet *rule) {
    result.add_set(*rule);
  }

 public:
  rules::CharacterSet result;
};

class FirstCharacters : public CharacterAggregator<true, false> {};
class LastCharacters : public CharacterAggregator<false, true> {};
class AllCharacters : public CharacterAggregator<true, true> {};

vector<Symbol> recovery_tokens(const LexicalGrammar &grammar) {
  vector<Symbol> result;

  AllCharacters all_separator_characters;
  for (const rule_ptr &separator : grammar.separators)
    all_separator_characters.apply(separator);

  for (size_t i = 0; i < grammar.variables.size(); i++) {
    const Variable &variable = grammar.variables[i];
    rule_ptr rule = variable.rule;

    FirstCharacters first_characters;
    first_characters.apply(variable.rule);

    LastCharacters last_characters;
    last_characters.apply(variable.rule);

    AllCharacters all_characters;
    all_characters.apply(variable.rule);

    bool has_distinct_start =
      !first_characters.result.includes_all &&
      !first_characters.result.intersects(all_separator_characters.result);

    bool has_distinct_end =
      !last_characters.result.includes_all &&
      !last_characters.result.intersects(all_separator_characters.result);

    bool has_no_separators =
      !all_characters.result.intersects(all_separator_characters.result);

    if ((has_distinct_start && has_distinct_end) || has_no_separators)
      result.push_back(Symbol(i, true));
  }

  return result;
}

}  // namespace build_tables
}  // namespace tree_sitter
