#include "compiler/prepare_grammar/expand_tokens.h"
#include <vector>
#include <string>
#include <utility>
#include <map>
#include "compiler/prepared_grammar.h"
#include "compiler/rules/visitor.h"
#include "compiler/rules/pattern.h"
#include "compiler/rules/string.h"
#include "compiler/rules/blank.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/metadata.h"
#include "compiler/rules/character_set.h"
#include "compiler/prepare_grammar/parse_regex.h"
#include "utf8proc.h"

namespace tree_sitter {
namespace prepare_grammar {

using std::string;
using std::vector;
using std::map;
using std::pair;
using std::make_shared;
using rules::String;
using rules::Pattern;
using rules::Metadata;

class ExpandTokens : public rules::IdentityRuleFn {
  using rules::IdentityRuleFn::apply_to;

  rule_ptr apply_to(const String *rule) {
    vector<rule_ptr> elements;
    uint8_t *iter = (uint8_t *)rule->value.data();
    uint8_t *end = iter + rule->value.size();

    while (iter < end) {
      int32_t el;
      size_t size = utf8proc_iterate(iter, (end - iter), &el);
      if (!size)
        break;
      iter += size;

      elements.push_back(rules::CharacterSet().include(el).copy());
    }

    return make_shared<rules::Metadata>(
      rules::Seq::build(elements),
      std::map<rules::MetadataKey, int>({
        { rules::IS_TOKEN, 1 }, { rules::PRECEDENCE, 1 },
      }));
  }

  rule_ptr apply_to(const Pattern *rule) {
    auto pair = parse_regex(rule->value);
    if (!error)
      error = pair.second;
    return pair.first;
  }

 public:
  const GrammarError *error;
  ExpandTokens() : error(nullptr) {}
};

pair<LexicalGrammar, const GrammarError *> expand_tokens(
  const LexicalGrammar &grammar) {
  LexicalGrammar result;
  ExpandTokens expander;

  for (auto &entry : grammar.rules) {
    auto rule = expander.apply(entry.rule);
    if (expander.error)
      return { result, expander.error };
    result.rules.push_back({ entry.name, rule, entry.type });
  }

  for (auto &sep : grammar.separators) {
    auto rule = expander.apply(sep);
    if (expander.error)
      return { result, expander.error };
    result.separators.push_back(rule);
  }

  return { result, nullptr };
}

}  // namespace prepare_grammar
}  // namespace tree_sitter
