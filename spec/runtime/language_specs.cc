#include "runtime/runtime_spec_helper.h"
#include "runtime/helpers/read_test_entries.h"
#include "runtime/helpers/spy_input.h"
#include "runtime/helpers/log_debugger.h"
#include <set>

extern "C" const TSLanguage *ts_language_javascript();
extern "C" const TSLanguage *ts_language_json();
extern "C" const TSLanguage *ts_language_arithmetic();
extern "C" const TSLanguage *ts_language_golang();
extern "C" const TSLanguage *ts_language_c();

START_TEST

describe("Languages", [&]() {
  TSDocument *doc;

  before_each([&]() {
    doc = ts_document_make();
  });

  after_each([&]() {
    ts_document_free(doc);
  });

  auto run_tests_for_language = [&](string language_name, const TSLanguage *language) {
    describe((string("The ") + language_name + " parser").c_str(), [&]() {
      before_each([&]() {
        ts_document_set_language(doc, language);
        // ts_document_set_debugger(doc, log_debugger_make());
      });

      for (auto &entry : test_entries_for_language(language_name)) {
        auto expect_the_correct_tree = [&]() {
          const char *node_string = ts_node_string(ts_document_root_node(doc), doc);
          AssertThat(node_string, Equals(entry.tree_string.c_str()));
          free((void *)node_string);
        };

        it(("parses " + entry.description).c_str(), [&]() {
          ts_document_set_input_string(doc, entry.input.c_str());
          ts_document_parse(doc);
          expect_the_correct_tree();
        });

        set<string> skipped({});

        if (skipped.find(entry.description) != skipped.end())
          continue;

        it(("handles random insertions in " + entry.description).c_str(), [&]() {
          SpyInput reader(entry.input, 3);
          ts_document_set_input(doc, reader.input());
          ts_document_parse(doc);

          string garbage("%^&*");
          size_t position = entry.input.size() / 2;

          reader.insert(position, garbage);
          ts_document_edit(doc, { position, garbage.size(), 0 });
          ts_document_parse(doc);

          reader.erase(position, garbage.size());
          ts_document_edit(doc, { position, 0, garbage.size() });
          ts_document_parse(doc);

          expect_the_correct_tree();
        });

        it(("handles random deletions in " + entry.description).c_str(), [&]() {
          SpyInput reader(entry.input, 3);
          ts_document_set_input(doc, reader.input());
          ts_document_parse(doc);

          size_t position = entry.input.size() / 2;
          string removed = entry.input.substr(position);

          reader.erase(position, removed.size());
          ts_document_edit(doc, { position, 0, removed.size() });
          ts_document_parse(doc);

          reader.insert(position, removed);
          ts_document_edit(doc, { position, removed.size(), 0 });
          ts_document_parse(doc);

          expect_the_correct_tree();
        });
      }
    });
  };

  run_tests_for_language("json", ts_language_json());
  run_tests_for_language("arithmetic", ts_language_arithmetic());
  run_tests_for_language("javascript", ts_language_javascript());
  run_tests_for_language("golang", ts_language_golang());
  run_tests_for_language("c", ts_language_c());
});

END_TEST
