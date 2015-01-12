#include "compiler/prepare_grammar/extract_tokens.h"
#include <map>
#include <vector>
#include <set>
#include <string>
#include "tree_sitter/compiler.h"
#include "compiler/lexical_grammar.h"
#include "compiler/prepare_grammar/initial_syntax_grammar.h"
#include "compiler/rules/visitor.h"
#include "compiler/rules/symbol.h"
#include "compiler/rules/string.h"
#include "compiler/rules/metadata.h"
#include "compiler/rules/pattern.h"
#include "compiler/prepare_grammar/token_description.h"
#include "compiler/prepare_grammar/is_token.h"

namespace tree_sitter {
namespace prepare_grammar {

using std::dynamic_pointer_cast;
using std::make_shared;
using std::make_tuple;
using std::map;
using std::pair;
using std::set;
using std::string;
using std::tuple;
using std::vector;
using rules::rule_ptr;
using rules::Symbol;
using rules::SymbolOptionToken;
using rules::SymbolOptionAuxToken;

class SymbolReplacer : public rules::IdentityRuleFn {
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
  map<Symbol, Symbol> replacements;

  Symbol replace_symbol(const Symbol &rule) {
    if (rule.is_built_in())
      return rule;
    auto replacement_pair = replacements.find(rule);
    if (replacement_pair != replacements.end())
      return replacement_pair->second;
    else
      return Symbol(new_index_for_symbol(rule), rule.options);
  }
};

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
    if (is_token(rule->copy())) {
      return apply_to_token(rule);
    } else {
      return result;
    }
  }

  rule_ptr apply_to(const rules::Metadata *rule) {
    auto result = rule->copy();
    if (is_token(rule->copy())) {
      return apply_to_token(rule);
    } else {
      return rules::IdentityRuleFn::apply_to(rule);
    }
  }

 public:
  vector<pair<string, rule_ptr>> tokens;
};

static tuple<InitialSyntaxGrammar, LexicalGrammar, const GrammarError *> ubiq_token_err(
    const string &msg) {
  return make_tuple(InitialSyntaxGrammar(), LexicalGrammar(),
                    new GrammarError(GrammarErrorTypeInvalidUbiquitousToken,
                                     "Not a token: " + msg));
}

tuple<InitialSyntaxGrammar, LexicalGrammar, const GrammarError *> extract_tokens(
    const Grammar &grammar) {
  vector<pair<string, rule_ptr>> rules, tokens;
  vector<rule_ptr> separators;
  set<Symbol> ubiquitous_tokens;

  SymbolReplacer symbol_replacer;
  TokenExtractor extractor;

  size_t i = 0;
  for (auto &pair : grammar.rules()) {
    if (is_token(pair.second)) {
      tokens.push_back(pair);
      symbol_replacer.replacements.insert(
          { Symbol(i), Symbol(tokens.size() - 1, SymbolOptionToken), });
    } else {
      rules.push_back({ pair.first, extractor.apply(pair.second) });
    }
    i++;
  }

  for (auto &pair : rules)
    pair.second = symbol_replacer.apply(pair.second);

  for (auto &rule : grammar.ubiquitous_tokens()) {
    if (is_token(rule)) {
      separators.push_back(rule);
    } else {
      auto sym = dynamic_pointer_cast<const Symbol>(extractor.apply(rule));
      if (!sym.get())
        return ubiq_token_err(rule->to_string());

      Symbol symbol = symbol_replacer.replace_symbol(*sym);
      if (!symbol.is_token())
        return ubiq_token_err(rules[symbol.index].first);

      ubiquitous_tokens.insert(symbol);
    }
  }

  return make_tuple(InitialSyntaxGrammar(rules, {}, ubiquitous_tokens),
                    LexicalGrammar(tokens, extractor.tokens, separators),
                    nullptr);
}

}  // namespace prepare_grammar
}  // namespace tree_sitter
