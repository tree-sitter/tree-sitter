#include "runtime/runtime_spec_helper.h"
#include "runtime/helpers/spy_input.h"
#include "runtime/helpers/log_debugger.h"

extern "C" const TSLanguage * ts_language_json();
extern "C" const TSLanguage * ts_language_javascript();
extern "C" const TSLanguage * ts_language_arithmetic();

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
    ts_document_free(doc);
    if (input)
      delete input;
  });

  auto set_text = [&](const char *text) {
    input = new SpyInput(text, chunk_size);
    ts_document_set_input(doc, input->input());
    root = ts_document_root_node(doc);
    AssertThat(ts_node_size(root).bytes + ts_node_pos(root).bytes, Equals(strlen(text)));
    input->clear();
  };

  auto insert_text = [&](size_t position, string text) {
    size_t prev_size = ts_node_size(root).bytes + ts_node_pos(root).bytes;
    AssertThat(input->insert(position, text), IsTrue());
    ts_document_edit(doc, { position, text.length(), 0 });

    root = ts_document_root_node(doc);
    size_t new_size = ts_node_size(root).bytes + ts_node_pos(root).bytes;
    AssertThat(new_size, Equals(prev_size + text.size()));
  };

  auto delete_text = [&](size_t position, size_t length) {
    size_t prev_size = ts_node_size(root).bytes + ts_node_pos(root).bytes;
    AssertThat(input->erase(position, length), IsTrue());
    ts_document_edit(doc, { position, 0, length });

    root = ts_document_root_node(doc);
    size_t new_size = ts_node_size(root).bytes + ts_node_pos(root).bytes;
    AssertThat(new_size, Equals(prev_size - length));
  };

  auto replace_text = [&](size_t position, size_t length, string new_text) {
    size_t prev_size = ts_node_size(root).bytes + ts_node_pos(root).bytes;
    AssertThat(input->erase(position, length), IsTrue());
    AssertThat(input->insert(position, new_text), IsTrue());

    ts_document_edit(doc, { position, new_text.size(), length });

    root = ts_document_root_node(doc);
    size_t new_size = ts_node_size(root).bytes + ts_node_pos(root).bytes;
    AssertThat(new_size, Equals(prev_size - length + new_text.size()));
  };

  describe("handling errors", [&]() {
    before_each([&]() {
      ts_document_set_language(doc, ts_language_json());
    });

    describe("when the error occurs at the beginning of a token", [&]() {
      it("computes the error node's size and position correctly", [&]() {
        set_text("  [123,  @@@@@,   true]");

        AssertThat(ts_node_string(root, doc), Equals(
          "(DOCUMENT (array (number) (ERROR (UNEXPECTED '@')) (true)))"));

        TSNode array = ts_node_child(root, 0);
        TSNode error = ts_node_child(array, 1);
        TSNode last = ts_node_child(array, 2);

        AssertThat(ts_node_name(error, doc), Equals("ERROR"));
        AssertThat(ts_node_pos(error).bytes, Equals(strlen("  [123,  ")))
        AssertThat(ts_node_size(error).bytes, Equals(strlen("@@@@@")))

        AssertThat(ts_node_name(last, doc), Equals("true"));
        AssertThat(ts_node_pos(last).bytes, Equals(strlen("  [123,  @@@@@,   ")))
      });
    });

    describe("when the error occurs in the middle of a token", [&]() {
      it("computes the error node's size and position correctly", [&]() {
        set_text("  [123, faaaaalse, true]");

        AssertThat(ts_node_string(root, doc), Equals(
          "(DOCUMENT (array (number) (ERROR (UNEXPECTED 'a')) (true)))"));

        TSNode array = ts_node_child(root, 0);
        TSNode error = ts_node_child(array, 1);
        TSNode last = ts_node_child(array, 2);

        AssertThat(ts_node_name(error, doc), Equals("ERROR"));
        AssertThat(ts_node_pos(error).bytes, Equals(strlen("  [123, ")))
        AssertThat(ts_node_size(error).bytes, Equals(strlen("faaaaalse")))

        AssertThat(ts_node_name(last, doc), Equals("true"));
        AssertThat(ts_node_pos(last).bytes, Equals(strlen("  [123, faaaaalse, ")));
      });
    });

    describe("when the error occurs after one or more tokens", [&]() {
      it("computes the error node's size and position correctly", [&]() {
        set_text("  [123, true false, true]");

        AssertThat(ts_node_string(root, doc), Equals(
          "(DOCUMENT (array (number) (ERROR (true) (UNEXPECTED 'f') (false)) (true)))"));

        TSNode array = ts_node_child(root, 0);
        TSNode error = ts_node_child(array, 1);
        TSNode last = ts_node_child(array, 2);

        AssertThat(ts_node_name(error, doc), Equals("ERROR"));
        AssertThat(ts_node_pos(error).bytes, Equals(strlen("  [123, ")));
        AssertThat(ts_node_size(error).bytes, Equals(strlen("true false")));

        AssertThat(ts_node_name(last, doc), Equals("true"));
        AssertThat(ts_node_pos(last).bytes, Equals(strlen("  [123, true false, ")));
      });
    });

    describe("when the error is an empty string", [&]() {
      it("computes the error node's size and position correctly", [&]() {
        set_text("  [123, , true]");

        AssertThat(ts_node_string(root, doc), Equals(
          "(DOCUMENT (array (number) (ERROR (UNEXPECTED ',')) (true)))"));

        TSNode array = ts_node_child(root, 0);
        TSNode error = ts_node_child(array, 1);
        TSNode last = ts_node_child(array, 2);

        AssertThat(ts_node_name(error, doc), Equals("ERROR"));
        AssertThat(ts_node_pos(error).bytes, Equals(strlen("  [123, ")));
        AssertThat(ts_node_size(error).bytes, Equals<size_t>(0))

        AssertThat(ts_node_name(last, doc), Equals("true"));
        AssertThat(ts_node_pos(last).bytes, Equals(strlen("  [123, , ")));
      });
    });
  });

  describe("handling ubiquitous tokens", [&]() {
    // In the javascript example grammar, ASI works by using newlines as
    // terminators in statements, but also as ubiquitous tokens.
    before_each([&]() {
      ts_document_set_language(doc, ts_language_javascript());
    });

    describe("when the token appears as part of a grammar rule", [&]() {
      it("is incorporated into the tree", [&]() {
        set_text("fn()\n");

        AssertThat(ts_node_string(root, doc), Equals(
          "(DOCUMENT (expression_statement (function_call (identifier))))"));
      });
    });

    describe("when the token appears somewhere else", [&]() {
      it("is incorporated into the tree", [&]() {
        set_text(
          "fn()\n"
          "  .otherFn();");

        AssertThat(ts_node_string(root, doc), Equals(
          "(DOCUMENT "
            "(expression_statement (function_call "
              "(member_access (function_call (identifier)) (identifier)))))"));
      });
    });

    describe("when several ubiquitous tokens appear in a row", [&]() {
      it("is incorporated into the tree", [&]() {
        set_text(
          "fn()\n\n"
          "// This is a comment"
          "\n\n"
          ".otherFn();");

        AssertThat(ts_node_string(root, doc), Equals(
          "(DOCUMENT "
            "(expression_statement (function_call "
              "(member_access (function_call (identifier)) "
                "(comment) "
                "(identifier)))))"));
      });
    });
  });

  describe("editing", [&]() {
    before_each([&]() {
      ts_document_set_language(doc, ts_language_arithmetic());
    });

    describe("inserting text", [&]() {
      describe("creating new tokens near the end of the input", [&]() {
        before_each([&]() {
          set_text("x ^ (100 + abc)");

          AssertThat(ts_node_string(root, doc), Equals(
            "(DOCUMENT (exponent "
              "(variable) "
              "(group (sum (number) (variable)))))"));

          insert_text(strlen("x ^ (100 + abc"), " * 5");
        });

        it("updates the parse tree", [&]() {
          AssertThat(ts_node_string(root, doc), Equals(
            "(DOCUMENT (exponent "
              "(variable) "
              "(group (sum (number) (product (variable) (number))))))"));
        });

        it("re-reads only the changed portion of the input", [&]() {
          AssertThat(input->strings_read, Equals(vector<string>({ " abc * 5)" })));
        });
      });

      describe("creating new tokens near the beginning of the input", [&]() {
        before_each([&]() {
          chunk_size = 2;

          set_text("123 * 456 ^ (10 + x)");

          AssertThat(ts_node_string(root, doc), Equals(
            "(DOCUMENT (product "
              "(number) "
              "(exponent (number) (group (sum (number) (variable))))))"));

          insert_text(strlen("123"), " + 5");
        });

        it("updates the parse tree", [&]() {
          AssertThat(ts_node_string(root, doc), Equals(
            "(DOCUMENT (sum "
              "(number) "
              "(product "
                "(number) "
                "(exponent (number) (group (sum (number) (variable)))))))"));
        });

        it("re-reads only the changed portion of the input", [&]() {
          AssertThat(input->strings_read, Equals(vector<string>({ "123 + 5 ", " 4", " ^ (", "" })));
        });
      });

      describe("introducing an error", [&]() {
        it("gives the error the right size", [&]() {
          ts_document_set_language(doc, ts_language_javascript());

          set_text("var x = y;");

          AssertThat(ts_node_string(root, doc), Equals(
            "(DOCUMENT (var_declaration (var_assignment "
              "(identifier) (identifier))))"));

          insert_text(strlen("var x = y"), " *");

          AssertThat(ts_node_string(root, doc), Equals(
              "(DOCUMENT (var_declaration (ERROR (identifier) (identifier) (UNEXPECTED ';'))))"));

          insert_text(strlen("var x = y *"), " z");

          AssertThat(ts_node_string(root, doc), Equals(
            "(DOCUMENT (var_declaration (var_assignment "
              "(identifier) (math_op (identifier) (identifier)))))"));
        });
      });

      describe("into the middle of an existing token", [&]() {
        before_each([&]() {
          set_text("abc * 123");

          AssertThat(ts_node_string(root, doc), Equals(
            "(DOCUMENT (product (variable) (number)))"));

          insert_text(strlen("ab"), "XYZ");
        });

        it("updates the parse tree", [&]() {
          AssertThat(ts_node_string(root, doc), Equals(
            "(DOCUMENT (product (variable) (number)))"));

          TSNode node = ts_node_find_for_pos(root, 1);
          AssertThat(ts_node_name(node, doc), Equals("variable"));
          AssertThat(ts_node_size(node).bytes, Equals(strlen("abXYZc")));
        });
      });

      describe("at the end of an existing token", [&]() {
        before_each([&]() {
          set_text("abc * 123");

          AssertThat(ts_node_string(root, doc), Equals(
            "(DOCUMENT (product (variable) (number)))"));

          insert_text(strlen("abc"), "XYZ");
        });

        it("updates the parse tree", [&]() {
          AssertThat(ts_node_string(root, doc), Equals(
            "(DOCUMENT (product (variable) (number)))"));

          TSNode node = ts_node_find_for_pos(root, 1);
          AssertThat(ts_node_name(node, doc), Equals("variable"));
          AssertThat(ts_node_size(node).bytes, Equals(strlen("abcXYZ")));
        });
      });

      describe("with non-ascii characters", [&]() {
        before_each([&]() {
          // αβδ + 1
          set_text("\u03b1\u03b2\u03b4 + 1");

          AssertThat(ts_node_string(root, doc), Equals(
            "(DOCUMENT (sum (variable) (number)))"));

          // αβδ + ψ1
          insert_text(strlen("abd + "), "\u03c8");
        });

        it("inserts the text according to the UTF8 character index", [&]() {
          AssertThat(ts_node_string(root, doc), Equals(
            "(DOCUMENT (sum (variable) (variable)))"));
        });
      });

      describe("into a node containing a ubiquitous token", [&]() {
        before_each([&]() {
          set_text("123 *\n"
            "# a-comment\n"
            "abc");

          AssertThat(ts_node_string(root, doc), Equals(
            "(DOCUMENT (product (number) (comment) (variable)))"));

          insert_text(
            strlen("123 *\n"
              "# a-comment\n"
              "abc"),
            "XYZ");
        });

        it("updates the parse tree", [&]() {
          AssertThat(ts_node_string(root, doc), Equals(
            "(DOCUMENT (product (number) (comment) (variable)))"));
        });
      });
    });

    describe("deleting text", [&]() {
      describe("when a critical token is removed", [&]() {
        before_each([&]() {
          set_text("123 * 456");

          AssertThat(ts_node_string(root, doc), Equals(
            "(DOCUMENT (product (number) (number)))"));

          delete_text(strlen("123 "), 2);
        });

        it("updates the parse tree, creating an error", [&]() {
          AssertThat(ts_node_string(root, doc), Equals(
            "(DOCUMENT (number) (ERROR (UNEXPECTED '4') (number)))"));
        });
      });
    });

    describe("replacing text", [&]() {
      it("does not try to re-use nodes that are within the edited region", [&]() {
        ts_document_set_language(doc, ts_language_javascript());

        set_text("{ x: (b.c) };");

        AssertThat(ts_node_string(root, doc), Equals(
          "(DOCUMENT (expression_statement (object (pair "
            "(identifier) (expression (member_access (identifier) (identifier)))))))"));

        replace_text(strlen("{ x: "), strlen("(b.c)"), "b.c");

        AssertThat(ts_node_string(root, doc), Equals(
          "(DOCUMENT (expression_statement (object (pair "
            "(identifier) (member_access (identifier) (identifier))))))"));
      });
    });
  });

  describe("lexing", [&]() {
    before_each([&]() {
      ts_document_set_language(doc, ts_language_arithmetic());
    });

    describe("handling tokens containing wildcard patterns (e.g. comments)", [&]() {
      it("terminates them at the end of the document", [&]() {
        set_text("x # this is a comment");

        AssertThat(ts_node_string(root, doc), Equals("(DOCUMENT "
          "(expression (variable) (comment)))"));

        TSNode expression = ts_node_child(root, 0);
        TSNode comment = ts_node_child(expression, 1);

        AssertThat(ts_node_size(comment).bytes, Equals(strlen("# this is a comment")));
      });
    });

    it("recognizes UTF8 characters as single characters", [&]() {
      // x # ΩΩΩ — ΔΔ
      set_text("x # \u03A9\u03A9\u03A9 \u2014 \u0394\u0394");

      AssertThat(ts_node_string(root, doc), Equals("(DOCUMENT "
        "(expression (variable) (comment)))"));

      AssertThat(ts_node_size(root).chars, Equals(strlen("x # OOO - DD")));
      AssertThat(ts_node_size(root).bytes, Equals(strlen("x # \u03A9\u03A9\u03A9 \u2014 \u0394\u0394")));
    });
  });
});

END_TEST
