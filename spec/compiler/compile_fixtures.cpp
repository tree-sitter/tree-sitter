#include "spec_helper.h"
#include "compile.h"
#include "../fixtures/grammars/arithmetic.h"
#include <fstream>

START_TEST

describe("code generation", []() {
    string test_parser_dir = src_dir() + "/spec/fixtures/parsers";
    
    it("works for the arithmetic grammar", [&]() {
        Grammar grammar = test_grammars::arithmetic();
        ofstream(test_parser_dir + "/arithmetic.c") << compile(grammar);
    });
});

END_TEST