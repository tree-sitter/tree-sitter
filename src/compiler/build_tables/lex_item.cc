#include "compiler/build_tables/lex_item.h"
#include "compiler/build_tables/get_metadata.h"
#include "compiler/build_tables/lex_item_transitions.h"
#include "compiler/rules/symbol.h"
#include <unordered_set>

namespace tree_sitter {
namespace build_tables {

using std::hash;
using std::map;
using std::string;
using std::unordered_set;
using rules::CharacterSet;
using rules::Symbol;

LexItem::LexItem(const rules::Symbol &lhs, const rule_ptr rule)
    : lhs(lhs), rule(rule) {}

bool LexItem::operator==(const LexItem &other) const {
  return (other.lhs == lhs) && other.rule->operator==(*rule);
}

bool LexItem::is_token_start() const {
  return get_metadata(rule, rules::START_TOKEN).max > 0;
}

size_t LexItem::Hash::operator()(const LexItem &item) const {
  return hash<Symbol>()(item.lhs) ^ hash<rule_ptr>()(item.rule);
}

size_t LexItemSet::Hash::operator()(const LexItemSet &item_set) const {
  size_t result = hash<size_t>()(item_set.entries.size());
  for (const auto &item : item_set.entries)
    result ^= LexItem::Hash()(item);
  return result;
}

LexItemSet::LexItemSet() {}

LexItemSet::LexItemSet(const unordered_set<LexItem, LexItem::Hash> &entries)
    : entries(entries) {}

bool LexItemSet::operator==(const LexItemSet &other) const {
  return entries == other.entries;
}

map<CharacterSet, LexItemSet> LexItemSet::transitions() const {
  map<CharacterSet, LexItemSet> result;
  for (const LexItem &item : entries)
    lex_item_transitions(&result, item);
  return result;
}

}  // namespace build_tables
}  // namespace tree_sitter
