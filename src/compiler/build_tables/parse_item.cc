#include "compiler/build_tables/parse_item.h"
#include <string>
#include "compiler/syntax_grammar.h"
#include "compiler/rule.h"
#include "compiler/util/hash_combine.h"

namespace tree_sitter {
namespace build_tables {

using std::map;
using std::pair;
using std::string;
using std::to_string;
using rules::Symbol;
using rules::Associativity;
using util::hash_combine;

ParseItem::ParseItem() : variable_index(-1), production(nullptr), step_index(0) {}

ParseItem::ParseItem(const Symbol &lhs, const Production &production,
                     unsigned int step_index)
    : variable_index(lhs.index),
      production(&production),
      step_index(step_index) {}

bool ParseItem::operator==(const ParseItem &other) const {
  if (step_index != other.step_index) return false;
  if (variable_index != other.variable_index) return false;
  if (production->size() != other.production->size()) return false;
  for (size_t i = 0; i < step_index; i++) {
    if (production->at(i).alias != other.production->at(i).alias) return false;
  }
  if (is_done()) {
    if (!production->empty()) {
      if (production->back().precedence != other.production->back().precedence) return false;
      if (production->back().associativity != other.production->back().associativity) return false;
    }
  } else {
    for (size_t i = step_index, n = production->size(); i < n; i++) {
      if (production->at(i) != other.production->at(i)) return false;
    }
  }
  return true;
}

bool ParseItem::operator<(const ParseItem &other) const {
  if (step_index < other.step_index) return true;
  if (other.step_index < step_index) return false;
  if (variable_index < other.variable_index) return true;
  if (other.variable_index < variable_index) return false;
  if (production->size() < other.production->size()) return true;
  if (other.production->size() < production->size()) return false;
  for (size_t i = 0; i < step_index; i++) {
    if (production->at(i).alias < other.production->at(i).alias) return true;
    if (other.production->at(i).alias < production->at(i).alias) return false;
  }
  if (is_done()) {
    if (!production->empty()) {
      if (production->back().precedence < other.production->back().precedence) return true;
      if (other.production->back().precedence < production->back().precedence) return false;
      if (production->back().associativity < other.production->back().associativity) return true;
      if (other.production->back().associativity < production->back().associativity) return false;
    }
  } else {
    for (size_t i = step_index, n = production->size(); i < n; i++) {
      if (production->at(i) < other.production->at(i)) return true;
      if (other.production->at(i) < production->at(i)) return false;
    }
  }
  return false;
}

Symbol ParseItem::lhs() const {
  return Symbol{variable_index, Symbol::NonTerminal};
}

bool ParseItem::is_done() const {
  return step_index >= production->size();
}

int ParseItem::precedence() const {
  if (is_done()) {
    if (production->empty()) {
      return 0;
    } else {
      return production->back().precedence;
    }
  } else {
    return production->at(step_index).precedence;
  }
}

int ParseItem::dynamic_precedence() const {
  return production->dynamic_precedence;
}

rules::Associativity ParseItem::associativity() const {
  if (is_done()) {
    if (production->empty()) {
      return rules::AssociativityNone;
    } else {
      return production->back().associativity;
    }
  } else {
    return production->at(step_index).associativity;
  }
}

Symbol ParseItem::next_symbol() const {
  if (step_index >= production->size())
    return rules::NONE();
  else
    return production->at(step_index).symbol;
}

bool ParseItemSet::operator==(const ParseItemSet &other) const {
  return entries == other.entries;
}

size_t ParseItemSet::unfinished_item_signature() const {
  size_t result = 0;
  ParseItem previous_item;
  for (auto &pair : entries) {
    const ParseItem &item = pair.first;
    if (item.step_index < item.production->size() &&
        (item.variable_index != previous_item.variable_index ||
         item.step_index != previous_item.step_index)) {
      hash_combine(&result, item.variable_index);
      hash_combine(&result, item.step_index);
      previous_item = item;
    }
  }
  return result;
}

void ParseItemSet::add(const ParseItemSet &other) {
  for (const auto &pair : other.entries)
    entries[pair.first].insert_all(pair.second);
}

}  // namespace build_tables
}  // namespace tree_sitter

namespace std {

using tree_sitter::build_tables::ParseItem;
using tree_sitter::build_tables::ParseItemSet;
using tree_sitter::util::hash_combine;

template <>
struct hash<ParseItem> {
  size_t operator()(const ParseItem &item) const {
    size_t result = 0;
    hash_combine(&result, item.variable_index);
    hash_combine(&result, item.step_index);
    hash_combine(&result, item.production->dynamic_precedence);
    hash_combine(&result, item.production->size());
    for (size_t i = 0; i < item.step_index; i++) {
      hash_combine(&result, item.production->at(i).alias.value);
      hash_combine(&result, item.production->at(i).alias.is_named);
    }
    if (item.is_done()) {
      if (!item.production->empty()) {
        hash_combine(&result, item.production->back().precedence);
        hash_combine<unsigned>(&result, item.production->back().associativity);
      }
    } else {
      for (size_t i = item.step_index, n = item.production->size(); i < n; i++) {
        auto &step = item.production->at(i);
        hash_combine(&result, step.symbol);
        hash_combine(&result, step.precedence);
        hash_combine<unsigned>(&result, step.associativity);
      }
    }
    return result;
  }
};

size_t hash<ParseItemSet>::operator()(const ParseItemSet &item_set) const {
  size_t result = 0;
  hash_combine(&result, item_set.entries.size());
  for (auto &pair : item_set.entries) {
    const ParseItem &item = pair.first;
    const auto &lookahead_set = pair.second;

    hash_combine(&result, item);
    hash_combine(&result, lookahead_set.size());
    lookahead_set.for_each([&result](Symbol symbol) {
      hash_combine(&result, symbol);
      return true;
    });
  }
  return result;
}

}  // namespace std
