#include "compiler_spec_helper.h"
#include "helpers/example_grammars.h"
#include <fstream>

static string src_dir() {
    const char * dir = getenv("TREESITTER_DIR");
    if (!dir) dir = getenv("PWD");
    return dir;
}

START_TEST

describe("compiling the example grammars", []() {
    string example_parser_dir = src_dir() + "/examples/parsers/";

    it("compiles the arithmetic grammar", [&]() {
        Grammar grammar = examples::arithmetic();
        ofstream(example_parser_dir + "arithmetic.c") << compile(grammar, "arithmetic");
    });

    it("compiles the json grammar", [&]() {
        Grammar grammar = examples::json();
        ofstream(example_parser_dir + "json.c") << compile(grammar, "json");
    });
});

END_TEST
