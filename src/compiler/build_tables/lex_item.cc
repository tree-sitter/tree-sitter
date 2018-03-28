#include "compiler/build_tables/lex_item.h"
#include <unordered_set>
#include "compiler/build_tables/lex_item_transitions.h"
#include "compiler/build_tables/rule_can_be_blank.h"
#include "compiler/rule.h"
#include "compiler/util/hash_combine.h"

namespace tree_sitter {
namespace build_tables {

using std::map;
using std::string;
using std::unordered_set;
using rules::CharacterSet;
using rules::Symbol;
using rules::Metadata;

LexItem::LexItem(const rules::Symbol &lhs, const rules::Rule &rule)
    : lhs(lhs), rule(rule) {}

bool LexItem::operator==(const LexItem &other) const {
  return lhs == other.lhs && rule == other.rule;
}

using CompletionStatus = LexItem::CompletionStatus;

static CompletionStatus get_completion_status(const rules::Rule &rule) {
  return rule.match(
    [](rules::Choice choice) {
      for (const auto &element : choice.elements) {
        auto status = get_completion_status(element);
        if (status.is_done) return status;
      }
      return CompletionStatus{false, PrecedenceRange()};
    },

    [](rules::Metadata metadata) {
      CompletionStatus result = get_completion_status(*metadata.rule);
      if (result.is_done && result.precedence.empty && metadata.params.has_precedence) {
        result.precedence.add(metadata.params.precedence);
      }
      return result;
    },

    [](rules::Repeat repeat) {
      return get_completion_status(*repeat.rule);
    },

    [](rules::Seq sequence) {
      CompletionStatus left_status = get_completion_status(*sequence.left);
      if (left_status.is_done) {
        return get_completion_status(*sequence.right);
      } else {
        return CompletionStatus{false, PrecedenceRange()};
      }
    },

    [](rules::Blank blank) {
      return CompletionStatus{true, PrecedenceRange()};
    },

    [](rules::CharacterSet) {
      return CompletionStatus{false, PrecedenceRange()};
    },

    [](auto) {
      return CompletionStatus{false, PrecedenceRange()};
    }
  );
}


LexItem::CompletionStatus LexItem::completion_status() const {
  return get_completion_status(rule);
}

LexItemSet::LexItemSet() {}

LexItemSet::LexItemSet(const unordered_set<LexItem> &entries)
    : entries(entries) {}

bool LexItemSet::operator==(const LexItemSet &other) const {
  return entries == other.entries;
}

bool LexItem::is_in_separators() const {
  if (!rule.is<Metadata>()) return false;
  auto &metadata = rule.get_unchecked<Metadata>();
  return !metadata.params.is_main_token;
}

bool LexItemSet::has_items_in_separators() const {
  for (const LexItem &item : entries) {
    if (item.is_in_separators()) return true;
  }
  return false;
}

LexItemSet::TransitionMap LexItemSet::transitions() const {
  TransitionMap result;
  for (const LexItem &item : entries) {
    lex_item_transitions(&result, item);
  }
  return result;
}

bool LexItemSet::Transition::operator==(const LexItemSet::Transition &other) const {
  return destination == other.destination && precedence == other.precedence &&
         in_main_token == other.in_main_token;
}

}  // namespace build_tables
}  // namespace tree_sitter

namespace std {

using tree_sitter::util::hash_combine;
using tree_sitter::util::symmetric_hash_combine;
using tree_sitter::build_tables::LexItem;
using tree_sitter::build_tables::LexItemSet;

size_t hash<LexItem>::operator()(const LexItem &item) const {
  size_t result = 0;
  hash_combine(&result, item.lhs.index);
  hash_combine(&result, item.rule);
  return result;
}

size_t hash<LexItemSet>::operator()(const LexItemSet &item_set) const {
  size_t result = 0;
  hash_combine(&result, item_set.entries.size());
  for (const auto &item : item_set.entries)
    symmetric_hash_combine(&result, item);
  return result;
}

}  // namespace std
