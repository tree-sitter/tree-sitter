#include "compiler_spec_helper.h"
#include <fstream>

static string src_dir() {
    const char * dir = getenv("TREESITTER_DIR");
    if (!dir) dir = getenv("PWD");
    return dir;
}

namespace tree_sitter {
    namespace examples {
        Grammar arithmetic();
        Grammar javascript();
        Grammar json();
    }
}

START_TEST

describe("compiling the example grammars", []() {
    string example_parser_dir = src_dir() + "/examples/parsers/";

    auto compile_grammar = [&](Grammar grammar, string language) {
        it(("compiles the " + language + " grammar").c_str(), [&]() {
            ofstream(example_parser_dir + language + ".c") << compile(grammar, language);
        });
    };

    compile_grammar(examples::arithmetic(), "arithmetic");
    compile_grammar(examples::json(), "json");
    compile_grammar(examples::javascript(), "javascript");
});

END_TEST
