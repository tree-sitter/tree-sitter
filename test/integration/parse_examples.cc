#include "test_helper.h"
#include "runtime/alloc.h"
#include "helpers/load_language.h"
#include "helpers/read_test_entries.h"
#include "helpers/spy_input.h"
#include "helpers/stderr_logger.h"
#include "helpers/point_helpers.h"
#include "helpers/encoding_helpers.h"
#include "helpers/record_alloc.h"
#include "helpers/random_helpers.h"
#include "helpers/scope_sequence.h"
#include <set>

vector<string> languages({
  "javascript",
  "c",
  "cpp",
  "python",
});

map<string, vector<string>> examples_by_language;

START_TEST

describe("randomized edits", [&]() {
  for (unsigned trial = 0; trial < 10; trial++) {

    it("handles randomized edits", [&]() {
      auto language = select_random(languages);
      printf("language: %s\n", language.c_str());

      if (!examples_by_language.count(language)) {
        examples_by_language.insert({language, examples_for_language(language)});
      }

      auto example = select_random(examples_by_language[language]);
      SpyInput input(example, random() % 5);

      auto document = ts_document_new();
      ts_document_set_language(document, load_real_language(language));
      ts_document_set_input(document, input.input());
      ts_document_parse(document);

      AssertThat(ts_node_has_error(ts_document_root_node(document)), IsFalse());
    });

  }
});

END_TEST
