#include "compiler/build_tables/build_parse_table.h"
#include <string>
#include <utility>
#include <map>
#include <set>
#include <unordered_map>
#include "compiler/prepared_grammar.h"
#include "compiler/rules/built_in_symbols.h"
#include "compiler/rules/symbol.h"
#include "compiler/build_tables/parse_conflict_manager.h"
#include "compiler/build_tables/parse_item.h"
#include "compiler/build_tables/item_set_closure.h"
#include "compiler/build_tables/item_set_transitions.h"
#include "compiler/build_tables/first_set.h"

namespace tree_sitter {
    using std::pair;
    using std::string;
    using std::vector;
    using std::set;
    using std::map;
    using std::unordered_map;
    using std::make_shared;
    using rules::Symbol;

    namespace build_tables {
        class ParseTableBuilder {
            const SyntaxGrammar grammar;
            ParseConflictManager conflict_manager;
            unordered_map<const ParseItemSet, ParseStateId> parse_state_ids;
            ParseTable parse_table;

            ParseStateId add_parse_state(const ParseItemSet &item_set) {
                auto pair = parse_state_ids.find(item_set);
                if (pair == parse_state_ids.end()) {
                    ParseStateId state_id = parse_table.add_state();
                    parse_state_ids[item_set] = state_id;
                    add_reduce_actions(item_set, state_id);
                    add_shift_actions(item_set, state_id);
                    add_ubiquitous_token_actions(state_id);
                    return state_id;
                } else {
                    return pair->second;
                }
            }

            void add_reduce_actions(const ParseItemSet &item_set, ParseStateId state_id) {
                for (const auto &pair : item_set) {
                    const ParseItem &item = pair.first;
                    const set<Symbol> &lookahead_symbols = pair.second;

                    if (item.is_done()) {
                        ParseAction action = (item.lhs == rules::START()) ?
                            ParseAction::Accept() :
                            ParseAction::Reduce(item.lhs, item.consumed_symbol_count, item.precedence());
                        for (auto &lookahead_sym : lookahead_symbols)
                            if (should_add_action(state_id, lookahead_sym, action))
                                parse_table.add_action(state_id, lookahead_sym, action);
                    }
                }
            }

            void add_shift_actions(const ParseItemSet &item_set, ParseStateId state_id) {
                for (const auto &transition : sym_transitions(item_set, grammar)) {
                    const Symbol &symbol = transition.first;
                    const ParseItemSet &next_item_set = transition.second;

                    ParseAction new_action = ParseAction::Shift(0, precedence_values_for_item_set(next_item_set));
                    if (should_add_action(state_id, symbol, new_action)) {
                        ParseStateId new_state_id = add_parse_state(next_item_set);
                        new_action.state_index = new_state_id;
                        parse_table.add_action(state_id, symbol, new_action);
                    }
                }
            }

            void add_ubiquitous_token_actions(ParseStateId state_id) {
                const map<Symbol, ParseAction> &actions = parse_table.states[state_id].actions;

                for (const Symbol &ubiquitous_symbol : grammar.ubiquitous_tokens) {
                    const auto &pair_for_symbol = actions.find(ubiquitous_symbol);

                    if (pair_for_symbol == actions.end()) {
                        parse_table.add_action(state_id, ubiquitous_symbol, ParseAction::ShiftExtra());
                    } else if (pair_for_symbol->second.type == ParseActionTypeShift) {
                        size_t shift_state_id = pair_for_symbol->second.state_index;
                        for (const auto &pair : actions) {
                            const Symbol &lookahead_sym = pair.first;
                            ParseAction reduce_extra = ParseAction::ReduceExtra(ubiquitous_symbol);
                            if (should_add_action(shift_state_id, lookahead_sym, reduce_extra))
                                parse_table.add_action(shift_state_id, lookahead_sym, reduce_extra);
                        }
                    }
                }
            }

            bool should_add_action(ParseStateId state_id, const Symbol &symbol, const ParseAction &action) {
                auto current_actions = parse_table.states[state_id].actions;
                auto current_action = current_actions.find(symbol);
                return (
                    current_action == current_actions.end() ||
                    conflict_manager.resolve_parse_action(symbol, current_action->second, action));
            }

            set<int> precedence_values_for_item_set(const ParseItemSet &item_set) {
                set<int> result;
                for (const auto &pair : item_set) {
                    const ParseItem &item = pair.first;
                    if (item.consumed_symbol_count > 0)
                        result.insert(item.precedence());
                }
                return result;
            }

        public:
            ParseTableBuilder(const SyntaxGrammar &grammar, const LexicalGrammar &lex_grammar) :
                grammar(grammar),
                conflict_manager(ParseConflictManager(grammar, lex_grammar)) {}

            pair<ParseTable, vector<Conflict>> build() {
                ParseItem start_item(rules::START(), make_shared<Symbol>(0), 0);
                add_parse_state(item_set_closure(start_item, { rules::END_OF_INPUT() }, grammar));
                return { parse_table, conflict_manager.conflicts() };
            }
        };

        pair<ParseTable, vector<Conflict>>
        build_parse_table(const SyntaxGrammar &grammar, const LexicalGrammar &lex_grammar) {
            return ParseTableBuilder(grammar, lex_grammar).build();
        }
    }
}
