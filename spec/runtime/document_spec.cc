#include "spec_helper.h"
#include "runtime/alloc.h"
#include "runtime/debugger.h"
#include "helpers/record_alloc.h"
#include "helpers/stream_methods.h"
#include "helpers/tree_helpers.h"
#include "helpers/spy_debugger.h"
#include "helpers/spy_input.h"
#include "helpers/test_languages.h"

START_TEST

describe("Document", [&]() {
  TSDocument *doc;
  TSNode root;

  before_each([&]() {
    record_alloc::start();
    doc = ts_document_make();
  });

  after_each([&]() {
    ts_document_free(doc);
    record_alloc::stop();
    AssertThat(record_alloc::outstanding_allocation_indices(), IsEmpty());
  });

  auto assert_node_string_equals = [&](TSNode node, const string &expected) {
    char *actual = ts_node_string(node, doc);
    AssertThat(actual, Equals(expected));
    ts_free(actual);
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
      AssertThat(ts_document_input(doc).read_fn, Equals(spy_input->input().read_fn));
      AssertThat(ts_document_input(doc).seek_fn, Equals(spy_input->input().seek_fn));
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
      assert_node_string_equals(
        new_root,
        "(ERROR (UNEXPECTED <EOF>))");

      ts_document_set_input_string(doc, "1");
      ts_document_parse(doc);
      new_root = ts_document_root_node(doc);
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

  describe("set_debugger(TSDebugger)", [&]() {
    SpyDebugger *debugger;

    before_each([&]() {
      debugger = new SpyDebugger();
      ts_document_set_language(doc, get_test_language("json"));
      ts_document_set_input_string(doc, "[1, 2]");
    });

    after_each([&]() {
      delete debugger;
    });

    it("calls the debugger with a message for each lex action", [&]() {
      ts_document_set_debugger(doc, debugger->debugger());
      ts_document_parse(doc);

      AssertThat(debugger->messages, Contains("lookahead char:'1'"));
      AssertThat(debugger->messages, Contains("advance state:1"));
      AssertThat(debugger->messages, Contains("accept_token sym:number"));
    });

    it("calls the debugger with a message for each parse action", [&]() {
      ts_document_set_debugger(doc, debugger->debugger());
      ts_document_parse(doc);

      AssertThat(debugger->messages, Contains("new_parse"));
      AssertThat(debugger->messages, Contains("lookahead char:'['"));
      AssertThat(debugger->messages, Contains("reduce sym:array, child_count:4, fragile:false"));
      AssertThat(debugger->messages, Contains("accept"));
    });

    it("allows the debugger to be retrieved later", [&]() {
      ts_document_set_debugger(doc, debugger->debugger());
      AssertThat(ts_document_debugger(doc).payload, Equals(debugger));
    });

    describe("disabling debugging", [&]() {
      before_each([&]() {
        ts_document_set_debugger(doc, debugger->debugger());
        ts_document_set_debugger(doc, ts_debugger_null());
      });

      it("does not call the debugger any more", [&]() {
        ts_document_parse(doc);
        AssertThat(debugger->messages, IsEmpty());
      });
    });
  });
});

END_TEST
