#include "compiler/prepare_grammar/intern_symbols.h"
#include <memory>
#include <vector>
#include <cassert>
#include <set>
#include "tree_sitter/compiler.h"
#include "compiler/grammar.h"
#include "compiler/rule.h"

namespace tree_sitter {
namespace prepare_grammar {

using std::string;
using std::vector;
using std::set;
using std::pair;
using rules::Symbol;
using rules::Rule;

class SymbolInterner {
 public:
  Rule apply(const Rule &rule) {
    return rule.match(
      [&](const rules::Blank &blank) -> Rule {
        return blank;
      },

      [&](const rules::NamedSymbol &symbol) {
        return intern_symbol(symbol);
      },

      [&](const rules::String &string) {
        return string;
      },

      [&](const rules::Pattern &pattern) {
        return pattern;
      },

      [&](const rules::Choice &choice) {
        vector<rules::Rule> elements;
        for (const auto &element : choice.elements) {
          elements.push_back(apply(element));
        }
        return rules::Choice{elements};
      },

      [&](const rules::Seq &sequence) {
        return rules::Seq{apply(*sequence.left), apply(*sequence.right)};
      },

      [&](const rules::Repeat &repeat) {
        return rules::Repeat{apply(*repeat.rule)};
      },

      [&](const rules::Metadata &metadata) {
        return rules::Metadata{apply(*metadata.rule), metadata.params};
      },

      [](auto) {
        assert(!"Unexpected rule type");
        return rules::Blank{};
      }
    );
  }

  Symbol intern_symbol(rules::NamedSymbol named_symbol) {
    for (size_t i = 0; i < grammar.variables.size(); i++) {
      if (grammar.variables[i].name == named_symbol.value) {
        return Symbol::non_terminal(i);
      }
    }

    for (size_t i = 0; i < grammar.external_tokens.size(); i++) {
      if (grammar.external_tokens[i] == named_symbol) {
        return Symbol::external(i);
      }
    }

    missing_rule_name = named_symbol.value;
    return rules::NONE();
  }

  explicit SymbolInterner(const InputGrammar &grammar) : grammar(grammar) {}
  const InputGrammar &grammar;
  string missing_rule_name;
};

CompileError missing_rule_error(string rule_name) {
  return CompileError(TSCompileErrorTypeUndefinedSymbol,
                      "Undefined rule '" + rule_name + "'");
}

pair<InternedGrammar, CompileError> intern_symbols(const InputGrammar &grammar) {
  InternedGrammar result;

  SymbolInterner interner(grammar);

  for (const Rule &external_token : grammar.external_tokens) {
    string external_token_name;
    VariableType external_token_type = VariableTypeAnonymous;
    external_token.match(
      [&](rules::NamedSymbol named_symbol) {
        external_token_name = named_symbol.value;
        if (external_token_name[0] == '_') {
          external_token_type = VariableTypeHidden;
        } else {
          external_token_type =VariableTypeNamed;
        }
      },
      [](auto rule) {}
    );

    auto new_rule = interner.apply(external_token);
    if (!interner.missing_rule_name.empty()) {
      return { result, missing_rule_error(interner.missing_rule_name) };
    }

    result.external_tokens.push_back(Variable{
      external_token_name,
      external_token_type,
      new_rule,
    });
  }

  if (grammar.variables[0].name[0] == '_') {
    return {result, CompileError(TSCompileErrorTypeInvalidRuleName, "A grammar's start rule must be visible.")};
  }

  for (auto &variable : grammar.variables) {
    auto new_rule = interner.apply(variable.rule);
    if (!interner.missing_rule_name.empty()) {
      return { result, missing_rule_error(interner.missing_rule_name) };
    }

    result.variables.push_back(Variable{
      variable.name,
      variable.name[0] == '_' ? VariableTypeHidden : VariableTypeNamed,
      new_rule
    });
  }

  for (auto &rule : grammar.extra_tokens) {
    auto new_rule = interner.apply(rule);
    if (!interner.missing_rule_name.empty()) {
      return { result, missing_rule_error(interner.missing_rule_name) };
    }
    result.extra_tokens.push_back(new_rule);
  }

  for (auto &expected_conflict : grammar.expected_conflicts) {
    set<rules::Symbol> entry;
    for (auto &named_symbol : expected_conflict) {
      auto symbol = interner.intern_symbol(named_symbol);
      if (symbol != rules::NONE()) {
        entry.insert(symbol);
      }
    }
    result.expected_conflicts.insert(entry);
  }

  for (auto &named_symbol : grammar.variables_to_inline) {
    auto symbol = interner.intern_symbol(named_symbol);
    if (symbol != rules::NONE()) {
      result.variables_to_inline.insert(symbol);
    }
  }

  result.word_token = interner.intern_symbol(grammar.word_token);

  return {result, CompileError::none()};
}

}  // namespace prepare_grammar
}  // namespace tree_sitter
