#include "compiler/build_tables/lex_conflict_manager.h"
#include <vector>
#include <map>
#include <string>
#include <set>
#include "compiler/util/string_helpers.h"

namespace tree_sitter {
    namespace build_tables {
        using std::string;
        using std::to_string;
        using std::map;
        using std::set;
        using std::vector;

        LexConflictManager::LexConflictManager(const PreparedGrammar &grammar) :
            grammar(grammar) {}

        bool LexConflictManager::resolve_lex_action(const LexAction &old_action,
                                                    const LexAction &new_action) {
            switch (old_action.type) {
                case LexActionTypeError:
                    return true;
                case LexActionTypeAccept:
                    if (new_action.precedence > old_action.precedence) {
                        return true;
                    } else if (new_action.precedence < old_action.precedence) {
                        return false;
                    } else {
                        return new_action.symbol.index < old_action.symbol.index;
                    }
                default:
                    return false;
            }
        }
    }
}
