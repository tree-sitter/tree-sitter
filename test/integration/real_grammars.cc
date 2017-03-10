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

static void assert_consistent_sizes(TSNode node) {
  size_t child_count = ts_node_child_count(node);
  size_t start_byte = ts_node_start_byte(node);
  size_t end_byte = ts_node_end_byte(node);
  TSPoint start_point = ts_node_start_point(node);
  TSPoint end_point = ts_node_end_point(node);
  bool some_child_has_changes = false;

  AssertThat(start_byte, !IsGreaterThan(end_byte));
  AssertThat(start_point, !IsGreaterThan(end_point));

  size_t last_child_end_byte = start_byte;
  TSPoint last_child_end_point = start_point;

  for (size_t i = 0; i < child_count; i++) {
    TSNode child = ts_node_child(node, i);
    size_t child_start_byte = ts_node_start_byte(child);
    TSPoint child_start_point = ts_node_start_point(child);

    AssertThat(child_start_byte, !IsLessThan(last_child_end_byte));
    AssertThat(child_start_point, !IsLessThan(last_child_end_point));
    assert_consistent_sizes(child);
    if (ts_node_has_changes(child))
      some_child_has_changes = true;

    last_child_end_byte = ts_node_end_byte(child);
    last_child_end_point = ts_node_end_point(child);
  }

  if (child_count > 0) {
    AssertThat(end_byte, !IsLessThan(last_child_end_byte));
    AssertThat(end_point, !IsLessThan(last_child_end_point));
  }

  if (some_child_has_changes) {
    AssertThat(ts_node_has_changes(node), IsTrue());
  }
}

static void assert_correct_tree_size(TSDocument *document, string content) {
  TSNode root_node = ts_document_root_node(document);
  size_t expected_size = content.size();

  // In the JSON grammar, the start rule (`_value`) is hidden, so the node
  // returned from `ts_document_root_node` (e.g. an `object` node), does not
  // actually point to the root of the tree. In this weird case, trailing
  // whitespace is not included in the root node's size.
  //
  // TODO: Fix this inconsistency. Maybe disallow the start rule being hidden?
  if (ts_document_language(document) == load_real_language("json") &&
      string(ts_node_type(root_node, document)) != "ERROR")
    expected_size = content.find_last_not_of("\n ") + 1;

  AssertThat(ts_node_end_byte(root_node), Equals(expected_size));
  assert_consistent_sizes(root_node);
}

START_TEST

vector<string> test_languages({
  "javascript",
  "json",
  "c",
  "cpp",
  "python",
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
