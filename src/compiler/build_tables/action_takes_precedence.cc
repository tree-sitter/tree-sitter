#include "compiler/build_tables/action_takes_precedence.h"

namespace tree_sitter {
namespace build_tables {

using std::pair;

pair<bool, bool> action_takes_precedence(const ParseAction &new_action,
                                         const ParseAction &old_action,
                                         const rules::Symbol &symbol,
                                         const SyntaxGrammar &grammar) {
  if (new_action.type < old_action.type) {
    auto opposite =
        action_takes_precedence(old_action, new_action, symbol, grammar);
    return { !opposite.first, opposite.second };
  }

  bool has_precedence = false, has_conflict = false;

  switch (old_action.type) {
    case ParseActionTypeError:
      has_precedence = true;
      break;

    case ParseActionTypeShift: {
      int min_precedence = *old_action.precedence_values.begin();
      int max_precedence = *old_action.precedence_values.rbegin();
      switch (new_action.type) {
        case ParseActionTypeReduce: {
          int new_precedence = *new_action.precedence_values.rbegin();
          if (new_precedence < max_precedence) {
            if (new_precedence > min_precedence)
              has_conflict = true;
          } else if (new_precedence > max_precedence) {
            has_precedence = true;
          } else {
            has_conflict = true;
          }
          break;
        }
        default:
          break;
      }
      break;
    }

    case ParseActionTypeReduce:
      switch (new_action.type) {
        case ParseActionTypeReduce: {
          int old_precedence = *old_action.precedence_values.begin();
          int new_precedence = *new_action.precedence_values.begin();
          if (new_precedence > old_precedence) {
            has_precedence = true;
          } else if (new_precedence == old_precedence) {
            has_precedence = new_action.symbol.index < old_action.symbol.index;
            has_conflict = true;
          }
          break;
        }
        default:
          break;
      }

    default:
      break;
  }

  return { has_precedence, has_conflict };
}

}  // namespace build_tables
}  // namespace tree_sitter
