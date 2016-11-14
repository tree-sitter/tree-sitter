#include "compiler/build_tables/lex_conflict_manager.h"
#include <utility>
#include "compiler/parse_table.h"
#include "compiler/rules/built_in_symbols.h"
#include "compiler/build_tables/lex_item.h"

namespace tree_sitter {
namespace build_tables {

bool LexConflictManager::resolve(const LexItemSet &item_set,
                                 const AdvanceAction &new_action,
                                 const AcceptTokenAction &old_action) {
  if (!old_action.is_present())
    return true;
  if (new_action.precedence_range.max >= old_action.precedence) {
    for (const LexItem &item : item_set.entries)
      possible_extensions[old_action.symbol.index].insert(item.lhs.index);
    return true;
  } else {
    return false;
  }
}

bool LexConflictManager::resolve(const AcceptTokenAction &new_action,
                                 const AcceptTokenAction &old_action) {
  if (!old_action.is_present())
    return true;

  int old_precedence = old_action.precedence;
  int new_precedence = new_action.precedence;

  bool result;
  if (new_precedence > old_precedence)
    result = true;
  else if (new_precedence < old_precedence)
    result = false;
  else if (new_action.is_string && !old_action.is_string)
    result = true;
  else if (old_action.is_string && !new_action.is_string)
    result = false;
  else if (new_action.symbol.index < old_action.symbol.index)
    result = true;
  else
    result = false;

  if (result)
    possible_homonyms[old_action.symbol.index].insert(new_action.symbol.index);
  else
    possible_homonyms[new_action.symbol.index].insert(old_action.symbol.index);

  return result;
}

}  // namespace build_tables
}  // namespace tree_sitter
