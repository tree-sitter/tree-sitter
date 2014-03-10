#include "compiler_spec_helper.h"
#include "prepared_grammar.h"
#include "build_tables/build_tables.h"
#include <functional>

using namespace rules;
using build_tables::build_tables;

typedef set<ParseAction> parse_actions;
typedef set<LexAction> lex_actions;

static set<Symbol> keys(const map<Symbol, parse_actions> &map) {
    set<Symbol> result;
    for (auto pair : map) {
        result.insert(pair.first);
    }
    return result;
}

START_TEST

describe("building parse and lex tables", []() {
    PreparedGrammar grammar("expression", {
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
    }, {});

    PreparedGrammar lex_grammar("", {
        { "plus", str("+") },
        { "variable", pattern("\\w+") },
        { "number", pattern("\\d+") },
        { "left-paren", str("(") },
        { "right-paren", str(")") }
    }, {});

    ParseTable table;
    LexTable lex_table;

    before_each([&]() {
        pair<ParseTable, LexTable> tables = build_tables::build_tables(grammar, lex_grammar);
        table = tables.first;
        lex_table = tables.second;
    });

    function<ParseState(size_t)> parse_state = [&](size_t index) {
        return table.states[index];
    };

    function<LexState(size_t)> lex_state = [&](size_t parse_state_index) {
        long index = table.states[parse_state_index].lex_state_id;
        return lex_table.states[index];
    };

    it("has the right starting state", [&]() {
        AssertThat(keys(parse_state(0).actions), Equals(set<Symbol>({
            Symbol("expression"),
            Symbol("term"),
            Symbol("number"),
            Symbol("variable"),
            Symbol("left-paren"),
        })));

        AssertThat(lex_state(0).expected_inputs(), Equals(set<CharacterSet>({
            CharacterSet({ '(' }),
            CharacterSet({ CharacterRange('0', '9') }),
            CharacterSet({ {'a', 'z'}, {'A', 'Z'} }),
        })));
    });
});

END_TEST
