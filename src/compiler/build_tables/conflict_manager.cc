#include "compiler/build_tables/conflict_manager.h"
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

        ConflictManager::ConflictManager(const PreparedGrammar &parse_grammar,
                                         const PreparedGrammar &lex_grammar) :
            parse_grammar(parse_grammar),
            lex_grammar(lex_grammar) {}

        bool ConflictManager::resolve_parse_action(const rules::Symbol &symbol,
                                                   const ParseAction &old_action,
                                                   const ParseAction &new_action) {
            if (new_action.type < old_action.type)
                return !resolve_parse_action(symbol, new_action, old_action);

            switch (old_action.type) {
                case ParseActionTypeError:
                    return true;
                case ParseActionTypeShift: {
                    int min_precedence = *old_action.precedence_values.begin();
                    int max_precedence = *old_action.precedence_values.rbegin();
                    switch (new_action.type) {
                        case ParseActionTypeReduce: {
                            int new_precedence = *new_action.precedence_values.rbegin();
                            if (max_precedence > new_precedence) {
                                if (min_precedence < new_precedence)
                                    record_conflict(symbol, old_action, new_action);
                                return false;
                            } else if (max_precedence < new_precedence) {
                                return true;
                            } else {
                                record_conflict(symbol, old_action, new_action);
                                return false;
                            }
                        }
                        default:
                            return false;
                    }
                }
                case ParseActionTypeReduce:
                    switch (new_action.type) {
                        case ParseActionTypeReduce: {
                            int old_precedence = *old_action.precedence_values.begin();
                            int new_precedence = *new_action.precedence_values.begin();
                            if (new_precedence > old_precedence) {
                                return true;
                            } else if (new_precedence < old_precedence) {
                                return false;
                            } else {
                                record_conflict(symbol, old_action, new_action);
                                return new_action.symbol.index < old_action.symbol.index;
                            }
                        }
                        default:
                            return false;
                    }
                default:
                    return false;
            }
        }

        bool ConflictManager::resolve_lex_action(const LexAction &old_action,
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

        const vector<Conflict> ConflictManager::conflicts() const {
            vector<Conflict> result;
            result.insert(result.end(), conflicts_.begin(), conflicts_.end());
            return result;
        }

        string precedence_string(const ParseAction &action) {
            string precedences = "(precedence ";
            bool started = false;
            for (auto value : action.precedence_values) {
                if (started) precedences += ", ";
                started = true;
                precedences += to_string(value);
            }
            return precedences + ")";
        }

        string message_for_action(const ParseAction &action, const PreparedGrammar &parse_grammar) {
            switch (action.type) {
                case ParseActionTypeShift:
                    return "shift " + precedence_string(action);
                case ParseActionTypeReduce: {
                    string name = parse_grammar.rule_name(action.symbol);
                    if (name == "")
                        return "ERROR" + to_string(action.symbol.index);
                    else
                        return "reduce " + name + " " + precedence_string(action);
                }
                case ParseActionTypeAccept:
                    return "accept";
                default:
                    return "error";
            }
        }

        void ConflictManager::record_conflict(const rules::Symbol &symbol,
                                              const ParseAction &left,
                                              const ParseAction &right) {
            string name = symbol.is_token() ?
                lex_grammar.rule_name(symbol) :
                parse_grammar.rule_name(symbol);
            conflicts_.insert(Conflict(name + ": " +
                                       message_for_action(left, parse_grammar) + " / " +
                                       message_for_action(right, parse_grammar)));
        }
    }
}
