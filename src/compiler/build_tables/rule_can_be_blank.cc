#include "compiler/build_tables/rule_can_be_blank.h"
#include "compiler/rule.h"

namespace tree_sitter {
namespace build_tables {

bool rule_can_be_blank(const rules::Rule &rule) {
  return rule.match(
    [](rules::Blank) {
      return true;
    },

    [](rules::CharacterSet) {
      return false;
    },

    [](rules::Repeat repeat) {
      return rule_can_be_blank(*repeat.rule);
    },

    [](rules::Metadata metadata) {
      return rule_can_be_blank(*metadata.rule);
    },

    [](rules::Choice choice) {
      for (const auto &element : choice.elements) {
        if (rule_can_be_blank(element)) {
          return true;
        }
      }
      return false;
    },

    [](rules::Seq seq) {
      return rule_can_be_blank(*seq.left) && rule_can_be_blank(*seq.right);
    },

    [](auto) { return false; }
  );
}

}  // namespace build_tables
}  // namespace tree_sitter
