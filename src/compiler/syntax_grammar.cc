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
  Production({ {rules::Symbol(0), 0, -1} }, 2)
});

static const vector<Production> NO_PRODUCTIONS({});

bool ProductionEntry::operator==(const ProductionEntry &other) const {
  return symbol == other.symbol && precedence == other.precedence &&
    rule_id == other.rule_id;
}

Production::Production(const vector<ProductionEntry> &entries, int last_rule_id) :
  entries(entries), end_rule_id(last_rule_id) {}

int Production::precedence_at(size_t index) const {
  if (index >= size())
    return 0;
  else
    return entries[index].precedence;
}

int Production::rule_id_at(size_t index) const {
  if (index >= size())
    return end_rule_id;
  else
    return entries[index].rule_id;
}

const rules::Symbol &Production::symbol_at(size_t index) const {
  return entries[index].symbol;
}

size_t Production::size() const {
  return entries.size();
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
  return stream << string(") end_rule_id: ") <<
    to_string(production.end_rule_id) << string(")");
}

}  // namespace tree_sitter
