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
#include "compiler/util/hash_combine.h"

namespace tree_sitter {
namespace build_tables {

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

LexItem::CompletionStatus LexItem::completion_status() const {
  class GetCompletionStatus : public rules::RuleFn<CompletionStatus> {
   protected:
    CompletionStatus apply_to(const rules::Choice *rule) {
      for (const auto &element : rule->elements) {
        CompletionStatus status = apply(element);
        if (status.is_done) return status;
      }
      return { false, PrecedenceRange() };
    }

    CompletionStatus apply_to(const rules::Metadata *rule) {
      CompletionStatus result = apply(rule->rule);
      if (result.is_done && result.precedence.empty && rule->params.has_precedence) {
        result.precedence.add(rule->params.precedence);
      }
      return result;
    }

    CompletionStatus apply_to(const rules::Repeat *rule) {
      return apply(rule->content);
    }

    CompletionStatus apply_to(const rules::Blank *rule) {
      return { true, PrecedenceRange() };
    }

    CompletionStatus apply_to(const rules::Seq *rule) {
      CompletionStatus left_status = apply(rule->left);
      if (left_status.is_done) {
        return apply(rule->right);
      } else {
        return { false, PrecedenceRange() };
      }
    }
  };

  return GetCompletionStatus().apply(rule);
}

LexItemSet::LexItemSet() {}

LexItemSet::LexItemSet(const unordered_set<LexItem> &entries)
    : entries(entries) {}

bool LexItemSet::operator==(const LexItemSet &other) const {
  return entries == other.entries;
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
