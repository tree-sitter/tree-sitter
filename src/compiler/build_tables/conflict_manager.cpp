#include "compiler/build_tables/conflict_manager.h"
#include <vector>

namespace tree_sitter {
    namespace build_tables {
        using rules::Symbol;
        using std::vector;
        using std::string;

        string message_for_action(const ParseAction &action) {
            switch (action.type) {
                case ParseActionTypeShift:
                    return "shift";
                case ParseActionTypeReduce:
                    return "reduce " + action.symbol.name;
                case ParseActionTypeAccept:
                    return "accept";
                case ParseActionTypeError:
                    return "error";
                    break;
            }
        }

        void ConflictManager::record_conflict(const rules::Symbol &symbol, const ParseAction &left, const ParseAction &right) {
            conflicts_.push_back(Conflict(symbol.name + ": " +
                                          message_for_action(left) +
                                          " / " +
                                          message_for_action(right)));
        }

        ConflictManager::ConflictManager(const PreparedGrammar &parse_grammar, const PreparedGrammar &lex_grammar) :
            parse_grammar(parse_grammar),
            lex_grammar(lex_grammar) {}

        ParseAction ConflictManager::resolve_parse_action(const rules::Symbol &symbol, ParseAction left, ParseAction right) {
            if (right.type < left.type) {
                ParseAction swap = right;
                right = left;
                left = swap;
            }

            switch (left.type) {
                case ParseActionTypeError:
                    return right;
                case ParseActionTypeShift:
                    switch (right.type) {
                        case ParseActionTypeShift:
                            record_conflict(symbol, left, right);
                            return left;
                        case ParseActionTypeReduce:
                            record_conflict(symbol, left, right);
                            return left;
                        default:
                            return left;
                    }
                case ParseActionTypeReduce:
                    switch (right.type) {
                        case ParseActionTypeReduce: {
                            size_t left_index = parse_grammar.index_of(left.symbol);
                            size_t right_index = parse_grammar.index_of(right.symbol);
                            return (right_index < left_index) ? right : left;
                        }
                        default:
                            return right;
                    }
                default:
                    return left;
            }
        }

        LexAction ConflictManager::resolve_lex_action(const LexAction &left, const LexAction &right) {
            switch (left.type) {
                case LexActionTypeError:
                    return right;
                case LexActionTypeAccept:
                    if (right.type == LexActionTypeAccept) {
                        size_t left_index = lex_grammar.index_of(left.symbol);
                        size_t right_index = lex_grammar.index_of(right.symbol);
                        return (right_index < left_index) ? right : left;
                    } else {
                        return left;
                    }
                default:
                    return left;
            }
        }

        const vector<Conflict> & ConflictManager::conflicts() const {
            return conflicts_;
        }
    }
}