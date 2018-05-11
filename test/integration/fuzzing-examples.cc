#include "test_helper.h"
#include "base64.c"
#include "helpers/load_language.h"
#include "helpers/tree_helpers.h"
#include "helpers/record_alloc.h"

START_TEST

vector<pair<string, string>> examples({
  {
    "javascript",
    "Bi0tLS0tLS0tLS0tLS0tLS0tLS0tLS0tLXGK0i0vLS0tLS0tLS0tLS0tLS0tLS0tLS0tLXGK0i0vLS0tLS0tLS0tLS0tLS0xLS0tLTYtLfpZAA=="
  },
  {
    "python",
    "NWNvbogsKTMsLCwsY29uiCwqLDo1Y29uLA=="
  },
});

describe("examples found via fuzzing", [&]() {
  before_each([&]() {
    record_alloc::start();
  });

  after_each([&]() {
    AssertThat(record_alloc::outstanding_allocation_indices(), IsEmpty());
  });

  for (unsigned i = 0, n = examples.size(); i < n; i++) {

    it(("parses example number " + to_string(i)).c_str(), [&]() {
      TSParser *parser = ts_parser_new();

      if (getenv("TREE_SITTER_ENABLE_DEBUG_GRAPHS")) {
        ts_parser_print_debugging_graphs(parser, true);
      }

      const string &language_name = examples[i].first;
      ts_parser_set_language(parser, load_real_language(language_name));

      string input;
      const string &base64_input = examples[i].second;
      input.resize(base64_input.size());
      input.resize(base64_decode(
        reinterpret_cast<const unsigned char *>(base64_input.c_str()),
        reinterpret_cast<unsigned char *>(&input[0]),
        base64_input.size()
      ));

      TSTree *tree = ts_parser_parse_string(parser, nullptr, input.c_str(), input.size());
      TSNode node = ts_tree_root_node(tree);
      assert_consistent_tree_sizes(node);

      ts_tree_delete(tree);
      ts_parser_delete(parser);
    });

  }
});

END_TEST
