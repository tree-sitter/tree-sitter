#include "compiler/build_tables/action_takes_precedence.h"

#include <iostream>

namespace tree_sitter {
namespace build_tables {

using std::pair;

pair<bool, ConflictType>
action_takes_precedence(const ParseAction &new_action,
                        const ParseAction &old_action,
                        const rules::Symbol &symbol) {
  if (new_action.type < old_action.type) {
    auto opposite =
        action_takes_precedence(old_action, new_action, symbol);
    return { !opposite.first, opposite.second };
  }

  switch (old_action.type) {
    case ParseActionTypeError:
      return { true, ConflictTypeNone };

    case ParseActionTypeShift:
      if (new_action.type == ParseActionTypeReduce) {
        int min_precedence = *old_action.precedence_values.begin();
        int max_precedence = *old_action.precedence_values.rbegin();
        int new_precedence = *new_action.precedence_values.rbegin();
        if (new_precedence < min_precedence)
          return { false, ConflictTypeResolved };
        else if (new_precedence > max_precedence)
          return { true, ConflictTypeResolved };
        else {

          // TODO: Add associativity annotations. In the event of a precedence
          // tie, return ConflictTypeError unless there is an associativity
          // annotation to break the tie.
          return { false, ConflictTypeResolved };
        }
      }
      break;

    case ParseActionTypeReduce:
      if (new_action.type == ParseActionTypeReduce) {
        int old_precedence = *old_action.precedence_values.begin();
        int new_precedence = *new_action.precedence_values.begin();
        if (new_precedence > old_precedence) {
          return { true, ConflictTypeResolved };
        } else if (new_precedence < old_precedence) {
          return { false, ConflictTypeResolved };
        } else {
          return { false, ConflictTypeError };
        }
      }

    default:
      break;
  }

  return { false, ConflictTypeNone };
}

bool action_takes_precedence(const LexAction &new_action,
                             const LexAction &old_action) {
  if (new_action.type < old_action.type)
    return !action_takes_precedence(old_action, new_action);

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
