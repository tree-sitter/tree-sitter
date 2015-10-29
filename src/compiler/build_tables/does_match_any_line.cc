#include "compiler/build_tables/does_match_any_line.h"
#include "compiler/rules/choice.h"
#include "compiler/rules/character_set.h"
#include "compiler/rules/repeat.h"
#include "compiler/rules/visitor.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/metadata.h"

namespace tree_sitter {
namespace build_tables {

class DoesTokenCatchAnyCharacter : public rules::RuleFn<bool> {
  bool apply_to(const rules::Choice *rule) {
    for (const rule_ptr &element : rule->elements)
      if (apply(element))
        return true;
    return false;
  }

  bool apply_to(const rules::Metadata *rule) {
    return apply(rule->rule);
  }

  bool apply_to(const rules::CharacterSet *rule) {
    if (rule->includes_all) {
      for (uint32_t character : rule->excluded_chars) {
        if (character != 0 && character != '\n')
          return false;
      }
      return true;
    }
    return false;
  }
};

class DoesTokenCatchAll : public rules::RuleFn<bool> {
  bool apply_to(const rules::Repeat *rule) {
    return DoesTokenCatchAnyCharacter().apply(rule->content);
  }

  bool apply_to(const rules::Metadata *rule) {
    return apply(rule->rule);
  }

  bool apply_to(const rules::Choice *rule) {
    for (const rule_ptr &element : rule->elements)
      if (apply(element))
        return true;
    return false;
  }

  bool apply_to(const rules::Seq *rule) {
    return apply(rule->left) && apply(rule->right);
  }
};

bool does_match_any_line(const rule_ptr &rule) {
  return DoesTokenCatchAll().apply(rule);
}

}  // namespace build_tables
}  // namespace tree_sitter
