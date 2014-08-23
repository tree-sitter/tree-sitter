#include "compiler/prepare_grammar/extract_tokens.h"
#include <map>
#include <vector>
#include <set>
#include <string>
#include "tree_sitter/compiler.h"
#include "compiler/prepared_grammar.h"
#include "compiler/rules/visitor.h"
#include "compiler/rules/symbol.h"
#include "compiler/rules/string.h"
#include "compiler/rules/metadata.h"
#include "compiler/rules/pattern.h"
#include "compiler/prepare_grammar/interned_grammar.h"
#include "compiler/prepare_grammar/token_description.h"

namespace tree_sitter {
namespace prepare_grammar {

using std::pair;
using std::string;
using std::map;
using std::to_string;
using std::vector;
using std::set;
using std::make_shared;
using rules::rule_ptr;
using rules::Symbol;

class IsToken : public rules::RuleFn<bool> {
  bool apply_to(const rules::String *rule) { return true; }
  bool apply_to(const rules::Pattern *rule) { return true; }
  bool apply_to(const rules::Metadata *rule) {
    return rule->value_for(rules::IS_TOKEN);
  }
};

class SymbolInliner : public rules::IdentityRuleFn {
  map<Symbol, Symbol> replacements;
  using rules::IdentityRuleFn::apply_to;

  int new_index_for_symbol(const Symbol &symbol) {
    int result = symbol.index;
    for (const auto &pair : replacements)
      if (pair.first.index < symbol.index &&
          pair.first.is_auxiliary() == symbol.is_auxiliary())
        result--;
    return result;
  }

  rule_ptr apply_to(const Symbol *rule) { return replace_symbol(*rule).copy(); }

 public:
  Symbol replace_symbol(const Symbol &rule) {
    if (rule.is_built_in())
      return rule;
    auto replacement_pair = replacements.find(rule);
    if (replacement_pair != replacements.end())
      return replacement_pair->second;
    else
      return Symbol(new_index_for_symbol(rule), rule.options);
  }

  explicit SymbolInliner(const map<Symbol, Symbol> &replacements)
      : replacements(replacements) {}
};

const rules::SymbolOption SymbolOptionAuxToken = rules::SymbolOption(
    rules::SymbolOptionToken | rules::SymbolOptionAuxiliary);

class TokenExtractor : public rules::IdentityRuleFn {
  rule_ptr apply_to_token(const rules::Rule *input) {
    auto rule = input->copy();
    for (size_t i = 0; i < tokens.size(); i++)
      if (tokens[i].second->operator==(*rule))
        return make_shared<Symbol>(i, SymbolOptionAuxToken);
    size_t index = tokens.size();
    tokens.push_back({ token_description(rule), rule });
    return make_shared<Symbol>(index, SymbolOptionAuxToken);
  }

  rule_ptr default_apply(const rules::Rule *rule) {
    auto result = rule->copy();
    if (IsToken().apply(rule->copy())) {
      return apply_to_token(rule);
    } else {
      return result;
    }
  }

  rule_ptr apply_to(const rules::Metadata *rule) {
    auto result = rule->copy();
    if (IsToken().apply(rule->copy())) {
      return apply_to_token(rule);
    } else {
      return rules::IdentityRuleFn::apply_to(rule);
    }
  }

 public:
  vector<pair<string, rule_ptr> > tokens;
};

pair<SyntaxGrammar, LexicalGrammar> extract_tokens(
    const InternedGrammar &input_grammar) {
  vector<pair<string, rule_ptr> > rules, tokens, aux_rules, aux_tokens;
  set<Symbol> ubiquitous_tokens;

  TokenExtractor extractor;
  map<Symbol, Symbol> symbol_replacements;

  for (size_t i = 0; i < input_grammar.rules.size(); i++) {
    auto pair = input_grammar.rules[i];
    if (IsToken().apply(pair.second)) {
      tokens.push_back(pair);
      symbol_replacements.insert(
          { Symbol(i), Symbol(tokens.size() - 1, rules::SymbolOptionToken) });
    } else {
      rules.push_back({ pair.first, extractor.apply(pair.second) });
    }
  }

  aux_tokens.insert(aux_tokens.end(), extractor.tokens.begin(),
                    extractor.tokens.end());

  SymbolInliner inliner(symbol_replacements);
  for (auto &pair : rules)
    pair.second = inliner.apply(pair.second);
  for (auto &symbol : input_grammar.ubiquitous_tokens)
    ubiquitous_tokens.insert(inliner.replace_symbol(symbol));

  return { SyntaxGrammar(rules, aux_rules, ubiquitous_tokens),
           LexicalGrammar(tokens, aux_tokens, input_grammar.separators), };
}

}  // namespace prepare_grammar
}  // namespace tree_sitter
