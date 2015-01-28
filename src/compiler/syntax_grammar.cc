#include "compiler/syntax_grammar.h"
#include <vector>
#include <string>
#include <utility>
#include "compiler/rules/symbol.h"
#include "compiler/rules/built_in_symbols.h"

namespace tree_sitter {

using std::string;
using std::to_string;
using std::pair;
using std::vector;
using std::set;

static const vector<Production> START_PRODUCTIONS({
  Production({ {rules::Symbol(0), 0, -1}, { rules::NONE(), 0, -2} })
});

static const vector<Production> NO_PRODUCTIONS({});

bool ProductionEntry::operator==(const ProductionEntry &other) const {
  return symbol == other.symbol && precedence == other.precedence &&
    rule_id == other.rule_id;
}

Production::Production(const vector<ProductionEntry> &entries) : entries(entries) {}

size_t Production::symbol_count() const {
  return entries.size() - 1;
}

const ProductionEntry &Production::operator[](int i) const {
  return entries[i];
}

SyntaxGrammar::SyntaxGrammar() {}

SyntaxGrammar::SyntaxGrammar(
    const vector<pair<string, vector<Production>>> &rules,
    const vector<pair<string, vector<Production>>> &aux_rules,
    const set<rules::Symbol> &ubiquitous_tokens)
    : rules(rules), aux_rules(aux_rules), ubiquitous_tokens(ubiquitous_tokens) {}

const string &SyntaxGrammar::rule_name(const rules::Symbol &symbol) const {
  return symbol.is_auxiliary() ? aux_rules[symbol.index].first
                               : rules[symbol.index].first;
}

const vector<Production> &SyntaxGrammar::productions(const rules::Symbol &symbol) const {
  if (symbol == rules::START())
    return START_PRODUCTIONS;
  if (symbol.is_built_in() || symbol.is_token())
    return NO_PRODUCTIONS;
  if (symbol.is_auxiliary())
    return aux_rules[symbol.index].second;
  else
    return rules[symbol.index].second;
}

std::ostream &operator<<(std::ostream &stream, const ProductionEntry &entry) {
  return stream << string("(entry symbol:") << entry.symbol <<
    string(" precedence: ") << to_string(entry.precedence) <<
    string(" id: ") << to_string(entry.rule_id) << string(")");
}

std::ostream &operator<<(std::ostream &stream, const Production &production) {
  stream << string("(production entries: (");
  bool started = false;
  for (const auto &entry : production.entries) {
    if (started) stream << string(" ");
    stream << entry;
    started = true;
  }
  return stream << string(")");
}

}  // namespace tree_sitter
