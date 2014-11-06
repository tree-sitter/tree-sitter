#include "compiler/compiler_spec_helper.h"
#include <fstream>
#include <iostream>

static string src_dir() {
  const char * dir = getenv("TREESITTER_DIR");
  if (!dir) dir = getenv("PWD");
  return dir;
}

namespace tree_sitter_examples {

extern const Grammar arithmetic;
extern const Grammar javascript;
extern const Grammar json;
extern const Grammar golang;

}  // namespace tree_sitter_examples

START_TEST

describe("compiling the example grammars", []() {
  string example_parser_dir = src_dir() + "/spec/fixtures/parsers/";

  auto compile_grammar = [&](const Grammar &grammar, string language) {
    it(("compiles the " + language + " grammar").c_str(), [&]() {
      auto result = compile(grammar, language);
      string code = get<0>(result);
      vector<Conflict> conflicts = get<1>(result);
      const GrammarError *error = get<2>(result);

      AssertThat(error, Equals((GrammarError *)nullptr));

      // for (const auto &conflict : conflicts)
        // std::cout << conflict << std::endl;

      ofstream file(example_parser_dir + language + ".c");
      file << get<0>(result);
      file.close();
    });
  };

  compile_grammar(tree_sitter_examples::arithmetic, "arithmetic");
  compile_grammar(tree_sitter_examples::json, "json");
  compile_grammar(tree_sitter_examples::javascript, "javascript");
  compile_grammar(tree_sitter_examples::golang, "golang");
});

END_TEST
