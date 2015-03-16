#include "compiler/build_tables/lex_conflict_manager.h"
#include "compiler/parse_table.h"
#include "compiler/rules/built_in_symbols.h"
#include <utility>

namespace tree_sitter {
namespace build_tables {

LexConflictManager::LexConflictManager(const LexicalGrammar &grammar) :
  grammar(grammar) {}

bool LexConflictManager::resolve(const LexAction &new_action, const LexAction &old_action) const {
  if (new_action.type < old_action.type)
    return !resolve(old_action, new_action);

  switch (old_action.type) {
    case LexActionTypeError:
      return true;

    case LexActionTypeAccept: {
      int old_precedence = *old_action.precedence_values.begin();

      switch (new_action.type) {
        case LexActionTypeAccept: {
          int new_precedence = *new_action.precedence_values.begin();
          if (new_precedence > old_precedence)
            return true;
          else if (new_precedence < old_precedence)
            return false;
          else
            return new_action.symbol.index < old_action.symbol.index;
        }

        case LexActionTypeAdvance:
          return true;

        default:
          return false;
      }
      return true;
    }

    default:
      return false;
  }
}

}  // namespace build_tables
}  // namespace tree_sitter
