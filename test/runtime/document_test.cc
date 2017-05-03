#include "test_helper.h"
#include "runtime/alloc.h"
#include "helpers/record_alloc.h"
#include "helpers/stream_methods.h"
#include "helpers/tree_helpers.h"
#include "helpers/point_helpers.h"
#include "helpers/spy_logger.h"
#include "helpers/stderr_logger.h"
#include "helpers/spy_input.h"
#include "helpers/load_language.h"

TSPoint point(size_t row, size_t column) {
  return TSPoint{static_cast<uint32_t>(row), static_cast<uint32_t>(column)};
}

START_TEST

describe("Document", [&]() {
  TSDocument *document;
  TSNode root;

  before_each([&]() {
    record_alloc::start();
    document = ts_document_new();
  });

  after_each([&]() {
    ts_document_free(document);
    record_alloc::stop();
    AssertThat(record_alloc::outstanding_allocation_indices(), IsEmpty());
  });

  auto assert_node_string_equals = [&](TSNode node, const string &expected) {
    char *str = ts_node_string(node, document);
    string actual(str);
    ts_free(str);
    AssertThat(actual, Equals(expected));
  };

  describe("set_input(input)", [&]() {
    SpyInput *spy_input;

    before_each([&]() {
      spy_input = new SpyInput("{\"key\": [null, 2]}", 3);

      ts_document_set_language(document, load_real_language("json"));
      ts_document_set_input_string(document, "{\"key\": [1, 2]}");
      ts_document_parse(document);

      root = ts_document_root_node(document);
      assert_node_string_equals(
        root,
        "(object (pair (string) (array (number) (number))))");
    });

    after_each([&]() {
      delete spy_input;
    });

    it("handles both UTF8 and UTF16 encodings", [&]() {
      const char16_t content[] = u"[true, false]";
      spy_input->content = string((const char *)content, sizeof(content));
      spy_input->encoding = TSInputEncodingUTF16;

      ts_document_set_input(document, spy_input->input());
      ts_document_invalidate(document);
      ts_document_parse(document);

      root = ts_document_root_node(document);
      assert_node_string_equals(
        root,
        "(array (true) (false))");
    });

    it("allows columns to be measured in either bytes or characters", [&]() {
      const char16_t content[] = u"[true, false]";
      spy_input->content = string((const char *)content, sizeof(content));
      spy_input->encoding = TSInputEncodingUTF16;
      // spy_input->measure_columns_in_bytes

      ts_document_set_input(document, spy_input->input());
      ts_document_invalidate(document);
      ts_document_parse(document);
    });

    it("allows the input to be retrieved later", [&]() {
      ts_document_set_input(document, spy_input->input());
      AssertThat(ts_document_input(document).payload, Equals<void *>(spy_input));
      AssertThat(ts_document_input(document).read, Equals(spy_input->input().read));
      AssertThat(ts_document_input(document).seek, Equals(spy_input->input().seek));
    });

    it("does not assume that the document's text has changed", [&]() {
      ts_document_set_input(document, spy_input->input());
      AssertThat(ts_document_root_node(document), Equals<TSNode>(root));
      AssertThat(ts_node_has_changes(root), IsFalse());
      AssertThat(spy_input->strings_read, Equals(vector<string>({ "" })));
    });

    it("reads text from the new input for future parses", [&]() {
      ts_document_set_input(document, spy_input->input());

      // Insert 'null', delete '1'.
      TSInputEdit edit = {};
      edit.start_point.column = edit.start_byte = strlen("{\"key\": [");
      edit.extent_added.column = edit.bytes_added = 4;
      edit.extent_removed.column = edit.bytes_removed = 1;

      ts_document_edit(document, edit);
      ts_document_parse(document);

      TSNode new_root = ts_document_root_node(document);
      assert_node_string_equals(
        new_root,
        "(object (pair (string) (array (null) (number))))");
      AssertThat(spy_input->strings_read, Equals(vector<string>({" [null, 2" })));
    });

    it("allows setting input string with length", [&]() {
      const char content[] = { '1' };
      ts_document_set_input_string_with_length(document, content, 1);
      ts_document_parse(document);
      TSNode new_root = ts_document_root_node(document);
      AssertThat(ts_node_end_char(new_root), Equals<size_t>(1));
      assert_node_string_equals(
        new_root,
        "(number)");
    });

    it("reads from the new input correctly when the old input was blank", [&]() {
      ts_document_set_input_string(document, "");
      ts_document_parse(document);
      TSNode new_root = ts_document_root_node(document);
      AssertThat(ts_node_end_char(new_root), Equals<size_t>(0));
      assert_node_string_equals(
        new_root,
        "(ERROR)");

      ts_document_set_input_string(document, "1");
      ts_document_parse(document);
      new_root = ts_document_root_node(document);
      AssertThat(ts_node_end_char(new_root), Equals<size_t>(1));
      assert_node_string_equals(
        new_root,
        "(number)");
    });
  });

  describe("set_language(language)", [&]() {
    before_each([&]() {
      ts_document_set_input_string(document, "{\"key\": [1, 2]}\n");
    });

    it("uses the given language for future parses", [&]() {
      ts_document_set_language(document, load_real_language("json"));
      ts_document_parse(document);

      root = ts_document_root_node(document);
      assert_node_string_equals(
        root,
        "(object (pair (string) (array (number) (number))))");
    });

    it("clears out any previous tree", [&]() {
      ts_document_set_language(document, load_real_language("json"));
      ts_document_parse(document);

      ts_document_set_language(document, load_real_language("javascript"));
      AssertThat(ts_document_root_node(document).data, Equals<void *>(nullptr));

      ts_document_parse(document);
      root = ts_document_root_node(document);
      assert_node_string_equals(
        root,
        "(program (expression_statement "
          "(object (pair (string) (array (number) (number))))))");
    });

    it("does not allow setting a language with a different version number", [&]() {
      TSLanguage language = *load_real_language("json");
      AssertThat(ts_language_version(&language), Equals<uint32_t>(TREE_SITTER_LANGUAGE_VERSION));

      language.version++;
      AssertThat(ts_language_version(&language), !Equals<uint32_t>(TREE_SITTER_LANGUAGE_VERSION));

      ts_document_set_language(document, &language);
      AssertThat(ts_document_language(document), IsNull());
    });
  });

  describe("set_logger(TSLogger)", [&]() {
    SpyLogger *logger;

    before_each([&]() {
      logger = new SpyLogger();
      ts_document_set_language(document, load_real_language("json"));
      ts_document_set_input_string(document, "[1, 2]");
    });

    after_each([&]() {
      delete logger;
    });

    it("calls the debugger with a message for each parse action", [&]() {
      ts_document_set_logger(document, logger->logger());
      ts_document_parse(document);

      AssertThat(logger->messages, Contains("new_parse"));
      AssertThat(logger->messages, Contains("skip character:' '"));
      AssertThat(logger->messages, Contains("consume character:'['"));
      AssertThat(logger->messages, Contains("consume character:'1'"));
      AssertThat(logger->messages, Contains("reduce sym:array, child_count:4"));
      AssertThat(logger->messages, Contains("accept"));
    });

    it("allows the debugger to be retrieved later", [&]() {
      ts_document_set_logger(document, logger->logger());
      AssertThat(ts_document_logger(document).payload, Equals(logger));
    });

    describe("disabling debugging", [&]() {
      before_each([&]() {
        ts_document_set_logger(document, logger->logger());
        ts_document_set_logger(document, {NULL, NULL});
      });

      it("does not call the debugger any more", [&]() {
        ts_document_parse(document);
        AssertThat(logger->messages, IsEmpty());
      });
    });
  });

  describe("parse_and_get_changed_ranges()", [&]() {
    SpyInput *input;

    before_each([&]() {
      ts_document_set_language(document, load_real_language("javascript"));
      input = new SpyInput("{a: null};", 3);
      ts_document_set_input(document, input->input());
      ts_document_parse(document);
      assert_node_string_equals(
        ts_document_root_node(document),
        "(program (expression_statement (object (pair (identifier) (null)))))");
    });

    after_each([&]() {
      delete input;
    });

    auto get_invalidated_ranges_for_edit = [&](std::function<TSInputEdit()> callback) -> vector<TSRange> {
      TSInputEdit edit = callback();
      ts_document_edit(document, edit);

      TSRange *ranges;
      uint32_t range_count = 0;
      ts_document_parse_and_get_changed_ranges(document, &ranges, &range_count);

      vector<TSRange> result;
      for (size_t i = 0; i < range_count; i++) {
        result.push_back(ranges[i]);
      }
      ts_free(ranges);
      return result;
    };

    it("reports changes when one token has been updated", [&]() {
      // Replace `null` with `nothing`
      auto ranges = get_invalidated_ranges_for_edit([&]() {
        return input->replace(input->content.find("ull"), 1, "othing");
      });

      AssertThat(ranges, Equals(vector<TSRange>({
        TSRange{
          point(0, input->content.find("nothing")),
          point(0, input->content.find("}"))
        },
      })));

      // Replace `nothing` with `null` again
      ranges = get_invalidated_ranges_for_edit([&]() {
        return input->undo();
      });

      AssertThat(ranges, Equals(vector<TSRange>({
        TSRange{
          point(0, input->content.find("null")),
          point(0, input->content.find("}"))
        },
      })));
    });

    it("reports changes when tokens have been appended", [&]() {
      // Add a second key-value pair
      auto ranges = get_invalidated_ranges_for_edit([&]() {
        return input->replace(input->content.find("}"), 0, ", b: false");
      });

      AssertThat(ranges, Equals(vector<TSRange>({
        TSRange{
          point(0, input->content.find(",")),
          point(0, input->content.find("}"))
        },
      })));

      // Add a third key-value pair in between the first two
      ranges = get_invalidated_ranges_for_edit([&]() {
        return input->replace(input->content.find(", b"), 0, ", c: 1");
      });

      assert_node_string_equals(
        ts_document_root_node(document),
        "(program (expression_statement (object "
          "(pair (identifier) (null)) "
          "(pair (identifier) (number)) "
          "(pair (identifier) (false)))))");

      AssertThat(ranges, Equals(vector<TSRange>({
        TSRange{
          point(0, input->content.find(", c")),
          point(0, input->content.find(", b"))
        },
      })));

      // Delete the middle pair.
      ranges = get_invalidated_ranges_for_edit([&]() {
        return input->undo();
      });

      assert_node_string_equals(
        ts_document_root_node(document),
        "(program (expression_statement (object "
          "(pair (identifier) (null)) "
          "(pair (identifier) (false)))))");

      AssertThat(ranges, IsEmpty());

      // Delete the second pair.
      ranges = get_invalidated_ranges_for_edit([&]() {
        return input->undo();
      });

      assert_node_string_equals(
        ts_document_root_node(document),
        "(program (expression_statement (object "
          "(pair (identifier) (null)))))");

      AssertThat(ranges, IsEmpty());
    });

    it("reports changes when trees have been wrapped", [&]() {
      // Wrap the object in an assignment expression.
      auto ranges = get_invalidated_ranges_for_edit([&]() {
        return input->replace(input->content.find("null"), 0, "b === ");
      });

      assert_node_string_equals(
        ts_document_root_node(document),
        "(program (expression_statement (object "
          "(pair (identifier) (rel_op (identifier) (null))))))");

      AssertThat(ranges, Equals(vector<TSRange>({
        TSRange{
          point(0, input->content.find("b ===")),
          point(0, input->content.find("}"))
        },
      })));
    });
  });

  describe("parse_with_options(options)", [&]() {
    it("halts as soon as an error is found if the halt_on_error flag is set", [&]() {
      string input_string = "[1, null, error, 3]";
      ts_document_set_language(document, load_real_language("json"));
      ts_document_set_input_string(document, input_string.c_str());

      TSParseOptions options;
      options.changed_ranges = nullptr;

      options.halt_on_error = false;
      ts_document_parse_with_options(document, options);
      root = ts_document_root_node(document);
      assert_node_string_equals(
        root,
        "(array (number) (null) (ERROR (UNEXPECTED 'e')) (number))");

      ts_document_invalidate(document);

      options.halt_on_error = true;
      ts_document_parse_with_options(document, options);
      root = ts_document_root_node(document);
      assert_node_string_equals(
        root,
        "(ERROR (number) (null) (UNEXPECTED 'e'))");

      AssertThat(ts_node_end_char(root), Equals(input_string.size()));
      AssertThat(ts_node_end_byte(root), Equals(input_string.size()));
    });

    it("can parse valid code with the halt_on_error flag set", [&]() {
      string input_string = "[1, null, 3]";
      ts_document_set_language(document, load_real_language("json"));
      ts_document_set_input_string(document, input_string.c_str());

      TSParseOptions options;
      options.changed_ranges = nullptr;
      options.halt_on_error = true;
      ts_document_parse_with_options(document, options);
      root = ts_document_root_node(document);
      assert_node_string_equals(
        root,
        "(array (number) (null) (number))");
    });
  });
});

END_TEST
