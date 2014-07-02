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

#include <iostream>

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
                    add_ubiquitous_token_actions(item_set, state_id);
                    return state_id;
                } else {
                    return pair->second;
                }
            }

            void add_shift_actions(const ParseItemSet &item_set, ParseStateId state_id) {
                map<Symbol, size_t> shifts;

                for (const auto &transition : sym_transitions(item_set, grammar)) {
                    const Symbol &symbol = transition.first;
                    const ParseItemSet &next_item_set = transition.second;

                    ParseAction new_action = ParseAction::Shift(0, precedence_values_for_item_set(next_item_set));
                    if (should_add_action(state_id, symbol, new_action)) {
                        ParseStateId new_state_id = add_parse_state(next_item_set);
                        new_action.state_index = new_state_id;
                        parse_table.add_action(state_id, symbol, new_action);

                        shifts.insert({ symbol, new_state_id });
                    }
                }

                for (auto &pair : shifts) {
                    const Symbol &shift_symbol = pair.first;
                    size_t new_state_id = pair.second;

                    if (grammar.ubiquitous_tokens.find(shift_symbol) != grammar.ubiquitous_tokens.end()) {
                        for (const auto &pair : parse_table.states[state_id].actions) {
                            const Symbol &lookahead_sym = pair.first;
                            ParseAction action = ParseAction::ReduceExtra(shift_symbol);
                            if (should_add_action(new_state_id, lookahead_sym, action))
                                parse_table.add_action(new_state_id, lookahead_sym, action);
                        }
                    }
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

            void add_ubiquitous_token_actions(const ParseItemSet &item_set, ParseStateId state_id) {
                for (const Symbol &symbol : grammar.ubiquitous_tokens) {
                    auto &actions = parse_table.states[state_id].actions;
                    if (actions.find(symbol) == actions.end())
                        parse_table.add_action(state_id, symbol, ParseAction::ShiftExtra());
                }
            }

            set<Symbol> first_set_for_item_set(const ParseItemSet &item_set) {
                set<Symbol> result;
                for (const auto &pair : item_set) {
                    auto new_set = first_set(pair.first.rule, grammar);
                    result.insert(new_set.begin(), new_set.end());
                }
                return result;
            }

            bool should_add_action(size_t state_id, const Symbol &symbol, const ParseAction &action) {
                auto current_actions = parse_table.states[state_id].actions;
                auto current_action = current_actions.find(symbol);
                return (
                    current_action == current_actions.end() ||
                    conflict_manager.resolve_parse_action(symbol, current_action->second, action)
                );
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
