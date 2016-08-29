#include "spec_helper.h"
#include "runtime/alloc.h"
#include "helpers/load_language.h"
#include "helpers/read_test_entries.h"
#include "helpers/spy_input.h"
#include "helpers/log_debugger.h"
#include "helpers/point_helpers.h"
#include "helpers/encoding_helpers.h"
#include "helpers/record_alloc.h"
#include "helpers/random_helpers.h"
#include <set>

static void expect_the_correct_tree(TSNode node, TSDocument *document, string tree_string) {
  const char *node_string = ts_node_string(node, document);
  string result(node_string);
  ts_free((void *)node_string);
  AssertThat(result, Equals(tree_string));
}

static void expect_a_consistent_tree(TSNode node, TSDocument *document) {
  size_t child_count = ts_node_child_count(node);
  size_t start_char = ts_node_start_char(node);
  size_t end_char = ts_node_end_char(node);
  TSPoint start_point = ts_node_start_point(node);
  TSPoint end_point = ts_node_end_point(node);
  bool has_changes = ts_node_has_changes(node);
  bool some_child_has_changes = false;

  AssertThat(start_char, !IsGreaterThan(end_char));
  AssertThat(start_point, !IsGreaterThan(end_point));

  size_t last_child_end_char = 0;
  TSPoint last_child_end_point = {0, 0};

  for (size_t i = 0; i < child_count; i++) {
    TSNode child = ts_node_child(node, i);
    size_t child_start_char = ts_node_start_char(child);
    size_t child_end_char = ts_node_end_char(child);
    TSPoint child_start_point = ts_node_start_point(child);
    TSPoint child_end_point = ts_node_end_point(child);

    if (i > 0) {
      AssertThat(child_start_char, !IsLessThan(last_child_end_char));
      AssertThat(child_start_point, !IsLessThan(last_child_end_point));
      last_child_end_char = child_end_char;
      last_child_end_point = child_end_point;
    }

    AssertThat(child_start_char, !IsLessThan(start_char));
    AssertThat(child_end_char, !IsGreaterThan(end_char));
    AssertThat(child_start_point, !IsLessThan(start_point));
    AssertThat(child_end_point, !IsGreaterThan(end_point));

    expect_a_consistent_tree(child, document);

    if (ts_node_has_changes(child))
      some_child_has_changes = true;
  }

  if (child_count > 0)
    AssertThat(has_changes, Equals(some_child_has_changes));
}

START_TEST

describe("The Corpus", []() {
  vector<string> test_languages({
    "javascript",
    "json",
    "c",
    "cpp",
  });

  for (auto &language_name : test_languages) {
    describe(("the " + language_name + " language").c_str(), [&]() {
      TSDocument *document;

      before_each([&]() {
        record_alloc::start();
        document = ts_document_make();
        ts_document_set_language(document, get_test_language(language_name));

        // ts_document_set_debugger(document, log_debugger_make(true));
        // ts_document_print_debugging_graphs(document, true);
      });

      after_each([&]() {
        ts_document_free(document);
        AssertThat(record_alloc::outstanding_allocation_indices(), IsEmpty());
      });

      for (auto &entry : read_corpus_entries(language_name)) {
        SpyInput *input;

        auto it_handles_edit_sequence = [&](string name, std::function<void()> edit_sequence){
          it(("parses " + entry.description + ": " + name).c_str(), [&]() {
            input = new SpyInput(entry.input, 3);
            ts_document_set_input(document, input->input());
            edit_sequence();
            TSNode root_node = ts_document_root_node(document);
            expect_the_correct_tree(root_node, document, entry.tree_string);
            expect_a_consistent_tree(root_node, document);
            delete input;
          });
        };

        it_handles_edit_sequence("initial parse", [&]() {
          ts_document_parse(document);
        });

        std::set<std::pair<size_t, size_t>> deletions;
        std::set<std::pair<size_t, string>> insertions;

        for (size_t i = 0; i < 60; i++) {
          size_t edit_position = random() % utf8_char_count(entry.input);
          size_t deletion_size = random() % (utf8_char_count(entry.input) - edit_position);
          string inserted_text = random_words(random() % 4 + 1);

          if (insertions.insert({edit_position, inserted_text}).second) {
            string description = "\"" + inserted_text + "\" at " + to_string(edit_position);

            it_handles_edit_sequence("repairing an insertion of " + description, [&]() {
              ts_document_edit(document, input->replace(edit_position, 0, inserted_text));
              ts_document_parse(document);

              expect_a_consistent_tree(ts_document_root_node(document), document);

              ts_document_edit(document, input->undo());
              ts_document_parse(document);
            });
          }

          if (deletions.insert({edit_position, deletion_size}).second) {
            string desription = to_string(edit_position) + "-" + to_string(edit_position + deletion_size);

            it_handles_edit_sequence("repairing a deletion of " + desription, [&]() {
              ts_document_edit(document, input->replace(edit_position, deletion_size, ""));
              ts_document_parse(document);

              expect_a_consistent_tree(ts_document_root_node(document), document);

              ts_document_edit(document, input->undo());
              ts_document_parse(document);
            });
          }
        }
      }
    });
  }
});

END_TEST
