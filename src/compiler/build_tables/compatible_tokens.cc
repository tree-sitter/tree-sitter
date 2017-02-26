#include "compiler/build_tables/compatible_tokens.h"
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
using std::set;

template <bool left, bool right>
class CharacterAggregator : public rules::RuleFn<void> {
  void apply_to(const rules::Seq *rule) {
    if (left) apply(rule->left);
    if (right) apply(rule->right);
  }

  void apply_to(const rules::Choice *rule) {
    for (const rule_ptr &element : rule->elements) {
      apply(element);
    }
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

template <bool left, bool right>
class CharacterIntersector : public rules::RuleFn<bool> {
  bool apply_to(const rules::Seq *rule) {
    bool result = false;
    if (left) result = apply(rule->left);
    if (right && !result) result = apply(rule->right);
    return result;
  }

  bool apply_to(const rules::Choice *rule) {
    for (const rule_ptr &element : rule->elements) {
      if (apply(element)) return true;
    }
    return false;
  }

  bool apply_to(const rules::Repeat *rule) {
    return apply(rule->content);
  }

  bool apply_to(const rules::Metadata *rule) {
    return apply(rule->rule);
  }

  bool apply_to(const rules::CharacterSet *rule) {
    return character_set->intersects(*rule);
  }

 public:
  rules::CharacterSet *character_set;

  CharacterIntersector(rules::CharacterSet *set) : character_set {set} {}
};

using FirstCharacters = CharacterAggregator<true, false>;
using LastCharacters = CharacterAggregator<false, true>;
using AllCharacters = CharacterAggregator<true, true>;
using FirstCharactersIntersector = CharacterIntersector<true, false>;

CompatibleTokensResult get_compatible_tokens(const LexicalGrammar &grammar) {
  CompatibleTokensResult result;

  AllCharacters all_separator_characters;
  for (const rule_ptr &separator : grammar.separators)
    all_separator_characters.apply(separator);

  for (size_t i = 0; i < grammar.variables.size(); i++) {
    Symbol symbol(i, Symbol::Terminal);
    rule_ptr rule = grammar.variables[i].rule;

    FirstCharacters first_characters;
    first_characters.apply(rule);

    LastCharacters last_characters;
    last_characters.apply(rule);

    AllCharacters all_characters;
    all_characters.apply(rule);

    bool has_distinct_start =
      !first_characters.result.includes_all &&
      !first_characters.result.intersects(all_separator_characters.result);

    bool has_distinct_end =
      !last_characters.result.includes_all &&
      !last_characters.result.intersects(all_separator_characters.result);

    bool has_no_separators =
      !all_characters.result.intersects(all_separator_characters.result);

    if ((has_distinct_start && has_distinct_end) || has_no_separators)
      result.recovery_tokens.insert(symbol);

    for (size_t j = 0; j < grammar.variables.size(); j++) {
      if (j == i) continue;
      Symbol other_symbol(j, Symbol::Terminal);
      FirstCharactersIntersector intersector(&first_characters.result);
      if (intersector.apply(grammar.variables[j].rule)) {
        result.unmergeable_pairs[symbol].insert(other_symbol);
      }
    }
  }

  return result;
}

}  // namespace build_tables
}  // namespace tree_sitter
