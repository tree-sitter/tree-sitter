#include "spec_helper.h"
#include "parse_table_builder.h"
#include "parse_table.h"

using namespace tree_sitter::lr;

typedef std::unordered_set<ParseAction> actions;

Describe(ParseTableBuilder_test) {
    Grammar grammar = test_grammars::arithmetic();
    ParseTable table = build_tables(grammar);
    
    It(has_the_right_starting_state) {
        AssertThat(table.states[0].actions, Equals(unordered_map<string, actions>({
            { "expression", actions({ ParseAction::Shift(1) }) },
            { "term", actions({ ParseAction::Shift(2) }) },
            { "factor", actions({ ParseAction::Shift(5) }) },
            { "variable", actions({ ParseAction::Shift(8) }) },
            { "number", actions({ ParseAction::Shift(8) }) },
            { "left_paren", actions({ ParseAction::Shift(9) }) }
        })));
    }
    
    It(accepts_when_the_start_symbol_is_reduced) {
        AssertThat(table.states[1].actions, Equals(unordered_map<string, actions>({
            { ParseTable::END_OF_INPUT, actions({ ParseAction::Accept() }) }
        })));
    }
    
    It(has_the_right_next_states) {
        AssertThat(table.states[2].actions, Equals(unordered_map<string, actions>({
            { "plus", actions({ ParseAction::Shift(3) }) },
        })));

        AssertThat(table.states[3].actions, Equals(unordered_map<string, actions>({
            { "variable", actions({ ParseAction::Shift(8) }) },
            { "factor", actions({ ParseAction::Shift(5) }) },
            { "left_paren", actions({ ParseAction::Shift(9) }) },
            { "number", actions({ ParseAction::Shift(8) }) },
            { "term", actions({ ParseAction::Shift(4) }) },
        })));
    }
};
