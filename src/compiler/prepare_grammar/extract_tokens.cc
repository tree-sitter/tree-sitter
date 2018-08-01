#include "compiler/prepare_grammar/extract_tokens.h"
#include <map>
#include <vector>
#include <cassert>
#include <set>
#include <string>
#include <tuple>
#include "tree_sitter/compiler.h"
#include "compiler/lexical_grammar.h"
#include "compiler/rule.h"
#include "compiler/prepare_grammar/token_description.h"
#include "compiler/prepare_grammar/expand_tokens.h"

namespace tree_sitter {
namespace prepare_grammar {

using std::make_tuple;
using std::map;
using std::set;
using std::string;
using std::tuple;
using std::vector;
using rules::Symbol;
using rules::Rule;
using rules::Rule;

class SymbolReplacer {
 public:
  map<Symbol, Symbol> replacements;

  Rule apply(const Rule &rule) {
    return rule.match(
      [](const rules::Blank &blank) -> Rule {
        return blank;
      },

      [this](const rules::Symbol &symbol) {
        return replace_symbol(symbol);
      },

      [this](const rules::Choice &choice) {
        vector<rules::Rule> elements;
        for (const auto &element : choice.elements) {
          elements.push_back(apply(element));
        }
        return Rule::choice(elements);
      },

      [this](const rules::Seq &sequence) {
        return rules::Seq{
          apply(*sequence.left),
          apply(*sequence.right)
        };
      },

      [this](const rules::Repeat &repeat) {
        return Rule::repeat(apply(*repeat.rule));
      },

      [this](const rules::Metadata &metadata) {
        return rules::Metadata{apply(*metadata.rule), metadata.params};
      },

      [](auto) {
        assert(!"Unexpected rule type");
        return rules::Blank{};
      }
    );
  }

  Symbol replace_symbol(const Symbol &symbol) {
    if (!symbol.is_non_terminal()) return symbol;

    auto replacement_pair = replacements.find(symbol);
    if (replacement_pair != replacements.end()) {
      return replacement_pair->second;
    }

    int new_index = symbol.index;
    for (const auto &pair : replacements) {
      if (pair.first.index < symbol.index) {
        new_index--;
      }
    }

    return Symbol::non_terminal(new_index);
  }
};

class TokenExtractor {
  Symbol extract_token(const rules::Rule &input, VariableType entry_type) {
    for (size_t i = 0; i < tokens.size(); i++) {
      if (tokens[i].rule == input) {
        token_usage_counts[i]++;
        return Symbol::terminal(i);
      }
    }

    size_t index = tokens.size();
    tokens.push_back({
      token_description(input),
      entry_type,
      input
    });
    token_usage_counts.push_back(1);

    return Symbol::terminal(index);
  }

 public:
  Rule apply(const rules::Rule &rule) {
    return rule.match(
      [](const rules::Blank &blank) -> Rule { return blank; },

      [this](const rules::Metadata &rule) -> Rule {
        if (rule.params.is_token) {
          rules::Metadata metadata{*rule.rule, rule.params};
          metadata.params.is_token = false;
          if (metadata.params == rules::MetadataParams{}) {
            return extract_token(*metadata.rule, VariableTypeAuxiliary);
          } else if (metadata.rule->is<rules::String>()) {
            return extract_token(metadata, VariableTypeAnonymous);
          } else {
            return extract_token(metadata, VariableTypeAuxiliary);
          }
        } else {
          return rules::Metadata{apply(*rule.rule), rule.params};
        }
      },

      [this](const rules::String &rule) {
        return extract_token(rule, VariableTypeAnonymous);
      },

      [this](const rules::Pattern &rule) {
        return extract_token(rule, VariableTypeAuxiliary);
      },

      [this](const rules::Repeat &rule) {
        return Rule::repeat(apply(*rule.rule));
      },

      [this](const rules::Seq &rule) {
        return Rule::seq({apply(*rule.left), apply(*rule.right)});
      },

      [this](const rules::Choice &rule) {
        std::vector<Rule> elements;
        for (const auto &element : rule.elements) {
          elements.push_back(apply(element));
        }
        return Rule::choice(elements);
      },

      [](const rules::Symbol &symbol) {
        return symbol;
      },

      [](auto) {
        assert(!"Unexpected rule type");
        return rules::Blank{};
      }
    );
  }

  vector<size_t> token_usage_counts;
  vector<Variable> tokens;
};

tuple<InitialSyntaxGrammar, LexicalGrammar, CompileError> extract_tokens(
  const InternedGrammar &grammar
) {
  InitialSyntaxGrammar syntax_grammar;
  LexicalGrammar lexical_grammar;
  SymbolReplacer symbol_replacer;
  TokenExtractor extractor;

  // Extract all of the grammar's tokens into the lexical grammar.
  vector<Variable> processed_variables;
  for (const auto &variable : grammar.variables) {
    processed_variables.push_back({
      variable.name,
      variable.type,
      extractor.apply(variable.rule)
    });
  }

  vector<Variable> processed_external_tokens;
  for (const auto &external_token : grammar.external_tokens) {
    processed_external_tokens.push_back(Variable{
      external_token.name,
      external_token.type,
      extractor.apply(external_token.rule),
    });
  }

  for (const auto &extracted_token : extractor.tokens) {
    auto expansion = expand_token(extracted_token.rule);
    if (expansion.error) return make_tuple(
      syntax_grammar,
      lexical_grammar,
      expansion.error
    );
    lexical_grammar.variables.push_back({
      extracted_token.name,
      extracted_token.type,
      expansion.rule,
      extracted_token.type == VariableTypeAnonymous
    });
  }

  // If a variable's entire rule was extracted as a token and that token didn't
  // appear within any other rule, then remove that variable from the syntax
  // grammar, giving its name to the token in the lexical grammar. Any symbols
  // that pointed to that variable will need to be updated to point to the
  // variable in the lexical grammar. Symbols that pointed to later variables
  // will need to have their indices decremented.
  size_t i = -1;
  for (const auto &variable : processed_variables) {
    i++;
    if (i > 0 && variable.rule.is<Symbol>()) {
      auto symbol = variable.rule.get_unchecked<Symbol>();
      if (symbol.is_terminal() && extractor.token_usage_counts[symbol.index] == 1) {
        lexical_grammar.variables[symbol.index].type = variable.type;
        lexical_grammar.variables[symbol.index].name = variable.name;
        symbol_replacer.replacements[Symbol::non_terminal(i)] = symbol;
        continue;
      }
    }
    syntax_grammar.variables.push_back(variable);
  }

  // Perform any replacements of symbols needed based on the previous step.
  for (auto &variable : syntax_grammar.variables) {
    variable.rule = symbol_replacer.apply(variable.rule);
  }

  for (const auto &conflict_set : grammar.expected_conflicts) {
    set<Symbol> new_conflict_set;
    for (const Symbol &symbol : conflict_set) {
      new_conflict_set.insert(symbol_replacer.replace_symbol(symbol));
    }
    syntax_grammar.expected_conflicts.insert(new_conflict_set);
  }

  for (const Symbol &symbol : grammar.variables_to_inline) {
    syntax_grammar.variables_to_inline.insert(symbol_replacer.replace_symbol(symbol));
  }

  // The grammar's extra tokens can be either token rules or symbols
  // pointing to token rules. If they are symbols, then they'll be handled by
  // the parser; add them to the syntax grammar's extra tokens. If they
  // are anonymous rules, they can be handled by the lexer; add them to the
  // lexical grammar's separator rules.
  for (const auto &rule : grammar.extra_tokens) {
    CompileError error = rule.match(
      [&](const Symbol &symbol) {
        Symbol new_symbol = symbol_replacer.replace_symbol(symbol);
        if (new_symbol.is_non_terminal()) {
          return CompileError(
            TSCompileErrorTypeInvalidExtraToken,
            "Non-token symbol " + syntax_grammar.variables[new_symbol.index].name + " can't be used as an extra token"
          );
        } else {
          syntax_grammar.extra_tokens.insert(new_symbol);
          return CompileError::none();
        }
      },

      [&](auto non_symbol) {
        auto expansion = expand_token(non_symbol);
        if (expansion.error) return CompileError(
          TSCompileErrorTypeInvalidExtraToken,
          "Non-token rule expression can't be used as an extra token"
        );
        int i = 0;
        for (const LexicalVariable &variable : lexical_grammar.variables) {
          if (variable.rule == expansion.rule) {
            syntax_grammar.extra_tokens.insert(Symbol::terminal(i));
            return CompileError::none();
          }
          i++;
        }

        lexical_grammar.separators.push_back(expansion.rule);
        return CompileError::none();
      }
    );

    if (error) return make_tuple(syntax_grammar, lexical_grammar, error);
  }

  for (const auto &external_token : processed_external_tokens) {
    Rule new_rule = symbol_replacer.apply(external_token.rule);

    if (!new_rule.is<Symbol>()) {
      return make_tuple(
        syntax_grammar,
        lexical_grammar,
        CompileError(
          TSCompileErrorTypeInvalidExternalToken,
          "Non-symbol rule expressions can't be used as external tokens"
        )
      );
    }

    Symbol symbol = new_rule.get_unchecked<Symbol>();
    if (symbol.is_non_terminal()) {
      return make_tuple(
        syntax_grammar,
        lexical_grammar,
        CompileError(
          TSCompileErrorTypeInvalidExternalToken,
          "Name '" + external_token.name + "' cannot be used for both an external token and a non-terminal rule"
        )
      );
    }

    if (symbol.is_external()) {
      syntax_grammar.external_tokens.push_back(ExternalToken{
        external_token.name,
        external_token.type,
        rules::NONE(),
      });
    } else {
      syntax_grammar.external_tokens.push_back(ExternalToken{
        lexical_grammar.variables[symbol.index].name,
        external_token.type,
        symbol,
      });
    }
  }

  syntax_grammar.word_token = symbol_replacer.replace_symbol(grammar.word_token);
  if (syntax_grammar.word_token.is_non_terminal()) {
    return make_tuple(
      syntax_grammar,
      lexical_grammar,
      CompileError(
        TSCompileErrorTypeInvalidWordRule,
        "Word rules must be tokens"
      )
    );
  }

  return make_tuple(syntax_grammar, lexical_grammar, CompileError::none());
}

}  // namespace prepare_grammar
}  // namespace tree_sitter
