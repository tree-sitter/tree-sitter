#include "spec_helper.h"
#include "../../examples/grammars/json.hpp"
#include "../../examples/grammars/arithmetic.hpp"
#include <fstream>

START_TEST

describe("compiling the example grammars", []() {
    string example_parser_dir = src_dir() + "/examples/parsers/";
    
    it("compiles the arithmetic grammar", [&]() {
        Grammar grammar = test_grammars::arithmetic();
        ofstream(example_parser_dir + "arithmetic.c") << compile(grammar, "arithmetic");
    });

    it("compiles the json grammar", [&]() {
        Grammar grammar = test_grammars::json();
        ofstream(example_parser_dir + "json.c") << compile(grammar, "json");
    });
});

END_TEST