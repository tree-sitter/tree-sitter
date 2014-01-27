#include "spec_helper.h"
#include <functional>
#include "build_tables/perform.h"

using build_tables::perform;
using namespace rules;

typedef unordered_set<ParseAction> parse_actions;
typedef unordered_set<LexAction> lex_actions;

static unordered_set<Symbol> keys(const unordered_map<Symbol, parse_actions> &map) {
    unordered_set<Symbol> result;
    for (auto pair : map) {
        result.insert(pair.first);
    }
    return result;
}

static unordered_set<CharMatch> keys(const unordered_map<CharMatch, lex_actions> &map) {
    unordered_set<CharMatch> result;
    for (auto pair : map) {
        result.insert(pair.first);
    }
    return result;
}

START_TEST

describe("building parse and lex tables", []() {
    Grammar grammar({
        { "expression", choice({
            seq({
                sym("term"),
                sym("plus"),
                sym("term") }),
            sym("term") }) },
        { "term", choice({
            sym("variable"),
            sym("number"),
            seq({
                sym("left-paren"),
                sym("expression"),
                sym("right-paren")
            }) }) }
    });
    
    Grammar lex_grammar({
        { "plus", str("+") },
        { "variable", pattern("\\w+") },
        { "number", pattern("\\d+") },
        { "left-paren", str("(") },
        { "right-paren", str(")") }
    });
    
    ParseTable table;
    LexTable lex_table;
    
    before_each([&]() {
        pair<ParseTable, LexTable> tables = perform(grammar, lex_grammar);
        table = tables.first;
        lex_table = tables.second;
    });
    
    function<ParseState(size_t)> parse_state = [&](size_t index) {
        return table.states[index];
    };
    
    function<LexState(size_t)> lex_state = [&](size_t parse_state_index) {
        long index = table.states[parse_state_index].lex_state_index;
        return lex_table.states[index];
    };
    
    it("has the right starting state", [&]() {
        AssertThat(keys(parse_state(0).actions), Equals(unordered_set<Symbol>({
            Symbol("expression"),
            Symbol("term"),
            Symbol("number"),
            Symbol("variable"),
            Symbol("left-paren"),
        })));
        
        AssertThat(keys(lex_state(0).actions), Equals(unordered_set<CharMatch>({
            CharMatchSpecific('('),
            CharMatchClass(CharClassDigit),
            CharMatchClass(CharClassWord),
        })));

        AssertThat(lex_state(0).expected_inputs(), Equals(unordered_set<CharMatch>({
            CharMatchSpecific('('),
            CharMatchClass(CharClassDigit),
            CharMatchClass(CharClassWord),
        })));
    });
    
    it("accepts when the start symbol is reduced", [&]() {
        AssertThat(parse_state(1).actions, Equals(unordered_map<Symbol, parse_actions>({
            { Symbol("__END__"), parse_actions({ ParseAction::Accept() }) }
        })));
    });
    
    it("has the right next states", [&]() {
        AssertThat(parse_state(2).actions, Equals(unordered_map<Symbol, parse_actions>({
            { Symbol("plus"), parse_actions({ ParseAction::Shift(3) }) },
            { Symbol("__END__"), parse_actions({ ParseAction::Reduce(Symbol("expression"), 1) }) },
        })));
    });
});

END_TEST
