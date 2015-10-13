#include "compiler/build_tables/parse_conflict_manager.h"
#include <utility>
#include "compiler/parse_table.h"
#include "compiler/rules/built_in_symbols.h"

namespace tree_sitter {
namespace build_tables {

using std::pair;
using std::vector;

ParseConflictManager::ParseConflictManager(const SyntaxGrammar &syntax_grammar)
    : syntax_grammar(syntax_grammar) {}

pair<bool, ConflictType> ParseConflictManager::resolve(
  const ParseAction &new_action, const ParseAction &old_action,
  const rules::Symbol &symbol) const {
  if (new_action.type < old_action.type) {
    auto opposite = resolve(old_action, new_action, symbol);
    return { !opposite.first, opposite.second };
  }

  switch (old_action.type) {
    case ParseActionTypeError:
    case ParseActionTypeShiftExtra:
    case ParseActionTypeReduceExtra:
      return { true, ConflictTypeNone };

    case ParseActionTypeShift:
      if (new_action.type == ParseActionTypeReduce) {
        int min_precedence = old_action.precedence_range.min;
        int max_precedence = old_action.precedence_range.max;
        int new_precedence = new_action.precedence_range.max;
        if (new_precedence < min_precedence ||
            (new_precedence == min_precedence &&
             min_precedence < max_precedence)) {
          return { false, ConflictTypeResolved };
        } else if (new_precedence > max_precedence ||
                   (new_precedence == max_precedence &&
                    min_precedence < max_precedence)) {
          return { true, ConflictTypeResolved };
        } else if (min_precedence == max_precedence) {
          switch (new_action.associativity) {
            case rules::AssociativityLeft:
              return { true, ConflictTypeResolved };
            case rules::AssociativityRight:
              return { false, ConflictTypeResolved };
            default:
              return { false, ConflictTypeUnresolved };
          }
        } else {
          return { false, ConflictTypeUnresolved };
        }
      }

    case ParseActionTypeReduce:
      if (new_action.type == ParseActionTypeReduce) {
        int old_precedence = old_action.precedence_range.min;
        int new_precedence = new_action.precedence_range.min;
        if (new_precedence > old_precedence) {
          return { true, ConflictTypeResolved };
        } else if (new_precedence < old_precedence) {
          return { false, ConflictTypeResolved };
        } else {
          return { false, ConflictTypeUnresolved };
        }
      }

    default:
      break;
  }

  return { false, ConflictTypeNone };
}

}  // namespace build_tables
}  // namespace tree_sitter
