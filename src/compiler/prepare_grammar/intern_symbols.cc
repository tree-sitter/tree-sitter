#include "compiler/prepare_grammar/intern_symbols.h"
#include <memory>
#include <vector>
#include <set>
#include "tree_sitter/compiler.h"
#include "compiler/rules/visitor.h"
#include "compiler/rules/blank.h"
#include "compiler/rules/named_symbol.h"
#include "compiler/rules/symbol.h"

namespace tree_sitter {
namespace prepare_grammar {

using std::string;
using std::vector;
using std::set;
using std::pair;
using std::make_shared;

class InternSymbols : public rules::IdentityRuleFn {
  using rules::IdentityRuleFn::apply_to;

  rule_ptr apply_to(const rules::NamedSymbol *rule) {
    auto result = symbol_for_rule_name(rule->name);
    if (!result.get()) {
      missing_rule_name = rule->name;
      return rules::Blank::build();
    }
    return result;
  }

 public:
  std::shared_ptr<rules::Symbol> symbol_for_rule_name(string rule_name) {
    for (size_t i = 0; i < grammar.rules().size(); i++)
      if (grammar.rules()[i].first == rule_name)
        return make_shared<rules::Symbol>(i);
    return nullptr;
  }

  explicit InternSymbols(const Grammar &grammar) : grammar(grammar) {}
  const Grammar grammar;
  string missing_rule_name;
};

const GrammarError *missing_rule_error(string rule_name) {
  return new GrammarError(GrammarErrorTypeUndefinedSymbol,
                          "Undefined rule '" + rule_name + "'");
}

pair<InternedGrammar, const GrammarError *> intern_symbols(const Grammar &grammar) {
  InternedGrammar result;
  InternSymbols interner(grammar);

  for (auto &pair : grammar.rules()) {
    auto new_rule = interner.apply(pair.second);
    if (!interner.missing_rule_name.empty())
      return { result, missing_rule_error(interner.missing_rule_name) };
    result.rules.push_back({ pair.first, new_rule });
  }

  for (auto &rule : grammar.ubiquitous_tokens()) {
    auto new_rule = interner.apply(rule);
    if (!interner.missing_rule_name.empty())
      return { result, missing_rule_error(interner.missing_rule_name) };
    result.ubiquitous_tokens.insert(new_rule);
  }

  for (auto &names : grammar.expected_conflicts()) {
    set<rules::Symbol> entry;
    for (auto &name : names) {
      auto symbol = interner.symbol_for_rule_name(name);
      if (symbol.get())
        entry.insert(*symbol);
    }
    result.expected_conflicts.insert(entry);
  }

  return { result, nullptr };
}

}  // namespace prepare_grammar
}  // namespace tree_sitter
