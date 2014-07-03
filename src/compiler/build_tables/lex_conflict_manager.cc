#include "compiler/build_tables/lex_conflict_manager.h"
#include <vector>
#include <map>
#include <string>
#include <set>
#include "compiler/util/string_helpers.h"
#include "compiler/prepared_grammar.h"

namespace tree_sitter {
    namespace build_tables {
        using std::string;
        using std::to_string;
        using std::map;
        using std::set;
        using std::vector;

        LexConflictManager::LexConflictManager(const LexicalGrammar &grammar) :
            grammar(grammar) {}

        bool LexConflictManager::resolve_lex_action(const LexAction &old_action,
                                                    const LexAction &new_action) {
            if (new_action.type < old_action.type)
                return !resolve_lex_action(new_action, old_action);

            switch (old_action.type) {
                case LexActionTypeError:
                    return true;
                case LexActionTypeAccept: {
                    int old_precedence = *old_action.precedence_values.begin();
                    switch (new_action.type) {
                        case LexActionTypeAccept: {
                            int new_precedence = *new_action.precedence_values.begin();
                            if (new_precedence > old_precedence) {
                                return true;
                            } else if (new_precedence < old_precedence) {
                                return false;
                            } else {
                                return new_action.symbol.index < old_action.symbol.index;
                            }
                        }
                        case LexActionTypeAdvance: {
                           return true;
                        }
                        default:
                            return false;
                    }

                    return true;
                }
                default:
                    return false;
            }
        }
    }
}
