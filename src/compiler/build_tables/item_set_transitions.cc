#include <set>
#include "compiler/build_tables/item_set_closure.h"
#include "compiler/build_tables/lex_item.h"
#include "compiler/build_tables/merge_transitions.h"
#include "compiler/build_tables/parse_item.h"
#include "compiler/build_tables/rule_transitions.h"
#include "compiler/syntax_grammar.h"
#include "compiler/rules/symbol.h"

namespace tree_sitter {
namespace build_tables {

using std::map;
using rules::CharacterSet;
using rules::Symbol;

map<Symbol, ParseItemSet> sym_transitions(const ParseItemSet &input_item_set,
                                          const SyntaxGrammar &grammar) {
  ParseItemSet item_set(item_set_closure(input_item_set, grammar));
  map<Symbol, ParseItemSet> result;
  for (const auto &pair : item_set) {
    const ParseItem &item = pair.first;
    const LookaheadSet &lookahead_symbols = pair.second;
    const Production &production =
      grammar.productions(item.lhs())[item.production_index];
    if (item.step_index == production.size())
      continue;

    const Symbol &symbol = production[item.step_index].symbol;
    unsigned int step = item.step_index + 1;
    int rule_id = step < production.size() ? production[step].rule_id : 0;
    ParseItem new_item(item.lhs(), item.production_index, step, rule_id);

    result[symbol][new_item] = lookahead_symbols;
  }

  return result;
}

map<CharacterSet, LexItemSet> char_transitions(const LexItemSet &item_set) {
  map<CharacterSet, LexItemSet> result;
  for (const LexItem &item : item_set) {
    for (auto &transition : char_transitions(item.rule)) {
      LexItem next_item(item.lhs, transition.second);
      merge_char_transition<LexItemSet>(
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
