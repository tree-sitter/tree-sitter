#include "spec_helper.h"
#include "parse_table.h"
#include "lex_table.h"
#include "table_builder.h"

using namespace tree_sitter::lr;

typedef std::unordered_set<ParseAction> parse_actions;
typedef std::unordered_set<LexAction> lex_actions;

Describe(TableBuilderSpec) {
    Grammar grammar = test_grammars::arithmetic();
    ParseTable table = build_tables(grammar).first;
    LexTable lex_table = build_tables(grammar).second;
    
    ParseState parse_state(size_t index) {
        return table.states[index];
    }
    
    LexState lex_state(size_t parse_state_index) {
        size_t index = table.states[parse_state_index].lex_state_index;
        return lex_table.states[index];
    }
    
    It(has_the_right_starting_state) {
        AssertThat(parse_state(0).actions, Equals(unordered_map<string, parse_actions>({
            { "expression", parse_actions({ ParseAction::Shift(1) }) },
            { "term", parse_actions({ ParseAction::Shift(2) }) },
            { "factor", parse_actions({ ParseAction::Shift(5) }) },
            { "variable", parse_actions({ ParseAction::Shift(8) }) },
            { "number", parse_actions({ ParseAction::Shift(8) }) },
            { "left_paren", parse_actions({ ParseAction::Shift(9) }) }
        })));
        
        AssertThat(lex_state(0).actions, Equals(unordered_map<CharMatch, lex_actions>({
            { CharMatchClass(CharClassWord), lex_actions({ LexAction::Advance(1) }) },
            { CharMatchClass(CharClassDigit), lex_actions({ LexAction::Advance(4) }) },
            { CharMatchSpecific('('), lex_actions({ LexAction::Advance(11) }) }
        })));
    }
    
    It(accepts_when_the_start_symbol_is_reduced) {
        AssertThat(parse_state(1).actions, Equals(unordered_map<string, parse_actions>({
            { ParseTable::END_OF_INPUT, parse_actions({ ParseAction::Accept() }) }
        })));
    }
    
    It(has_the_right_next_states) {
        AssertThat(parse_state(2).actions, Equals(unordered_map<string, parse_actions>({
            { "plus", parse_actions({ ParseAction::Shift(3) }) },
        })));

        AssertThat(parse_state(3).actions, Equals(unordered_map<string, parse_actions>({
            { "variable", parse_actions({ ParseAction::Shift(8) }) },
            { "factor", parse_actions({ ParseAction::Shift(5) }) },
            { "left_paren", parse_actions({ ParseAction::Shift(9) }) },
            { "number", parse_actions({ ParseAction::Shift(8) }) },
            { "term", parse_actions({ ParseAction::Shift(4) }) },
        })));
    }
};
