#include "compiler/build_tables/get_metadata.h"
#include "compiler/rules/visitor.h"
#include "compiler/rules/seq.h"

namespace tree_sitter {
namespace build_tables {

int get_metadata(const rules::rule_ptr &rule, rules::MetadataKey key) {
  class GetMetadata : public rules::RuleFn<int> {
    rules::MetadataKey metadata_key;

    int apply_to(const rules::Metadata *rule) {
      int result = rule->value_for(metadata_key);
      return (result != 0) ? result : apply(rule->rule);
    }

    // TODO -
    // Remove this. It is currently needed to make the rule generated
    // by `LexTableBuilder::after_separators` have the right precedence.
    int apply_to(const rules::Seq *rule) { return apply(rule->left); }

   public:
    explicit GetMetadata(rules::MetadataKey key) : metadata_key(key) {}
  };

  return GetMetadata(key).apply(rule);
}

}  // namespace build_tables
}  // namespace tree_sitter
