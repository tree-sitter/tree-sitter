#include "runtime/runtime_spec_helper.h"
#include <functional>
#include "runtime/helpers/read_test_entries.h"
#include "runtime/helpers/spy_input.h"
#include "runtime/helpers/log_debugger.h"

extern "C" const TSLanguage *ts_language_javascript();
extern "C" const TSLanguage *ts_language_json();
extern "C" const TSLanguage *ts_language_arithmetic();
extern "C" const TSLanguage *ts_language_golang();
extern "C" const TSLanguage *ts_language_c();

START_TEST

map<string, const TSLanguage *> languages({
  {"json", ts_language_json()},
  {"arithmetic", ts_language_arithmetic()},
  {"javascript", ts_language_javascript()},
  {"golang", ts_language_golang()},
  {"c", ts_language_c()},
});

describe("Languages", [&]() {
  TSDocument *doc;

  before_each([&]() {
    doc = ts_document_make();
  });

  after_each([&]() {
    ts_document_free(doc);
  });

  for (const auto &pair : languages) {
    describe(("The " + pair.first + " parser").c_str(), [&]() {
      before_each([&]() {
        ts_document_set_language(doc, pair.second);
        // ts_document_set_debugger(doc, log_debugger_make(true));
      });

      for (auto &entry : test_entries_for_language(pair.first)) {
        SpyInput *input;

        auto expect_the_correct_tree = [&](string tree_string) {
          const char *node_string = ts_node_string(ts_document_root_node(doc), doc);
          AssertThat(node_string, Equals(tree_string));
          free((void *)node_string);
        };

        auto it_handles_edit_sequence = [&](string name, std::function<void()> edit_sequence){
          it(("parses " + entry.description + ": " + name).c_str(), [&]() {
            input = new SpyInput(entry.input, 3);
            ts_document_set_input(doc, input->input());
            edit_sequence();
            expect_the_correct_tree(entry.tree_string);
            delete input;
          });
        };

        it_handles_edit_sequence("initial parse", [&]() {
          ts_document_parse(doc);
        });

        it_handles_edit_sequence("repairing an inserted error", [&]() {
          ts_document_edit(doc, input->replace(entry.input.size() / 2, 0, "%^&*"));
          ts_document_parse(doc);

          ts_document_edit(doc, input->undo());
          ts_document_parse(doc);
        });

        it_handles_edit_sequence("creating and repairing an inserted error", [&]() {
          ts_document_parse(doc);

          ts_document_edit(doc, input->replace(entry.input.size() / 2, 0, "%^&*"));
          ts_document_parse(doc);

          ts_document_edit(doc, input->undo());
          ts_document_parse(doc);
        });

        it_handles_edit_sequence("repairing an errant deletion", [&]() {
          ts_document_parse(doc);

          ts_document_edit(doc, input->replace(entry.input.size() / 2, 5, ""));
          ts_document_parse(doc);

          ts_document_edit(doc, input->undo());
          ts_document_parse(doc);
        });

        it_handles_edit_sequence("creating and repairing an errant deletion", [&]() {
          ts_document_edit(doc, input->replace(entry.input.size() / 2, 5, ""));
          ts_document_parse(doc);

          ts_document_edit(doc, input->undo());
          ts_document_parse(doc);
        });
      }
    });
  }
});

END_TEST
