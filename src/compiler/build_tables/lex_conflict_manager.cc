#include "compiler/build_tables/lex_conflict_manager.h"
#include <utility>
#include "compiler/parse_table.h"
#include "compiler/rules/built_in_symbols.h"

namespace tree_sitter {
namespace build_tables {

bool LexConflictManager::resolve(const LexAction &new_action,
                                 const LexAction &old_action) {
  if (new_action.type < old_action.type)
    return !resolve(old_action, new_action);

  switch (old_action.type) {
    case LexActionTypeError:
      return true;

    case LexActionTypeAccept: {
      int old_precedence = old_action.precedence_range.min;

      switch (new_action.type) {
        case LexActionTypeAccept: {
          int new_precedence = new_action.precedence_range.min;

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
            fragile_tokens.insert(old_action.symbol);
          else
            fragile_tokens.insert(new_action.symbol);

          return result;
        }

        case LexActionTypeAdvance:
          if (old_precedence > new_action.precedence_range.max)
            return false;
          else
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
