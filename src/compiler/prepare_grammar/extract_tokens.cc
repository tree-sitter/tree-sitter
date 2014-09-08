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
#include "compiler/prepare_grammar/token_description.h"
#include "compiler/prepare_grammar/is_token.h"

namespace tree_sitter {
namespace prepare_grammar {

using std::pair;
using std::tuple;
using std::string;
using std::map;
using std::to_string;
using std::vector;
using std::set;
using std::make_shared;
using std::make_tuple;
using std::dynamic_pointer_cast;
using rules::rule_ptr;
using rules::Symbol;
using rules::SymbolOptionToken;
using rules::SymbolOptionAuxToken;

class UsedSymbols : public rules::IdentityRuleFn {
  set<Symbol> used_symbols_;

  rules::rule_ptr apply(rules::Symbol *sym) {
    used_symbols_.insert(*sym);
    return sym->copy();
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

static const GrammarError *ubiq_token_err(const string &msg) {
  return new GrammarError(GrammarErrorTypeInvalidUbiquitousToken, msg);
}

tuple<SyntaxGrammar, LexicalGrammar, const GrammarError *> extract_tokens(
    const Grammar &grammar) {
  vector<pair<string, rule_ptr>> rules, tokens, aux_rules, aux_tokens;
  vector<rule_ptr> separators;
  set<Symbol> ubiquitous_tokens;
  map<Symbol, Symbol> symbol_replacements;

  TokenExtractor extractor;

  for (size_t i = 0; i < grammar.rules().size(); i++) {
    auto pair = grammar.rules()[i];
    if (is_token(pair.second)) {
      tokens.push_back(pair);
      symbol_replacements.insert(
          { Symbol(i), Symbol(tokens.size() - 1, SymbolOptionToken) });
    } else {
      rules.push_back({ pair.first, extractor.apply(pair.second) });
    }
  }

  aux_tokens.insert(aux_tokens.end(), extractor.tokens.begin(),
                    extractor.tokens.end());

  SymbolInliner inliner(symbol_replacements);
  for (auto &pair : rules)
    pair.second = inliner.apply(pair.second);

  for (auto rule : grammar.ubiquitous_tokens()) {
    if (is_token(rule)) {
      separators.push_back(rule);
    } else {
      auto sym = dynamic_pointer_cast<const Symbol>(extractor.apply(rule));
      if (!sym.get())
        return make_tuple(SyntaxGrammar(), LexicalGrammar(),
                 ubiq_token_err("Not a token: " + rule->to_string()));

      Symbol symbol = inliner.replace_symbol(*sym);
      if (!symbol.is_token())
        return make_tuple(SyntaxGrammar(), LexicalGrammar(),
                 ubiq_token_err("Not a token: " + symbol.to_string()));

      ubiquitous_tokens.insert(symbol);
    }
  }

  return make_tuple(SyntaxGrammar(rules, aux_rules, ubiquitous_tokens),
           LexicalGrammar(tokens, aux_tokens, separators), nullptr);
}

}  // namespace prepare_grammar
}  // namespace tree_sitter
