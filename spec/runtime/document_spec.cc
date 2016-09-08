#include "spec_helper.h"
#include "runtime/alloc.h"
#include "helpers/record_alloc.h"
#include "helpers/stream_methods.h"
#include "helpers/tree_helpers.h"
#include "helpers/point_helpers.h"
#include "helpers/spy_logger.h"
#include "helpers/spy_input.h"
#include "helpers/load_language.h"

START_TEST

describe("Document", [&]() {
  TSDocument *doc;
  TSNode root;

  before_each([&]() {
    record_alloc::start();
    doc = ts_document_new();
  });

  after_each([&]() {
    ts_document_free(doc);
    record_alloc::stop();
    AssertThat(record_alloc::outstanding_allocation_indices(), IsEmpty());
  });

  auto assert_node_string_equals = [&](TSNode node, const string &expected) {
    char *str = ts_node_string(node, doc);
    string actual(str);
    ts_free(str);
    AssertThat(actual, Equals(expected));
  };

  describe("set_input(input)", [&]() {
    SpyInput *spy_input;

    before_each([&]() {
      spy_input = new SpyInput("{\"key\": [null, 2]}", 3);

      ts_document_set_language(doc, get_test_language("json"));
      ts_document_set_input_string(doc, "{\"key\": [1, 2]}");
      ts_document_parse(doc);

      root = ts_document_root_node(doc);
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

      ts_document_set_input(doc, spy_input->input());
      ts_document_invalidate(doc);
      ts_document_parse(doc);

      root = ts_document_root_node(doc);
      assert_node_string_equals(
        root,
        "(array (true) (false))");
    });

    it("allows the input to be retrieved later", [&]() {
      ts_document_set_input(doc, spy_input->input());
      AssertThat(ts_document_input(doc).payload, Equals<void *>(spy_input));
      AssertThat(ts_document_input(doc).read, Equals(spy_input->input().read));
      AssertThat(ts_document_input(doc).seek, Equals(spy_input->input().seek));
    });

    it("does not assume that the document's text has changed", [&]() {
      ts_document_set_input(doc, spy_input->input());
      AssertThat(ts_document_root_node(doc), Equals<TSNode>(root));
      AssertThat(ts_node_has_changes(root), IsFalse());
      AssertThat(spy_input->strings_read, Equals(vector<string>({ "" })));
    });

    it("reads text from the new input for future parses", [&]() {
      ts_document_set_input(doc, spy_input->input());

      // Insert 'null', delete '1'.
      ts_document_edit(doc, {strlen("{\"key\": ["), 4, 1});
      ts_document_parse(doc);

      TSNode new_root = ts_document_root_node(doc);
      assert_node_string_equals(
        new_root,
        "(object (pair (string) (array (null) (number))))");
      AssertThat(spy_input->strings_read, Equals(vector<string>({" [null, 2", ""})));
    });

    it("reads from the new input correctly when the old input was blank", [&]() {
      ts_document_set_input_string(doc, "");
      ts_document_parse(doc);
      TSNode new_root = ts_document_root_node(doc);
      AssertThat(ts_node_end_char(new_root), Equals<size_t>(0));
      assert_node_string_equals(
        new_root,
        "(ERROR)");

      ts_document_set_input_string(doc, "1");
      ts_document_parse(doc);
      new_root = ts_document_root_node(doc);
      AssertThat(ts_node_end_char(new_root), Equals<size_t>(1));
      assert_node_string_equals(
        new_root,
        "(number)");
    });
  });

  describe("set_language(language)", [&]() {
    before_each([&]() {
      ts_document_set_input_string(doc, "{\"key\": [1, 2]}\n");
    });

    it("uses the given language for future parses", [&]() {
      ts_document_set_language(doc, get_test_language("json"));
      ts_document_parse(doc);

      root = ts_document_root_node(doc);
      assert_node_string_equals(
        root,
        "(object (pair (string) (array (number) (number))))");
    });

    it("clears out any previous tree", [&]() {
      ts_document_set_language(doc, get_test_language("json"));
      ts_document_parse(doc);

      ts_document_set_language(doc, get_test_language("javascript"));
      AssertThat(ts_document_root_node(doc).data, Equals<void *>(nullptr));

      ts_document_parse(doc);
      root = ts_document_root_node(doc);
      assert_node_string_equals(
        root,
        "(program (expression_statement "
          "(object (pair (string) (array (number) (number))))))");
    });
  });

  describe("set_logger(TSDebugger)", [&]() {
    SpyLogger *logger;

    before_each([&]() {
      logger = new SpyLogger();
      ts_document_set_language(doc, get_test_language("json"));
      ts_document_set_input_string(doc, "[1, 2]");
    });

    after_each([&]() {
      delete logger;
    });

    it("calls the debugger with a message for each lex action", [&]() {
      ts_document_set_logger(doc, logger->logger());
      ts_document_parse(doc);

      AssertThat(logger->messages, Contains("lookahead char:'1'"));
      AssertThat(logger->messages, Contains("lookahead char:'['"));
    });

    it("calls the debugger with a message for each parse action", [&]() {
      ts_document_set_logger(doc, logger->logger());
      ts_document_parse(doc);

      AssertThat(logger->messages, Contains("new_parse"));
      AssertThat(logger->messages, Contains("lookahead char:'['"));
      AssertThat(logger->messages, Contains("reduce sym:array, child_count:4"));
      AssertThat(logger->messages, Contains("accept"));
    });

    it("allows the debugger to be retrieved later", [&]() {
      ts_document_set_logger(doc, logger->logger());
      AssertThat(ts_document_logger(doc).payload, Equals(logger));
    });

    describe("disabling debugging", [&]() {
      before_each([&]() {
        ts_document_set_logger(doc, logger->logger());
        ts_document_set_logger(doc, {NULL, NULL});
      });

      it("does not call the debugger any more", [&]() {
        ts_document_parse(doc);
        AssertThat(logger->messages, IsEmpty());
      });
    });
  });

  describe("parse_and_diff()", [&]() {
    SpyInput *input;

    before_each([&]() {
      ts_document_set_language(doc, get_test_language("javascript"));
      input = new SpyInput("{a: null};", 3);
      ts_document_set_input(doc, input->input());
      ts_document_parse(doc);
      assert_node_string_equals(
        ts_document_root_node(doc),
        "(program (expression_statement (object (pair (identifier) (null)))))");
    });

    after_each([&]() {
      delete input;
    });

    auto get_ranges = [&](std::function<TSInputEdit()> callback) -> vector<TSRange> {
      TSInputEdit edit = callback();
      ts_document_edit(doc, edit);

      TSRange *ranges;
      size_t range_count = 0;
      ts_document_parse_and_diff(doc, &ranges, &range_count);

      vector<TSRange> result;
      for (size_t i = 0; i < range_count; i++)
        result.push_back(ranges[i]);
      ts_free(ranges);

      return result;
    };

    it("reports changes when one token has been updated", [&]() {
      // Replace `null` with `nothing`
      auto ranges = get_ranges([&]() {
        return input->replace(input->content.find("ull"), 1, "othing");
      });

      AssertThat(ranges, Equals(vector<TSRange>({
        TSRange{
          TSPoint{0, input->content.find("nothing")},
          TSPoint{0, input->content.find("}")}
        },
      })));

      // Replace `nothing` with `null` again
      ranges = get_ranges([&]() {
        return input->undo();
      });

      AssertThat(ranges, Equals(vector<TSRange>({
        TSRange{
          TSPoint{0, input->content.find("null")},
          TSPoint{0, input->content.find("}")}
        },
      })));
    });

    it("reports changes when tokens have been appended", [&]() {
      // Add a second key-value pair
      auto ranges = get_ranges([&]() {
        return input->replace(input->content.find("}"), 0, ", b: false");
      });

      AssertThat(ranges, Equals(vector<TSRange>({
        TSRange{
          TSPoint{0, input->content.find(",")},
          TSPoint{0, input->content.find("}")},
        },
      })));

      // Add a third key-value pair in between the first two
      ranges = get_ranges([&]() {
        return input->replace(input->content.find(", b"), 0, ", c: 1");
      });

      assert_node_string_equals(
        ts_document_root_node(doc),
        "(program (expression_statement (object "
          "(pair (identifier) (null)) "
          "(pair (identifier) (number)) "
          "(pair (identifier) (false)))))");

      AssertThat(ranges, Equals(vector<TSRange>({
        TSRange{
          TSPoint{0, input->content.find(", c")},
          TSPoint{0, input->content.find(", b")},
        },
      })));

      // Delete the middle pair.
      ranges = get_ranges([&]() {
        return input->undo();
      });

      assert_node_string_equals(
        ts_document_root_node(doc),
        "(program (expression_statement (object "
          "(pair (identifier) (null)) "
          "(pair (identifier) (false)))))");

      AssertThat(ranges, Equals(vector<TSRange>({
      })));

      // Delete the second pair.
      ranges = get_ranges([&]() {
        return input->undo();
      });

      assert_node_string_equals(
        ts_document_root_node(doc),
        "(program (expression_statement (object "
          "(pair (identifier) (null)))))");

      AssertThat(ranges, Equals(vector<TSRange>({
      })));
    });

    it("reports changes when trees have been wrapped", [&]() {
      // Wrap the object in an assignment expression.
      auto ranges = get_ranges([&]() {
        return input->replace(0, 0, "x.y = ");
      });

      AssertThat(ranges, Equals(vector<TSRange>({
        TSRange{
          TSPoint{0, 0},
          TSPoint{0, input->content.find(";")},
        },
      })));
    });
  });
});

END_TEST
