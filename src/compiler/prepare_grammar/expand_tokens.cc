#include "compiler/prepare_grammar/expand_tokens.h"
#include <vector>
#include <string>
#include <utility>
#include <map>
#include "compiler/lexical_grammar.h"
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
    const uint8_t *iter = reinterpret_cast<const uint8_t *>(rule->value.data());
    const uint8_t *end = iter + rule->value.size();

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
        { rules::IS_TOKEN, 1 }, { rules::IS_STRING, 1 },
      }));
  }

  rule_ptr apply_to(const Pattern *rule) {
    auto pair = parse_regex(rule->value);
    if (!error.type)
      error = pair.second;
    return pair.first;
  }

 public:
  CompileError error;
  ExpandTokens() : error(CompileError::none()) {}
};

pair<LexicalGrammar, CompileError> expand_tokens(const LexicalGrammar &grammar) {
  LexicalGrammar result;
  ExpandTokens expander;

  for (const Variable &variable : grammar.variables) {
    auto rule = expander.apply(variable.rule);
    if (expander.error.type)
      return { result, expander.error };
    result.variables.push_back(Variable(
      variable.internal_name, variable.external_name, variable.type, rule));
  }

  for (auto &sep : grammar.separators) {
    auto rule = expander.apply(sep);
    if (expander.error.type)
      return { result, expander.error };
    result.separators.push_back(rule);
  }

  return { result, CompileError::none() };
}

}  // namespace prepare_grammar
}  // namespace tree_sitter
