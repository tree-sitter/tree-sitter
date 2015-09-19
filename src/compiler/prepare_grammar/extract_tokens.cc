#include "compiler/prepare_grammar/extract_tokens.h"
#include <map>
#include <vector>
#include <set>
#include <string>
#include <tuple>
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

using std::dynamic_pointer_cast;
using std::make_shared;
using std::make_tuple;
using std::map;
using std::set;
using std::string;
using std::tuple;
using std::vector;
using rules::Symbol;

class SymbolReplacer : public rules::IdentityRuleFn {
  using rules::IdentityRuleFn::apply_to;

  rule_ptr apply_to(const Symbol *rule) {
    return replace_symbol(*rule).copy();
  }

 public:
  map<Symbol, Symbol> replacements;

  Symbol replace_symbol(const Symbol &symbol) {
    if (symbol.is_built_in() || symbol.is_token)
      return symbol;

    auto replacement_pair = replacements.find(symbol);
    if (replacement_pair != replacements.end())
      return replacement_pair->second;

    int new_index = symbol.index;
    for (const auto &pair : replacements)
      if (pair.first.index < symbol.index)
        new_index--;
    return Symbol(new_index);
  }
};

class TokenExtractor : public rules::IdentityRuleFn {
  using rules::IdentityRuleFn::apply_to;

  rule_ptr apply_to_token(const Rule *input, RuleEntryType entry_type) {
    for (size_t i = 0; i < tokens.size(); i++)
      if (tokens[i].rule->operator==(*input)) {
        token_usage_counts[i]++;
        return make_shared<Symbol>(i, true);
      }

    rule_ptr rule = input->copy();
    size_t index = tokens.size();
    tokens.push_back({
      token_description(rule), rule, entry_type,
    });
    token_usage_counts.push_back(1);
    return make_shared<Symbol>(index, true);
  }

  rule_ptr apply_to(const rules::String *rule) {
    return apply_to_token(rule, RuleEntryTypeAnonymous);
  }

  rule_ptr apply_to(const rules::Pattern *rule) {
    return apply_to_token(rule, RuleEntryTypeAuxiliary);
  }

  rule_ptr apply_to(const rules::Metadata *rule) {
    if (rule->value_for(rules::IS_TOKEN) > 0)
      return apply_to_token(rule->rule.get(), RuleEntryTypeAuxiliary);
    else
      return rules::IdentityRuleFn::apply_to(rule);
  }

 public:
  vector<size_t> token_usage_counts;
  vector<RuleEntry> tokens;
};

static const GrammarError *ubiq_token_err(const string &message) {
  return new GrammarError(GrammarErrorTypeInvalidUbiquitousToken,
                          "Not a token: " + message);
}

tuple<SyntaxGrammar, LexicalGrammar, const GrammarError *> extract_tokens(
  const InternedGrammar &grammar) {
  SyntaxGrammar syntax_grammar;
  LexicalGrammar lexical_grammar;
  SymbolReplacer symbol_replacer;
  TokenExtractor extractor;

  /*
   *  First, extract all of the grammar's tokens into the lexical grammar.
   */
  vector<RuleEntry> processed_rules;
  for (const RuleEntry &entry : grammar.rules)
    processed_rules.push_back({
      entry.name, extractor.apply(entry.rule), entry.type,
    });
  lexical_grammar.rules = extractor.tokens;

  /*
   *  If a rule's entire content was extracted as a token and that token didn't
   *  appear within any other rule, then remove that rule from the syntax
   *  grammar, giving its name to the token in the lexical grammar. Any symbols
   *  that pointed to that rule will need to be updated to point to the rule in
   *  the lexical grammar. Symbols that pointed to later rules will need to have
   *  their indices decremented.
   */
  size_t i = 0;
  for (const RuleEntry &entry : processed_rules) {
    auto symbol = dynamic_pointer_cast<const Symbol>(entry.rule);
    if (symbol.get() && symbol->is_token && !symbol->is_built_in() &&
        extractor.token_usage_counts[symbol->index] == 1) {
      lexical_grammar.rules[symbol->index].type = entry.type;
      lexical_grammar.rules[symbol->index].name = entry.name;
      symbol_replacer.replacements.insert({ Symbol(i), *symbol });
    } else {
      syntax_grammar.rules.push_back(entry);
    }
    i++;
  }

  /*
   *  Perform any replacements of symbols needed based on the previous step.
   */
  for (RuleEntry &entry : syntax_grammar.rules)
    entry.rule = symbol_replacer.apply(entry.rule);

  for (auto &symbol_set : grammar.expected_conflicts) {
    set<Symbol> new_symbol_set;
    for (const Symbol &symbol : symbol_set)
      new_symbol_set.insert(symbol_replacer.replace_symbol(symbol));
    syntax_grammar.expected_conflicts.insert(new_symbol_set);
  }

  /*
   *  The grammar's ubiquitous tokens can be either token rules or symbols
   *  pointing to token rules. If they are symbols, then they'll be handled by
   *  the parser; add them to the syntax grammar's ubiqutous tokens. If they
   *  are anonymous rules, they can be handled by the lexer; add them to the
   *  lexical grammar's separator rules.
   */
  for (const rule_ptr &rule : grammar.ubiquitous_tokens) {
    if (is_token(rule)) {
      lexical_grammar.separators.push_back(rule);
      continue;
    }

    auto symbol = dynamic_pointer_cast<const Symbol>(rule);
    if (!symbol.get())
      return make_tuple(syntax_grammar, lexical_grammar,
                        ubiq_token_err(rule->to_string()));

    Symbol new_symbol = symbol_replacer.replace_symbol(*symbol);
    if (!new_symbol.is_token)
      return make_tuple(
        syntax_grammar, lexical_grammar,
        ubiq_token_err(syntax_grammar.rules[new_symbol.index].name));

    syntax_grammar.ubiquitous_tokens.insert(new_symbol);
  }

  return make_tuple(syntax_grammar, lexical_grammar, nullptr);
}

}  // namespace prepare_grammar
}  // namespace tree_sitter
