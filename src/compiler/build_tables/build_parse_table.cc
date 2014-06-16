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

namespace tree_sitter {
    using std::pair;
    using std::string;
    using std::vector;
    using std::set;
    using std::unordered_map;
    using std::make_shared;
    using rules::Symbol;

    namespace build_tables {
        class ParseTableBuilder {
            const PreparedGrammar grammar;
            ParseConflictManager conflict_manager;
            unordered_map<const ParseItemSet, ParseStateId> parse_state_ids;
            SymTransitions sym_transitions;
            ParseTable parse_table;

            ParseStateId add_parse_state(const ParseItemSet &item_set) {
                auto pair = parse_state_ids.find(item_set);
                if (pair == parse_state_ids.end()) {
                    ParseStateId state_id = parse_table.add_state();
                    parse_state_ids[item_set] = state_id;
                    add_shift_actions(item_set, state_id);
                    add_ubiquitous_token_actions(item_set, state_id);
                    add_reduce_actions(item_set, state_id);
                    return state_id;
                } else {
                    return pair->second;
                }
            }

            void add_shift_actions(const ParseItemSet &item_set, ParseStateId state_id) {
                for (const auto &transition : sym_transitions(item_set, grammar)) {
                    const Symbol &symbol = transition.first;
                    const ParseItemSet &next_item_set = transition.second;
                    auto &actions = parse_table.states[state_id].actions;
                    auto current_action = actions.find(symbol);

                    set<int> precedence_values = precedence_values_for_item_set(next_item_set);
                    if (current_action == actions.end() ||
                        conflict_manager.resolve_parse_action(symbol, current_action->second, ParseAction::Shift(0, precedence_values))) {
                        ParseStateId new_state_id = add_parse_state(next_item_set);
                        parse_table.add_action(state_id, symbol, ParseAction::Shift(new_state_id, precedence_values));
                    }
                }
            }

            void add_ubiquitous_token_actions(const ParseItemSet &item_set, ParseStateId state_id) {
                for (const Symbol &symbol : grammar.ubiquitous_tokens()) {
                    auto &actions = parse_table.states[state_id].actions;
                    if (actions.find(symbol) == actions.end())
                        parse_table.add_action(state_id, symbol, ParseAction::Shift(state_id, { 0 }));
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
                        
                        for (auto &lookahead_sym : lookahead_symbols) {
                            auto current_actions = parse_table.states[state_id].actions;
                            auto current_action = current_actions.find(lookahead_sym);
                            if (current_action == current_actions.end() ||
                                conflict_manager.resolve_parse_action(lookahead_sym, current_action->second, action)) {
                                parse_table.add_action(state_id, lookahead_sym, action);
                            }
                        }
                    }
                }
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
            ParseTableBuilder(const PreparedGrammar &grammar, const PreparedGrammar &lex_grammar) :
                grammar(grammar),
                conflict_manager(ParseConflictManager(grammar, lex_grammar)) {}

            pair<ParseTable, vector<Conflict>> build() {
                ParseItem start_item(rules::START(), make_shared<Symbol>(0), 0);
                add_parse_state(item_set_closure(start_item, { rules::END_OF_INPUT() }, grammar));
                return { parse_table, conflict_manager.conflicts() };
            }
        };

        pair<ParseTable, vector<Conflict>>
        build_parse_table(const PreparedGrammar &grammar, const PreparedGrammar &lex_grammar) {
            return ParseTableBuilder(grammar, lex_grammar).build();
        }
    }
}
