#include "test_helper.h"
#include "runtime/alloc.h"
#include "helpers/record_alloc.h"
#include "helpers/spy_input.h"
#include "helpers/load_language.h"
#include "helpers/record_alloc.h"
#include "helpers/point_helpers.h"
#include "helpers/stderr_logger.h"
#include "helpers/dedent.h"

START_TEST

describe("Parser", [&]() {
  TSDocument *document;
  SpyInput *input;
  TSNode root;
  size_t chunk_size;

  before_each([&]() {
    record_alloc::start();

    chunk_size = 3;
    input = nullptr;
    document = ts_document_new();
    if (getenv("TREE_SITTER_ENABLE_DEBUG_GRAPHS")) {
      ts_document_print_debugging_graphs(document, true);
    }
  });

  after_each([&]() {
    if (document) ts_document_free(document);
    if (input) delete input;

    record_alloc::stop();
    AssertThat(record_alloc::outstanding_allocation_indices(), IsEmpty());
  });

  auto set_text = [&](string text) {
    input = new SpyInput(text, chunk_size);
    ts_document_set_input(document, input->input());
    ts_document_parse(document);

    root = ts_document_root_node(document);
    AssertThat(ts_node_end_byte(root), Equals(text.size()));
    input->clear();
  };

  auto replace_text = [&](size_t position, size_t length, string new_text) {
    size_t prev_size = ts_node_end_byte(root);

    ts_document_edit(document, input->replace(position, length, new_text));
    ts_document_parse(document);

    root = ts_document_root_node(document);
    size_t new_size = ts_node_end_byte(root);
    AssertThat(new_size, Equals(prev_size - length + new_text.size()));
  };

  auto insert_text = [&](size_t position, string text) {
    replace_text(position, 0, text);
  };

  auto delete_text = [&](size_t position, size_t length) {
    replace_text(position, length, "");
  };

  auto undo = [&]() {
    ts_document_edit(document, input->undo());
    ts_document_parse(document);
  };

  auto assert_root_node = [&](const string &expected) {
    TSNode node = ts_document_root_node(document);
    char *node_string = ts_node_string(node, document);
    string actual(node_string);
    ts_free(node_string);
    AssertThat(actual, Equals(expected));
  };

  auto get_node_text = [&](TSNode node) {
    size_t start = ts_node_start_byte(node);
    size_t end = ts_node_end_byte(node);
    return input->content.substr(start, end - start);
  };

  describe("handling errors", [&]() {
    describe("when there is an invalid substring right before a valid token", [&]() {
      it("computes the error node's size and position correctly", [&]() {
        ts_document_set_language(document, load_real_language("json"));
        set_text("  [123,  @@@@@,   true]");

        assert_root_node(
          "(value (array (number) (ERROR (UNEXPECTED '@')) (true)))");

        TSNode error = ts_node_named_child(ts_node_child(root, 0), 1);
        AssertThat(ts_node_type(error, document), Equals("ERROR"));
        AssertThat(get_node_text(error), Equals("@@@@@,"));
        AssertThat(ts_node_child_count(error), Equals<size_t>(2));

        TSNode garbage = ts_node_child(error, 0);
        AssertThat(get_node_text(garbage), Equals("@@@@@"));

        TSNode comma = ts_node_child(error, 1);
        AssertThat(get_node_text(comma), Equals(","));

        TSNode node_after_error = ts_node_next_named_sibling(error);
        AssertThat(ts_node_type(node_after_error, document), Equals("true"));
        AssertThat(get_node_text(node_after_error), Equals("true"));
      });
    });

    describe("when there is an unexpected string in the middle of a token", [&]() {
      it("computes the error node's size and position correctly", [&]() {
        ts_document_set_language(document, load_real_language("json"));
        set_text("  [123, faaaaalse, true]");

        assert_root_node(
          "(value (array (number) (ERROR (UNEXPECTED 'a')) (true)))");

        TSNode error = ts_node_named_child(ts_node_child(root, 0), 1);
        AssertThat(ts_node_type(error, document), Equals("ERROR"));
        AssertThat(get_node_text(error), Equals("faaaaalse,"));
        AssertThat(ts_node_child_count(error), Equals<size_t>(2));

        TSNode garbage = ts_node_child(error, 0);
        AssertThat(ts_node_type(garbage, document), Equals("ERROR"));
        AssertThat(get_node_text(garbage), Equals("faaaaalse"));

        TSNode comma = ts_node_child(error, 1);
        AssertThat(ts_node_type(comma, document), Equals(","));
        AssertThat(get_node_text(comma), Equals(","));

        TSNode last = ts_node_next_named_sibling(error);
        AssertThat(ts_node_type(last, document), Equals("true"));
        AssertThat(ts_node_start_byte(last), Equals(strlen("  [123, faaaaalse, ")));
      });
    });

    describe("when there is one unexpected token between two valid tokens", [&]() {
      it("computes the error node's size and position correctly", [&]() {
        ts_document_set_language(document, load_real_language("json"));
        set_text("  [123, true false, true]");

        assert_root_node(
          "(value (array (number) (true) (ERROR (false)) (true)))");

        TSNode error = ts_node_named_child(ts_node_child(root, 0), 2);
        AssertThat(ts_node_type(error, document), Equals("ERROR"));
        AssertThat(get_node_text(error), Equals("false"));
        AssertThat(ts_node_child_count(error), Equals<size_t>(1));

        TSNode last = ts_node_next_named_sibling(error);
        AssertThat(ts_node_type(last, document), Equals("true"));
        AssertThat(get_node_text(last), Equals("true"));
      });
    });

    describe("when there is an unexpected string at the end of a token", [&]() {
      it("computes the error's size and position correctly", [&]() {
        ts_document_set_language(document, load_real_language("json"));
        set_text("  [123, \"hi\n, true]");

        assert_root_node(
          "(value (array (number) (ERROR (UNEXPECTED '\\n')) (true)))");
      });
    });

    describe("when there is an unterminated error", [&]() {
      it("maintains a consistent tree", [&]() {
        ts_document_set_language(document, load_real_language("javascript"));
        set_text("a; ' this string never ends");
        assert_root_node(
          "(program (expression_statement (identifier)) (ERROR (UNEXPECTED EOF)))");
      });
    });

    describe("when there are extra tokens at the end of the viable prefix", [&]() {
      it("does not include them in the error node", [&]() {
        ts_document_set_language(document, load_real_language("javascript"));
        set_text(
          "var x;\n"
          "\n"
          "if\n"
          "\n"
          "var y;"
        );

        TSNode error = ts_node_named_child(root, 1);
        AssertThat(ts_node_type(error, document), Equals("ERROR"));
        AssertThat(ts_node_start_point(error), Equals<TSPoint>({2, 0}));
        AssertThat(ts_node_end_point(error), Equals<TSPoint>({2, 2}));
      });
    });

    it("handles invalid UTF8 characters at EOF", [&]() {
      char *string = (char *)malloc(1);
      string[0] = '\xdf';

      ts_document_set_language(document, load_real_language("json"));
      ts_document_set_input_string_with_length(document, string, 1);
      ts_document_parse(document);

      free(string);

      assert_root_node("(ERROR (UNEXPECTED INVALID))");
    });
  });

  describe("handling extra tokens", [&]() {
    describe("when the token appears as part of a grammar rule", [&]() {
      it("incorporates it into the tree", [&]() {
        ts_document_set_language(document, load_real_language("javascript"));
        set_text("fn()\n");

        assert_root_node(
          "(program (expression_statement (call_expression (identifier) (arguments))))");
      });
    });

    describe("when the token appears somewhere else", [&]() {
      it("incorporates it into the tree", [&]() {
        ts_document_set_language(document, load_real_language("javascript"));
        set_text(
          "fn()\n"
          "  .otherFn();");

        assert_root_node(
          "(program (expression_statement (call_expression "
            "(member_expression "
              "(call_expression (identifier) (arguments)) "
              "(property_identifier)) "
            "(arguments))))");
      });
    });

    describe("when several extra tokens appear in a row", [&]() {
      it("incorporates them into the tree", [&]() {
        ts_document_set_language(document, load_real_language("javascript"));
        set_text(
          "fn()\n\n"
          "// This is a comment"
          "\n\n"
          ".otherFn();");

        assert_root_node(
          "(program (expression_statement (call_expression "
            "(member_expression "
              "(call_expression (identifier) (arguments)) "
              "(comment) "
              "(property_identifier)) "
            "(arguments))))");
      });
    });
  });

  describe("editing", [&]() {
    describe("creating new tokens near the end of the input", [&]() {
      it("updates the parse tree and re-reads only the changed portion of the text", [&]() {
        ts_document_set_language(document, load_real_language("javascript"));
        set_text("x * (100 + abc);");

        assert_root_node(
          "(program (expression_statement (binary_expression "
            "(identifier) "
            "(parenthesized_expression "
              "(binary_expression (number) (identifier))))))");

        insert_text(strlen("x * (100 + abc"), ".d");

        assert_root_node(
          "(program (expression_statement (binary_expression "
            "(identifier) "
            "(parenthesized_expression "
              "(binary_expression (number) (member_expression (identifier) (property_identifier)))))))");

        AssertThat(input->strings_read(), Equals(vector<string>({
          // The '*' is not reused because the preceding `x` expression is reused, which
          // puts the parser into a different state than when the `*` was initially tokenized.
          // When the `*` was initially tokenized, `x` was just an identifier. In both of these
          // states, external tokens are valid so we don't reuse tokens unless the lex states
          // match. This could probably be improved somehow.
          " * ",
          " abc.d)"
        })));
      });
    });

    describe("creating new tokens near the beginning of the input", [&]() {
      it("updates the parse tree and re-reads only the changed portion of the input", [&]() {
        chunk_size = 2;

        ts_document_set_language(document, load_real_language("javascript"));
        set_text("123 + 456 * (10 + x);");

        assert_root_node(
          "(program (expression_statement (binary_expression "
            "(number) "
            "(binary_expression (number) (parenthesized_expression (binary_expression (number) (identifier)))))))");

        insert_text(strlen("123"), " || 5");

        assert_root_node(
          "(program (expression_statement (binary_expression "
            "(number) "
            "(binary_expression "
              "(number) "
              "(binary_expression (number) (parenthesized_expression (binary_expression (number) (identifier))))))))");

        AssertThat(input->strings_read(), Equals(vector<string>({
          "123 || 5 ",
          ";"
        })));
      });
    });

    describe("introducing an error", [&]() {
      it("gives the error the right size", [&]() {
        ts_document_set_language(document, load_real_language("javascript"));
        set_text("var x = y;");

        assert_root_node(
          "(program (variable_declaration (variable_declarator "
            "(identifier) (identifier))))");

        insert_text(strlen("var x = y"), " *");

        assert_root_node(
          "(program (variable_declaration (variable_declarator "
            "(identifier) (identifier)) (ERROR)))");

        insert_text(strlen("var x = y *"), " z");

        assert_root_node(
          "(program (variable_declaration (variable_declarator "
            "(identifier) (binary_expression (identifier) (identifier)))))");
      });
    });

    describe("into the middle of an existing token", [&]() {
      it("updates the parse tree", [&]() {
        ts_document_set_language(document, load_real_language("javascript"));
        set_text("abc * 123;");

        assert_root_node(
          "(program (expression_statement (binary_expression (identifier) (number))))");

        insert_text(strlen("ab"), "XYZ");

        assert_root_node(
          "(program (expression_statement (binary_expression (identifier) (number))))");

        TSNode node = ts_node_named_descendant_for_byte_range(root, 1, 1);
        AssertThat(ts_node_type(node, document), Equals("identifier"));
        AssertThat(ts_node_end_byte(node), Equals(strlen("abXYZc")));
      });
    });

    describe("at the end of an existing token", [&]() {
      it("updates the parse tree", [&]() {
        ts_document_set_language(document, load_real_language("javascript"));
        set_text("abc * 123;");

        assert_root_node(
          "(program (expression_statement (binary_expression (identifier) (number))))");

        insert_text(strlen("abc"), "XYZ");

        assert_root_node(
          "(program (expression_statement (binary_expression (identifier) (number))))");

        TSNode node = ts_node_named_descendant_for_byte_range(root, 1, 1);
        AssertThat(ts_node_type(node, document), Equals("identifier"));
        AssertThat(ts_node_end_byte(node), Equals(strlen("abcXYZ")));
      });
    });

    describe("inserting text into a node containing a extra token", [&]() {
      it("updates the parse tree", [&]() {
        ts_document_set_language(document, load_real_language("javascript"));
        set_text("123 *\n"
          "// a-comment\n"
          "abc;");

        assert_root_node(
          "(program (expression_statement (binary_expression "
            "(number) "
            "(comment) "
            "(identifier))))");

        insert_text(
          strlen("123 *\n"
            "// a-comment\n"
            "abc"),
          "XYZ");

        assert_root_node(
          "(program (expression_statement (binary_expression "
            "(number) "
            "(comment) "
            "(identifier))))");
      });
    });

    describe("when a critical token is removed", [&]() {
      it("updates the parse tree, creating an error", [&]() {
        ts_document_set_language(document, load_real_language("javascript"));
        set_text("123 * 456; 789 * 123;");

        assert_root_node(
          "(program "
            "(expression_statement (binary_expression (number) (number))) "
            "(expression_statement (binary_expression (number) (number))))");

        delete_text(strlen("123 "), 2);

        assert_root_node(
          "(program "
            "(ERROR (number)) "
            "(expression_statement (number)) "
            "(expression_statement (binary_expression (number) (number))))");
      });
    });

    describe("with external tokens", [&]() {
      it("maintains the external scanner's state during incremental parsing", [&]() {
        ts_document_set_language(document, load_real_language("python"));
        string text = dedent(R"PYTHON(
          if a:
              print b
          return c
        )PYTHON");

        set_text(text);
        assert_root_node("(module "
          "(if_statement (identifier) "
            "(print_statement (identifier))) "
          "(return_statement (expression_list (identifier))))");

        replace_text(text.find("return"), 0, "    ");
        assert_root_node("(module "
          "(if_statement (identifier) "
            "(print_statement (identifier)) "
            "(return_statement (expression_list (identifier)))))");

        undo();
        assert_root_node("(module "
          "(if_statement (identifier) "
            "(print_statement (identifier))) "
          "(return_statement (expression_list (identifier))))");
      });
    });

    it("does not try to reuse nodes that are within the edited region", [&]() {
      ts_document_set_language(document, load_real_language("javascript"));
      set_text("{ x: (b.c) };");

      assert_root_node(
        "(program (expression_statement (object (pair "
          "(property_identifier) (parenthesized_expression (member_expression (identifier) (property_identifier)))))))");

      replace_text(strlen("{ x: "), strlen("(b.c)"), "b.c");

      assert_root_node(
        "(program (expression_statement (object (pair "
          "(property_identifier) (member_expression (identifier) (property_identifier))))))");
    });

    it("updates the document's parse count", [&]() {
      ts_document_set_language(document, load_real_language("javascript"));
      AssertThat(ts_document_parse_count(document), Equals<size_t>(0));

      set_text("{ x: (b.c) };");
      AssertThat(ts_document_parse_count(document), Equals<size_t>(1));

      insert_text(strlen("{ x"), "yz");
      AssertThat(ts_document_parse_count(document), Equals<size_t>(2));
    });
  });

  describe("lexing", [&]() {
    describe("handling tokens containing wildcard patterns (e.g. comments)", [&]() {
      it("terminates them at the end of the document", [&]() {
        ts_document_set_language(document, load_real_language("javascript"));
        set_text("x; // this is a comment");

        assert_root_node(
          "(program (expression_statement (identifier)) (comment))");

        TSNode comment = ts_node_named_child(root, 1);

        AssertThat(ts_node_start_byte(comment), Equals(strlen("x; ")));
        AssertThat(ts_node_end_byte(comment), Equals(strlen("x; // this is a comment")));
      });
    });

    it("recognizes UTF8 characters as single characters", [&]() {
      // 'ΩΩΩ — ΔΔ';
      ts_document_set_language(document, load_real_language("javascript"));
      set_text("'\u03A9\u03A9\u03A9 \u2014 \u0394\u0394';");

      assert_root_node(
        "(program (expression_statement (string)))");

      AssertThat(ts_node_end_byte(root), Equals(strlen("'\u03A9\u03A9\u03A9 \u2014 \u0394\u0394';")));
    });

    it("handles non-UTF8 characters", [&]() {
      const char *string = "cons\xeb\x00e=ls\x83l6hi');\x0a";

      ts_document_set_language(document, load_real_language("javascript"));
      ts_document_set_input_string(document, string);
      ts_document_parse(document);

      TSNode root = ts_document_root_node(document);
      AssertThat(ts_node_end_byte(root), Equals(strlen(string)));
    });
  });
});

END_TEST
