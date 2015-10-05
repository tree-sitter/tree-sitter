#include "compiler/build_tables/lex_item.h"
#include "compiler/build_tables/get_metadata.h"
#include "compiler/build_tables/rule_transitions.h"
#include "compiler/build_tables/merge_transitions.h"
#include "compiler/rules/symbol.h"

namespace tree_sitter {
namespace build_tables {

using std::hash;
using std::map;
using std::string;
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

size_t LexItemSetHash::operator()(const LexItemSet &item_set) const {
  size_t result = hash<size_t>()(item_set.size());
  for (const auto &item : item_set)
    result ^= LexItem::Hash()(item);
  return result;
}

map<CharacterSet, LexItemSet> lex_item_set_transitions(const LexItemSet &item_set) {
  map<CharacterSet, LexItemSet> result;
  for (const LexItem &item : item_set) {
    for (auto &transition : rule_transitions(item.rule)) {
      LexItem next_item(item.lhs, transition.second);
      merge_transition<LexItemSet>(
        &result, { transition.first, LexItemSet({ next_item }) },
        [](LexItemSet *left, const LexItemSet *right) {
          left->insert(right->begin(), right->end());
        });
    }
  }
  return result;
}

}  // namespace build_tables
}  // namespace tree_sitter
