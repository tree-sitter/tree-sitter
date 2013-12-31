#include "spec_helper.h"
#include "table_builder.h"
#include "parse_table.h"
#include "c_code.h"
#include <fstream>

START_TEST

describe("code generation", []() {
    string test_parser_dir = src_dir() + "/spec/fixtures/parsers";
    
    it("works for the arithmetic grammar", [&]() {
        Grammar grammar = test_grammars::arithmetic();
        auto tables = lr::build_tables(grammar);
        string code = code_gen::c_code(grammar, tables.first, tables.second);
        std::ofstream(test_parser_dir + "/arithmetic.c") << code;
    });
});

END_TEST