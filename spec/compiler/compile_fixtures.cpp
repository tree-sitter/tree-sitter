#include "spec_helper.h"
#include "../fixtures/grammars/test_grammars.h"
#include <fstream>

START_TEST

describe("compiling grammars", []() {
    string test_parser_dir = src_dir() + "/spec/fixtures/parsers";
    
    it("compiles the arithmetic grammar", [&]() {
        Grammar grammar = test_grammars::arithmetic();
        ofstream(test_parser_dir + "/arithmetic.c") << compile(grammar, "arithmetic");
    });

    it("compiles the json grammar", [&]() {
        Grammar grammar = test_grammars::json();
        ofstream(test_parser_dir + "/json.c") << compile(grammar, "json");
    });
});

END_TEST