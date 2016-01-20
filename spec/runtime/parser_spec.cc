#include "spec_helper.h"
#include "helpers/spy_input.h"
#include "helpers/test_languages.h"
#include "helpers/log_debugger.h"
#include "helpers/record_alloc.h"

START_TEST

describe("Parser", [&]() {
  TSDocument *doc;
  SpyInput *input;
  TSNode root;
  size_t chunk_size;

  before_each([&]() {
    chunk_size = 3;
    input = nullptr;

    doc = ts_document_make();
  });

  after_each([&]() {
    if (doc)
      ts_document_free(doc);

    if (input)
      delete input;
  });

  auto set_text = [&](const char *text) {
    input = new SpyInput(text, chunk_size);
    ts_document_set_input(doc, input->input());
    AssertThat(ts_document_parse(doc), Equals(0));

    root = ts_document_root_node(doc);
    AssertThat(ts_node_end_byte(root), Equals(strlen(text)));
    input->clear();
  };

  auto insert_text = [&](size_t position, string text) {
    size_t prev_size = ts_node_end_byte(root);
    ts_document_edit(doc, input->replace(position, 0, text));
    ts_document_parse(doc);

    root = ts_document_root_node(doc);
    size_t new_size = ts_node_end_byte(root);
    AssertThat(new_size, Equals(prev_size + text.size()));
  };

  auto delete_text = [&](size_t position, size_t length) {
    size_t prev_size = ts_node_end_byte(root);
    ts_document_edit(doc, input->replace(position, length, ""));
    ts_document_parse(doc);

    root = ts_document_root_node(doc);
    size_t new_size = ts_node_end_byte(root);
    AssertThat(new_size, Equals(prev_size - length));
  };

  auto replace_text = [&](size_t position, size_t length, string new_text) {
    size_t prev_size = ts_node_end_byte(root);

    ts_document_edit(doc, input->replace(position, length, new_text));
    ts_document_parse(doc);

    root = ts_document_root_node(doc);
    size_t new_size = ts_node_end_byte(root);
    AssertThat(new_size, Equals(prev_size - length + new_text.size()));
  };

  describe("handling errors", [&]() {
    before_each([&]() {
      ts_document_set_language(doc, get_test_language("json"));
    });

    describe("when the error occurs at the beginning of a token", [&]() {
      it("computes the error node's size and position correctly", [&]() {
        set_text("  [123,  @@@@@,   true]");

        AssertThat(ts_node_string(root, doc), Equals(
          "(array (number) (ERROR (UNEXPECTED '@')) (true))"));

        TSNode error = ts_node_named_child(root, 1);
        TSNode last = ts_node_named_child(root, 2);

        AssertThat(ts_node_name(error, doc), Equals("ERROR"));
        AssertThat(ts_node_start_byte(error), Equals(strlen("  [123,  ")));
        AssertThat(ts_node_end_byte(error), Equals(strlen("  [123,  @@@@@")));

        AssertThat(ts_node_name(last, doc), Equals("true"));
        AssertThat(ts_node_start_byte(last), Equals(strlen("  [123,  @@@@@,   ")))
      });
    });

    describe("when the error occurs in the middle of a token", [&]() {
      it("computes the error node's size and position correctly", [&]() {
        set_text("  [123, faaaaalse, true]");

        AssertThat(ts_node_string(root, doc), Equals(
          "(array (number) (ERROR (UNEXPECTED 'a')) (true))"));

        TSNode error = ts_node_named_child(root, 1);
        TSNode last = ts_node_named_child(root, 2);

        AssertThat(ts_node_symbol(error), Equals(ts_builtin_sym_error));

        AssertThat(ts_node_name(error, doc), Equals("ERROR"));
        AssertThat(ts_node_start_byte(error), Equals(strlen("  [123, ")))
        AssertThat(ts_node_end_byte(error), Equals(strlen("  [123, faaaaalse")))

        AssertThat(ts_node_name(last, doc), Equals("true"));
        AssertThat(ts_node_start_byte(last), Equals(strlen("  [123, faaaaalse, ")));
      });
    });

    describe("when the error occurs after one or more tokens", [&]() {
      it("computes the error node's size and position correctly", [&]() {
        set_text("  [123, true false, true]");

        AssertThat(ts_node_string(root, doc), Equals(
          "(array (number) (ERROR (true) (UNEXPECTED 'f') (false)) (true))"));

        TSNode error = ts_node_named_child(root, 1);
        TSNode last = ts_node_named_child(root, 2);

        AssertThat(ts_node_name(error, doc), Equals("ERROR"));
        AssertThat(ts_node_start_byte(error), Equals(strlen("  [123, ")));
        AssertThat(ts_node_end_byte(error), Equals(strlen("  [123, true false")));

        AssertThat(ts_node_name(last, doc), Equals("true"));
        AssertThat(ts_node_start_byte(last), Equals(strlen("  [123, true false, ")));
      });
    });

    describe("when the error is an empty string", [&]() {
      it("computes the error node's size and position correctly", [&]() {
        set_text("  [123, , true]");

        AssertThat(ts_node_string(root, doc), Equals(
          "(array (number) (ERROR (UNEXPECTED ',')) (true))"));

        TSNode error = ts_node_named_child(root, 1);
        TSNode last = ts_node_named_child(root, 2);

        AssertThat(ts_node_name(error, doc), Equals("ERROR"));
        AssertThat(ts_node_start_byte(error), Equals(strlen("  [123, ")));
        AssertThat(ts_node_end_byte(error), Equals(strlen("  [123, ")))

        AssertThat(ts_node_name(last, doc), Equals("true"));
        AssertThat(ts_node_start_byte(last), Equals(strlen("  [123, , ")));
      });
    });
  });

  describe("handling extra tokens", [&]() {
    // In the javascript example grammar, ASI works by using newlines as
    // terminators in statements, but also as extra tokens.
    before_each([&]() {
      ts_document_set_language(doc, get_test_language("javascript"));
    });

    describe("when the token appears as part of a grammar rule", [&]() {
      it("is incorporated into the tree", [&]() {
        set_text("fn()\n");

        AssertThat(ts_node_string(root, doc), Equals(
          "(program (expression_statement (function_call (identifier))))"));
      });
    });

    describe("when the token appears somewhere else", [&]() {
      it("is incorporated into the tree", [&]() {
        set_text(
          "fn()\n"
          "  .otherFn();");

        AssertThat(ts_node_string(root, doc), Equals(
          "(program (expression_statement (function_call "
            "(member_access (function_call (identifier)) (identifier)))))"));
      });
    });

    describe("when several extra tokens appear in a row", [&]() {
      it("is incorporated into the tree", [&]() {
        set_text(
          "fn()\n\n"
          "// This is a comment"
          "\n\n"
          ".otherFn();");

        AssertThat(ts_node_string(root, doc), Equals(
          "(program (expression_statement (function_call "
            "(member_access (function_call (identifier)) "
              "(comment) "
              "(identifier)))))"));
      });
    });
  });

  describe("editing", [&]() {
    before_each([&]() {
      ts_document_set_language(doc, get_test_language("javascript"));
    });

    describe("inserting text", [&]() {
      describe("creating new tokens near the end of the input", [&]() {
        it("updates the parse tree and re-reads only the changed portion of the text", [&]() {
          set_text("x * (100 + abc);");

          AssertThat(ts_node_string(root, doc), Equals(
            "(program (expression_statement (math_op "
              "(identifier) "
              "(math_op (number) (identifier)))))"));

          insert_text(strlen("x ^ (100 + abc"), ".d");

          AssertThat(ts_node_string(root, doc), Equals(
            "(program (expression_statement (math_op "
              "(identifier) "
              "(math_op (number) (member_access (identifier) (identifier))))))"));

          AssertThat(input->strings_read, Equals(vector<string>({ " abc.d);", "" })));
        });
      });

      describe("creating new tokens near the beginning of the input", [&]() {
        it("updates the parse tree and re-reads only the changed portion of the input", [&]() {
          chunk_size = 2;

          set_text("123 + 456 * (10 + x);");

          AssertThat(ts_node_string(root, doc), Equals(
            "(program (expression_statement (math_op "
              "(number) "
              "(math_op (number) (math_op (number) (identifier))))))"));

          insert_text(strlen("123"), " || 5");

          AssertThat(ts_node_string(root, doc), Equals(
            "(program (expression_statement (bool_op "
              "(number) "
              "(math_op "
                "(number) "
                "(math_op (number) (math_op (number) (identifier)))))))"));

          AssertThat(input->strings_read, Equals(vector<string>({ "123 || 5 +", "" })));
        });
      });

      describe("introducing an error", [&]() {
        it("gives the error the right size", [&]() {
          ts_document_set_language(doc, get_test_language("javascript"));

          set_text("var x = y;");

          AssertThat(ts_node_string(root, doc), Equals(
            "(program (var_declaration (var_assignment "
              "(identifier) (identifier))))"));

          insert_text(strlen("var x = y"), " *");

          AssertThat(ts_node_string(root, doc), Equals(
              "(program (var_declaration (ERROR (identifier) (identifier) (UNEXPECTED ';'))))"));

          insert_text(strlen("var x = y *"), " z");

          AssertThat(ts_node_string(root, doc), Equals(
            "(program (var_declaration (var_assignment "
              "(identifier) (math_op (identifier) (identifier)))))"));
        });
      });

      describe("into the middle of an existing token", [&]() {
        it("updates the parse tree", [&]() {
          set_text("abc * 123;");

          AssertThat(ts_node_string(root, doc), Equals(
            "(program (expression_statement (math_op (identifier) (number))))"));

          insert_text(strlen("ab"), "XYZ");

          AssertThat(ts_node_string(root, doc), Equals(
            "(program (expression_statement (math_op (identifier) (number))))"));

          TSNode node = ts_node_named_descendant_for_range(root, 1, 1);
          AssertThat(ts_node_name(node, doc), Equals("identifier"));
          AssertThat(ts_node_end_byte(node), Equals(strlen("abXYZc")));
        });
      });

      describe("at the end of an existing token", [&]() {
        it("updates the parse tree", [&]() {
          set_text("abc * 123;");

          AssertThat(ts_node_string(root, doc), Equals(
            "(program (expression_statement (math_op (identifier) (number))))"));

          insert_text(strlen("abc"), "XYZ");

          AssertThat(ts_node_string(root, doc), Equals(
            "(program (expression_statement (math_op (identifier) (number))))"));

          TSNode node = ts_node_named_descendant_for_range(root, 1, 1);
          AssertThat(ts_node_name(node, doc), Equals("identifier"));
          AssertThat(ts_node_end_byte(node), Equals(strlen("abcXYZ")));
        });
      });

      describe("with non-ascii characters", [&]() {
        it("inserts the text according to the UTF8 character index", [&]() {
          // 'αβδ' + '1'
          set_text("'\u03b1\u03b2\u03b4' + '1';");

          AssertThat(ts_node_string(root, doc), Equals(
            "(program (expression_statement (math_op (string) (string))))"));

          // 'αβδ' + 'ψ1'
          insert_text(strlen("'abd' + '"), "\u03c8");

          AssertThat(ts_node_string(root, doc), Equals(
            "(program (expression_statement (math_op (string) (string))))"));
        });
      });

      describe("into a node containing a extra token", [&]() {
        it("updates the parse tree", [&]() {
          set_text("123 *\n"
            "// a-comment\n"
            "abc;");

          AssertThat(ts_node_string(root, doc), Equals(
            "(program (expression_statement (math_op "
              "(number) "
              "(comment) "
              "(identifier))))"));

          insert_text(
            strlen("123 *\n"
              "// a-comment\n"
              "abc"),
            "XYZ");

          AssertThat(ts_node_string(root, doc), Equals(
            "(program (expression_statement (math_op "
              "(number) "
              "(comment) "
              "(identifier))))"));
        });
      });
    });

    describe("deleting text", [&]() {
      describe("when a critical token is removed", [&]() {
        it("updates the parse tree, creating an error", [&]() {
          set_text("123 * 456;");

          AssertThat(ts_node_string(root, doc), Equals(
            "(program (expression_statement (math_op (number) (number))))"));

          delete_text(strlen("123 "), 2);

          AssertThat(ts_node_string(root, doc), Equals(
            "(program (expression_statement (ERROR (number) (UNEXPECTED '4') (number))))"));
        });
      });
    });

    describe("replacing text", [&]() {
      it("does not try to re-use nodes that are within the edited region", [&]() {
        ts_document_set_language(doc, get_test_language("javascript"));

        set_text("{ x: (b.c) };");

        AssertThat(ts_node_string(root, doc), Equals(
          "(program (expression_statement (object (pair "
            "(identifier) (member_access (identifier) (identifier))))))"));

        replace_text(strlen("{ x: "), strlen("(b.c)"), "b.c");

        AssertThat(ts_node_string(root, doc), Equals(
          "(program (expression_statement (object (pair "
            "(identifier) (member_access (identifier) (identifier))))))"));
      });
    });

    it("updates the document's parse count", [&]() {
      ts_document_set_language(doc, get_test_language("javascript"));
      AssertThat(ts_document_parse_count(doc), Equals<size_t>(0));

      set_text("{ x: (b.c) };");
      AssertThat(ts_document_parse_count(doc), Equals<size_t>(1));

      insert_text(strlen("{ x"), "yz");
      AssertThat(ts_document_parse_count(doc), Equals<size_t>(2));
    });
  });

  describe("lexing", [&]() {
    before_each([&]() {
      ts_document_set_language(doc, get_test_language("javascript"));
    });

    describe("handling tokens containing wildcard patterns (e.g. comments)", [&]() {
      it("terminates them at the end of the document", [&]() {
        set_text("x; // this is a comment");

        AssertThat(ts_node_string(root, doc), Equals(
          "(program (expression_statement (identifier)) (comment))"));

        TSNode comment = ts_node_named_child(root, 1);

        AssertThat(ts_node_start_byte(comment), Equals(strlen("x; ")));
        AssertThat(ts_node_end_byte(comment), Equals(strlen("x; // this is a comment")));
      });
    });

    it("recognizes UTF8 characters as single characters", [&]() {
      // 'ΩΩΩ — ΔΔ';
      set_text("'\u03A9\u03A9\u03A9 \u2014 \u0394\u0394';");

      AssertThat(ts_node_string(root, doc), Equals(
        "(program (expression_statement (string)))"));

      AssertThat(ts_node_end_char(root), Equals(strlen("'OOO - DD';")));
      AssertThat(ts_node_end_byte(root), Equals(strlen("'\u03A9\u03A9\u03A9 \u2014 \u0394\u0394';")));
    });
  });

  describe("handling allocation failures", [&]() {
    before_each([&]() {
      record_alloc::start();
    });

    after_each([&]() {
      record_alloc::stop();
    });

    it("handles failures when allocating documents", [&]() {
      TSDocument *document = ts_document_make();
      ts_document_free(document);
      AssertThat(record_alloc::outstanding_allocation_indices(), IsEmpty());

      size_t allocation_count = record_alloc::allocation_count();
      AssertThat(allocation_count, IsGreaterThan<size_t>(1));

      for (size_t i = 0; i < allocation_count; i++) {
        record_alloc::start();
        record_alloc::fail_at_allocation_index(i);
        AssertThat(ts_document_make(), Equals<TSDocument *>(nullptr));
        AssertThat(record_alloc::outstanding_allocation_indices(), IsEmpty());
      }
    });

    it("handles allocation failures during parsing", [&]() {
      ts_document_set_language(doc, get_test_language("cpp"));

      set_text("int main() { return vector<int *>().size(); }");

      size_t allocation_count = record_alloc::allocation_count();
      AssertThat(allocation_count, IsGreaterThan<size_t>(1));

      char *string = ts_node_string(root, doc);
      AssertThat(string, Equals("(translation_unit (function_definition "
        "(identifier) "
        "(function_declarator (identifier)) "
        "(compound_statement "
          "(return_statement (call_expression (field_expression "
            "(call_expression (template_call "
              "(identifier) "
              "(type_name (identifier) (abstract_pointer_declarator)))) "
            "(identifier)))))))"));
      free(string);

      for (size_t i = 0; i < allocation_count; i++) {
        record_alloc::start();
        record_alloc::fail_at_allocation_index(i);
        ts_document_invalidate(doc);
        AssertThat(ts_document_parse(doc), Equals(-1));
      }
    });
  });
});

END_TEST
