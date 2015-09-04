#include "compiler/build_tables/get_metadata.h"
#include <utility>
#include <string>
#include "compiler/rules/visitor.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/repeat.h"
#include "compiler/rules/choice.h"
#include "compiler/build_tables/rule_can_be_blank.h"

namespace tree_sitter {
namespace build_tables {

using std::pair;
using std::string;
using std::to_string;

std::ostream &operator<<(std::ostream &stream, const MetadataRange &range) {
  return stream << string("{") << to_string(range.min) << string(", ")
                << to_string(range.max) << string("}");
}

MetadataRange get_metadata(const rule_ptr &rule, rules::MetadataKey key) {
  class GetMetadata : public rules::RuleFn<pair<MetadataRange, bool>> {
    rules::MetadataKey metadata_key;

   public:
    explicit GetMetadata(rules::MetadataKey key) : metadata_key(key) {}

   protected:
    pair<MetadataRange, bool> apply_to(const rules::Metadata *rule) {
      pair<MetadataRange, bool> result = apply(rule->rule);
      if (result.second) {
        return result;
      } else {
        int value = rule->value_for(metadata_key);
        return { { value, value }, value != 0 };
      }
    }

    pair<MetadataRange, bool> apply_to(const rules::Choice *rule) {
      pair<MetadataRange, bool> result(MetadataRange(0, 0), false);
      for (const auto &element : rule->elements)
        merge_result(&result, apply(element));
      return result;
    }

    pair<MetadataRange, bool> apply_to(const rules::Seq *rule) {
      pair<MetadataRange, bool> result = apply(rule->left);
      if (rule_can_be_blank(rule->left))
        merge_result(&result, apply(rule->right));
      return result;
    }

    pair<MetadataRange, bool> apply_to(const rules::Repeat *rule) {
      return apply(rule->content);
    }

   private:
    void merge_result(pair<MetadataRange, bool> *left,
                      const pair<MetadataRange, bool> &right) {
      if (right.second) {
        if (!left->second || right.first.min < left->first.min)
          left->first.min = right.first.min;
        if (!left->second || right.first.max > left->first.max)
          left->first.max = right.first.max;
        left->second = true;
      }
    }
  };

  return GetMetadata(key).apply(rule).first;
}

}  // namespace build_tables
}  // namespace tree_sitter
