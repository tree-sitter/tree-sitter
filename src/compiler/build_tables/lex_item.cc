#include "compiler/build_tables/lex_item.h"
#include <unordered_set>
#include "compiler/build_tables/lex_item_transitions.h"
#include "compiler/build_tables/rule_can_be_blank.h"
#include "compiler/rules/choice.h"
#include "compiler/rules/metadata.h"
#include "compiler/rules/seq.h"
#include "compiler/rules/symbol.h"
#include "compiler/rules/repeat.h"
#include "compiler/rules/visitor.h"

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
  class IsTokenStart : public rules::RuleFn<bool> {
    bool apply_to(const rules::Seq *rule) {
      return apply(rule->left) ||
             (rule_can_be_blank(rule->left) && apply(rule->right));
    }

    bool apply_to(const rules::Metadata *rule) {
      return (rule->value_for(rules::START_TOKEN).second) || apply(rule->rule);
    }

    bool apply_to(const rules::Choice *rule) {
      for (const rule_ptr &element : rule->elements)
        if (apply(element))
          return true;
      return false;
    }
  };

  return IsTokenStart().apply(rule);
}

LexItem::CompletionStatus LexItem::completion_status() const {
  class GetCompletionStatus : public rules::RuleFn<CompletionStatus> {
   protected:
    CompletionStatus apply_to(const rules::Choice *rule) {
      for (const auto &element : rule->elements) {
        CompletionStatus status = apply(element);
        if (status.is_done)
          return status;
      }
      return { false, PrecedenceRange(), false };
    }

    CompletionStatus apply_to(const rules::Metadata *rule) {
      CompletionStatus result = apply(rule->rule);
      if (result.is_done) {
        if (result.precedence.empty && rule->value_for(rules::PRECEDENCE).second)
          result.precedence.add(rule->value_for(rules::PRECEDENCE).first);
        if (rule->value_for(rules::IS_STRING).second)
          result.is_string = true;
      }
      return result;
    }

    CompletionStatus apply_to(const rules::Repeat *rule) {
      return apply(rule->content);
    }

    CompletionStatus apply_to(const rules::Blank *rule) {
      return { true, PrecedenceRange(), false };
    }

    CompletionStatus apply_to(const rules::Seq *rule) {
      CompletionStatus left_status = apply(rule->left);
      if (left_status.is_done)
        return apply(rule->right);
      else
        return { false, PrecedenceRange(), false };
    }
  };

  return GetCompletionStatus().apply(rule);
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

LexItemSet::TransitionMap LexItemSet::transitions() const {
  TransitionMap result;
  for (const LexItem &item : entries)
    lex_item_transitions(&result, item);
  return result;
}

bool LexItemSet::Transition::operator==(const LexItemSet::Transition &other) const {
  return destination == other.destination && precedence == other.precedence;
}

}  // namespace build_tables
}  // namespace tree_sitter
