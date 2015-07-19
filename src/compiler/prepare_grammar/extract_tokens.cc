#include "compiler/prepare_grammar/extract_tokens.h"
#include <map>
#include <vector>
#include <set>
#include <string>
#include "tree_sitter/compiler.h"
#include "compiler/lexical_grammar.h"
#include "compiler/syntax_grammar.h"
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
    if (is_token(result))
      return apply_to_token(rule);
    else
      return result;
  }

  rule_ptr apply_to(const rules::Metadata *rule) {
    if (is_token(rule->copy()))
      return apply_to_token(rule);
    else
      return rules::IdentityRuleFn::apply_to(rule);
  }

 public:
  vector<pair<string, rule_ptr>> tokens;
};

static const GrammarError * ubiq_token_err(const string &msg) {
  return new GrammarError(GrammarErrorTypeInvalidUbiquitousToken, "Not a token: " + msg);
}

tuple<SyntaxGrammar, LexicalGrammar, const GrammarError *>
extract_tokens(const InternedGrammar &grammar) {
  SyntaxGrammar syntax_grammar;
  LexicalGrammar lexical_grammar;
  SymbolReplacer symbol_replacer;
  TokenExtractor extractor;

  size_t i = 0;
  for (auto &pair : grammar.rules) {
    if (is_token(pair.second)) {
      lexical_grammar.rules.push_back(pair);
      symbol_replacer.replacements.insert({
        Symbol(i),
        Symbol(lexical_grammar.rules.size() - 1, SymbolOptionToken)
      });
    } else {
      syntax_grammar.rules.push_back({ pair.first, extractor.apply(pair.second) });
    }
    i++;
  }

  for (auto &pair : syntax_grammar.rules)
    pair.second = symbol_replacer.apply(pair.second);

  for (auto &rule : grammar.ubiquitous_tokens) {
    if (is_token(rule)) {
      lexical_grammar.separators.push_back(rule);
    } else {
      auto sym = dynamic_pointer_cast<const Symbol>(extractor.apply(rule));
      if (!sym.get())
        return make_tuple(syntax_grammar, lexical_grammar, ubiq_token_err(rule->to_string()));

      Symbol symbol = symbol_replacer.replace_symbol(*sym);
      if (!symbol.is_token())
        return make_tuple(syntax_grammar, lexical_grammar, ubiq_token_err(syntax_grammar.rules[symbol.index].first));

      syntax_grammar.ubiquitous_tokens.insert(symbol);
    }
  }

  for (auto &symbol_set : grammar.expected_conflicts) {
    set<Symbol> new_symbol_set;
    for (const Symbol &symbol : symbol_set)
      new_symbol_set.insert(symbol_replacer.replace_symbol(symbol));
    syntax_grammar.expected_conflicts.insert(new_symbol_set);
  }

  lexical_grammar.aux_rules = extractor.tokens;

  return make_tuple(syntax_grammar, lexical_grammar, nullptr);
}

}  // namespace prepare_grammar
}  // namespace tree_sitter
