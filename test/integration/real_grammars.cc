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
#include "helpers/tree_helpers.h"
#include <set>

static void assert_correct_tree_size(TSDocument *document, string content) {
  TSNode root_node = ts_document_root_node(document);
  AssertThat(ts_node_end_byte(root_node), Equals(content.size()));
  assert_consistent_tree_sizes(root_node);
}

START_TEST

vector<string> test_languages({
  "javascript",
  "json",
  "c",
  "cpp",
  "python",
  "bash",
});

for (auto &language_name : test_languages) {
  describe(("the " + language_name + " language").c_str(), [&]() {
    TSDocument *document;

    before_each([&]() {
      record_alloc::start();
      document = ts_document_new();
      ts_document_set_language(document, load_real_language(language_name));

      // ts_document_set_logger(document, stderr_logger_new(true));
      // ts_document_print_debugging_graphs(document, true);
    });

    after_each([&]() {
      ts_document_free(document);
      AssertThat(record_alloc::outstanding_allocation_indices(), IsEmpty());
    });

    for (auto &entry : read_real_language_corpus(language_name)) {
      SpyInput *input;

      auto it_handles_edit_sequence = [&](string name, std::function<void()> edit_sequence){
        it(("parses " + entry.description + ": " + name).c_str(), [&]() {
          input = new SpyInput(entry.input, 3);
          ts_document_set_input(document, input->input());
          edit_sequence();

          TSNode root_node = ts_document_root_node(document);
          const char *node_string = ts_node_string(root_node, document);
          string result(node_string);
          ts_free((void *)node_string);
          AssertThat(result, Equals(entry.tree_string));

          assert_correct_tree_size(document, input->content);
          delete input;
        });
      };

      it_handles_edit_sequence("initial parse", [&]() {
        ts_document_parse(document);
      });

      set<pair<size_t, size_t>> deletions;
      set<pair<size_t, string>> insertions;

      for (size_t i = 0; i < 60; i++) {
        size_t edit_position = random_unsigned(utf8_char_count(entry.input));
        size_t deletion_size = random_unsigned(utf8_char_count(entry.input) - edit_position);
        string inserted_text = random_words(random_unsigned(4) + 1);

        if (insertions.insert({edit_position, inserted_text}).second) {
          string description = "\"" + inserted_text + "\" at " + to_string(edit_position);

          it_handles_edit_sequence("repairing an insertion of " + description, [&]() {
            ts_document_edit(document, input->replace(edit_position, 0, inserted_text));
            ts_document_parse(document);
            assert_correct_tree_size(document, input->content);

            ts_document_edit(document, input->undo());
            assert_correct_tree_size(document, input->content);

            TSRange *ranges;
            uint32_t range_count;
            ScopeSequence old_scope_sequence = build_scope_sequence(document, input->content);
            ts_document_parse_and_get_changed_ranges(document, &ranges, &range_count);

            ScopeSequence new_scope_sequence = build_scope_sequence(document, input->content);
            verify_changed_ranges(old_scope_sequence, new_scope_sequence,
                                  input->content, ranges, range_count);
            ts_free(ranges);
          });
        }

        if (deletions.insert({edit_position, deletion_size}).second) {
          string desription = to_string(edit_position) + "-" + to_string(edit_position + deletion_size);

          it_handles_edit_sequence("repairing a deletion of " + desription, [&]() {
            ts_document_edit(document, input->replace(edit_position, deletion_size, ""));
            ts_document_parse(document);
            assert_correct_tree_size(document, input->content);

            ts_document_edit(document, input->undo());
            assert_correct_tree_size(document, input->content);

            TSRange *ranges;
            uint32_t range_count;
            ScopeSequence old_scope_sequence = build_scope_sequence(document, input->content);
            ts_document_parse_and_get_changed_ranges(document, &ranges, &range_count);

            ScopeSequence new_scope_sequence = build_scope_sequence(document, input->content);
            verify_changed_ranges(old_scope_sequence, new_scope_sequence,
                                  input->content, ranges, range_count);
            ts_free(ranges);
          });
        }
      }
    }
  });
}

END_TEST
