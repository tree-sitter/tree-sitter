#include "compiler/prepare_grammar/extract_tokens.h"
#include <map>
#include <vector>
#include <set>
#include <string>
#include <tuple>
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

  rule_ptr apply_to_token(const Rule *input, VariableType entry_type) {
    for (size_t i = 0; i < tokens.size(); i++)
      if (tokens[i].rule->operator==(*input)) {
        token_usage_counts[i]++;
        return make_shared<Symbol>(i, true);
      }

    rule_ptr rule = input->copy();
    size_t index = tokens.size();
    tokens.push_back(Variable(token_description(rule), entry_type, rule));
    token_usage_counts.push_back(1);
    return make_shared<Symbol>(index, true);
  }

  rule_ptr apply_to(const rules::String *rule) {
    return apply_to_token(rule, VariableTypeAnonymous);
  }

  rule_ptr apply_to(const rules::Pattern *rule) {
    return apply_to_token(rule, VariableTypeAuxiliary);
  }

  rule_ptr apply_to(const rules::Metadata *rule) {
    if (rule->params.is_token)
      return apply_to_token(rule->rule.get(), VariableTypeAuxiliary);
    else
      return rules::IdentityRuleFn::apply_to(rule);
  }

 public:
  vector<size_t> token_usage_counts;
  vector<Variable> tokens;
};

static CompileError ubiq_token_err(const string &message) {
  return CompileError(TSCompileErrorTypeInvalidUbiquitousToken,
                      "Not a token: " + message);
}

tuple<InitialSyntaxGrammar, LexicalGrammar, CompileError> extract_tokens(
  const InternedGrammar &grammar) {
  InitialSyntaxGrammar syntax_grammar;
  LexicalGrammar lexical_grammar;
  SymbolReplacer symbol_replacer;
  TokenExtractor extractor;

  /*
   *  First, extract all of the grammar's tokens into the lexical grammar.
   */
  vector<Variable> processed_variables;
  for (const Variable &variable : grammar.variables)
    processed_variables.push_back(
      Variable(variable.name, variable.type, extractor.apply(variable.rule)));
  lexical_grammar.variables = extractor.tokens;

  /*
   *  If a variable's entire rule was extracted as a token and that token didn't
   *  appear within any other rule, then remove that variable from the syntax
   *  grammar, giving its name to the token in the lexical grammar. Any symbols
   *  that pointed to that variable will need to be updated to point to the
   *  variable in the lexical grammar. Symbols that pointed to later variables
   *  will need to have their indices decremented.
   */
  size_t i = 0;
  for (const Variable &variable : processed_variables) {
    auto symbol = variable.rule->as<Symbol>();
    if (symbol && symbol->is_token && !symbol->is_built_in() &&
        extractor.token_usage_counts[symbol->index] == 1) {
      lexical_grammar.variables[symbol->index].type = variable.type;
      lexical_grammar.variables[symbol->index].name = variable.name;
      symbol_replacer.replacements.insert({ Symbol(i), *symbol });
    } else {
      syntax_grammar.variables.push_back(variable);
    }
    i++;
  }

  /*
   *  Perform any replacements of symbols needed based on the previous step.
   */
  for (Variable &variable : syntax_grammar.variables)
    variable.rule = symbol_replacer.apply(variable.rule);

  for (const ConflictSet &conflict_set : grammar.expected_conflicts) {
    ConflictSet new_conflict_set;
    for (const Symbol &symbol : conflict_set)
      new_conflict_set.insert(symbol_replacer.replace_symbol(symbol));
    syntax_grammar.expected_conflicts.insert(new_conflict_set);
  }

  /*
   *  The grammar's extra tokens can be either token rules or symbols
   *  pointing to token rules. If they are symbols, then they'll be handled by
   *  the parser; add them to the syntax grammar's ubiqutous tokens. If they
   *  are anonymous rules, they can be handled by the lexer; add them to the
   *  lexical grammar's separator rules.
   */
  for (const rule_ptr &rule : grammar.extra_tokens) {
    int i = 0;
    bool used_elsewhere_in_grammar = false;
    for (const Variable &variable : lexical_grammar.variables) {
      if (variable.rule->operator==(*rule)) {
        syntax_grammar.extra_tokens.insert(Symbol(i, true));
        used_elsewhere_in_grammar = true;
      }
      i++;
    }

    if (used_elsewhere_in_grammar)
      continue;

    if (is_token(rule)) {
      lexical_grammar.separators.push_back(rule);
      continue;
    }

    auto symbol = rule->as<Symbol>();
    if (!symbol)
      return make_tuple(syntax_grammar, lexical_grammar,
                        ubiq_token_err(rule->to_string()));

    Symbol new_symbol = symbol_replacer.replace_symbol(*symbol);
    if (!new_symbol.is_token)
      return make_tuple(
        syntax_grammar, lexical_grammar,
        ubiq_token_err(syntax_grammar.variables[new_symbol.index].name));

    syntax_grammar.extra_tokens.insert(new_symbol);
  }

  return make_tuple(syntax_grammar, lexical_grammar, CompileError::none());
}

}  // namespace prepare_grammar
}  // namespace tree_sitter
