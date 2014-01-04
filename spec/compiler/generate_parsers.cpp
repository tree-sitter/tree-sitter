#include "spec_helper.h"
#include "table_builder.h"
#include "parse_table.h"
#include "prepare_grammar.h"
#include "c_code.h"
#include "../fixtures/grammars/arithmetic.h"
#include <fstream>

START_TEST

describe("code generation", []() {
    string test_parser_dir = src_dir() + "/spec/fixtures/parsers";
    
    it("works for the arithmetic grammar", [&]() {
        Grammar grammar = test_grammars::arithmetic();
        auto grammars = prepare_grammar(grammar);
        auto tables = lr::build_tables(grammars.first, grammars.second);
        auto rule_names = grammars.first.rule_names();
        auto token_names = grammars.second.rule_names();
        rule_names.insert(rule_names.end(), token_names.begin(), token_names.end());
        auto code = code_gen::c_code(rule_names, tables.first, tables.second);
        ofstream(test_parser_dir + "/arithmetic.c") << code;
    });
});

END_TEST