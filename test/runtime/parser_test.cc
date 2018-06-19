#include "test_helper.h"
#include <future>
#include "runtime/alloc.h"
#include "runtime/language.h"
#include "helpers/record_alloc.h"
#include "helpers/spy_input.h"
#include "helpers/load_language.h"
#include "helpers/record_alloc.h"
#include "helpers/point_helpers.h"
#include "helpers/spy_logger.h"
#include "helpers/stderr_logger.h"
#include "helpers/dedent.h"

START_TEST

describe("Parser", [&]() {
  TSParser *parser;
  TSTree *tree;
  SpyInput *input;
  TSNode root;
  size_t chunk_size;

  before_each([&]() {
    record_alloc::start();

    chunk_size = 3;
    input = nullptr;
    tree = nullptr;
    parser = ts_parser_new();
    if (getenv("TREE_SITTER_ENABLE_DEBUG_GRAPHS")) {
      ts_parser_print_dot_graphs(parser, stderr);
    }
  });

  after_each([&]() {
    if (parser) ts_parser_delete(parser);
    if (tree) ts_tree_delete(tree);
    if (input) delete input;

    record_alloc::stop();
    AssertThat(record_alloc::outstanding_allocation_indices(), IsEmpty());
  });

  auto set_text = [&](string text) {
    input = new SpyInput(text, chunk_size);
    tree = ts_parser_parse(parser, nullptr, input->input());
    root = ts_tree_root_node(tree);
    AssertThat(ts_node_end_byte(root), Equals(text.size()));
    input->clear();
  };

  auto replace_text = [&](size_t position, size_t length, string new_text) {
    size_t prev_size = ts_node_end_byte(root);

    TSInputEdit edit = input->replace(position, length, new_text);
    ts_tree_edit(tree, &edit);
    TSTree *new_tree = ts_parser_parse(parser, tree, input->input());
    ts_tree_delete(tree);
    tree = new_tree;

    root = ts_tree_root_node(tree);
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
    TSInputEdit edit = input->undo();
    ts_tree_edit(tree, &edit);
    TSTree *new_tree = ts_parser_parse(parser, tree, input->input());
    ts_tree_delete(tree);
    tree = new_tree;
  };

  auto assert_root_node = [&](const string &expected) {
    TSNode node = ts_tree_root_node(tree);
    char *node_string = ts_node_string(node);
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
        ts_parser_set_language(parser, load_real_language("json"));
        set_text("  [123,  @@@@@,   true]");
        assert_root_node("(value (array (number) (ERROR (UNEXPECTED '@')) (true)))");

        TSNode error = ts_node_named_child(ts_node_child(root, 0), 1);
        AssertThat(ts_node_type(error), Equals("ERROR"));
        AssertThat(get_node_text(error), Equals("@@@@@,"));
        AssertThat(ts_node_child_count(error), Equals<size_t>(2));

        TSNode garbage = ts_node_child(error, 0);
        AssertThat(get_node_text(garbage), Equals("@@@@@"));

        TSNode comma = ts_node_child(error, 1);
        AssertThat(get_node_text(comma), Equals(","));

        TSNode node_after_error = ts_node_next_named_sibling(error);
        AssertThat(ts_node_type(node_after_error), Equals("true"));
        AssertThat(get_node_text(node_after_error), Equals("true"));
      });
    });

    describe("when there is an unexpected string in the middle of a token", [&]() {
      it("computes the error node's size and position correctly", [&]() {
        ts_parser_set_language(parser, load_real_language("json"));
        set_text("  [123, faaaaalse, true]");

        assert_root_node(
          "(value (array (number) (ERROR (UNEXPECTED 'a')) (true)))");

        TSNode error = ts_node_named_child(ts_node_child(root, 0), 1);
        AssertThat(ts_node_type(error), Equals("ERROR"));
        AssertThat(get_node_text(error), Equals("faaaaalse,"));
        AssertThat(ts_node_child_count(error), Equals<size_t>(2));

        TSNode garbage = ts_node_child(error, 0);
        AssertThat(ts_node_type(garbage), Equals("ERROR"));
        AssertThat(get_node_text(garbage), Equals("faaaaalse"));

        TSNode comma = ts_node_child(error, 1);
        AssertThat(ts_node_type(comma), Equals(","));
        AssertThat(get_node_text(comma), Equals(","));

        TSNode last = ts_node_next_named_sibling(error);
        AssertThat(ts_node_type(last), Equals("true"));
        AssertThat(ts_node_start_byte(last), Equals(strlen("  [123, faaaaalse, ")));
      });
    });

    describe("when there is one unexpected token between two valid tokens", [&]() {
      it("computes the error node's size and position correctly", [&]() {
        ts_parser_set_language(parser, load_real_language("json"));
        set_text("  [123, true false, true]");

        assert_root_node("(value (array (number) (true) (ERROR (false)) (true)))");

        TSNode error = ts_node_named_child(ts_node_child(root, 0), 2);
        AssertThat(ts_node_type(error), Equals("ERROR"));
        AssertThat(get_node_text(error), Equals("false"));
        AssertThat(ts_node_child_count(error), Equals<size_t>(1));

        TSNode last = ts_node_next_named_sibling(error);
        AssertThat(ts_node_type(last), Equals("true"));
        AssertThat(get_node_text(last), Equals("true"));
      });
    });

    describe("when there is an unexpected string at the end of a token", [&]() {
      it("computes the error's size and position correctly", [&]() {
        ts_parser_set_language(parser, load_real_language("json"));
        set_text("  [123, \"hi\n, true]");
        assert_root_node("(value (array (number) (ERROR (UNEXPECTED '\\n')) (true)))");
      });
    });

    describe("when there is an unterminated error", [&]() {
      it("maintains a consistent tree", [&]() {
        ts_parser_set_language(parser, load_real_language("javascript"));
        set_text("a; ' this string never ends");
        assert_root_node("(program (expression_statement (identifier)) (ERROR (UNEXPECTED EOF)))");
      });
    });

    describe("when there are extra tokens at the end of the viable prefix", [&]() {
      it("does not include them in the error node", [&]() {
        ts_parser_set_language(parser, load_real_language("javascript"));
        set_text(
          "var x;\n"
          "\n"
          "if\n"
          "\n"
          "var y;"
        );

        TSNode error = ts_node_named_child(root, 1);
        AssertThat(ts_node_type(error), Equals("ERROR"));
        AssertThat(ts_node_start_point(error), Equals<TSPoint>({2, 0}));
        AssertThat(ts_node_end_point(error), Equals<TSPoint>({2, 2}));
      });
    });

    it("handles invalid UTF8 characters at EOF", [&]() {
      char *string = (char *)malloc(1);
      string[0] = '\xdf';

      ts_parser_set_language(parser, load_real_language("json"));
      tree = ts_parser_parse_string(parser, nullptr, string, 1);

      free(string);
      assert_root_node("(ERROR (UNEXPECTED INVALID))");
    });

    describe("when halt_on_error is set to true", [&]() {
      it("halts as soon as an error is found if the halt_on_error flag is set", [&]() {
        string input_string = "[1, null, error, 3]";
        ts_parser_set_language(parser, load_real_language("json"));

        tree = ts_parser_parse_string(parser, nullptr, input_string.c_str(), input_string.size());
        root = ts_tree_root_node(tree);
        assert_root_node("(value (array (number) (null) (ERROR (UNEXPECTED 'e')) (number)))");

        ts_parser_halt_on_error(parser, true);

        ts_tree_delete(tree);
        tree = ts_parser_parse_string(parser, nullptr, input_string.c_str(), input_string.size());
        root = ts_tree_root_node(tree);
        assert_root_node("(ERROR (number) (null))");
        AssertThat(ts_node_end_byte(root), Equals(input_string.size()));
      });

      it("does not insert missing tokens if the halt_on_error flag is set", [&]() {
        string input_string = "[1, null, 3";
        ts_parser_set_language(parser, load_real_language("json"));

        tree = ts_parser_parse_string(parser, nullptr, input_string.c_str(), input_string.size());
        root = ts_tree_root_node(tree);
        assert_root_node("(value (array (number) (null) (number) (MISSING)))");

        ts_parser_halt_on_error(parser, true);

        ts_tree_delete(tree);
        tree = ts_parser_parse_string(parser, nullptr, input_string.c_str(), input_string.size());
        root = ts_tree_root_node(tree);
        assert_root_node("(ERROR (number) (null) (number))");
        AssertThat(ts_node_end_byte(root), Equals(input_string.size()));
      });

      it("can parse valid code with the halt_on_error flag set", [&]() {
        string input_string = "[1, null, 3]";
        ts_parser_set_language(parser, load_real_language("json"));

        ts_parser_halt_on_error(parser, true);
        tree = ts_parser_parse_string(parser, nullptr, input_string.c_str(), input_string.size());
        root = ts_tree_root_node(tree);
        assert_root_node("(value (array (number) (null) (number)))");
      });
    });
  });

  describe("editing", [&]() {
    describe("creating new tokens near the end of the input", [&]() {
      it("updates the parse tree and re-reads only the changed portion of the text", [&]() {
        ts_parser_set_language(parser, load_real_language("javascript"));
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

        ts_parser_set_language(parser, load_real_language("javascript"));
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
        ts_parser_set_language(parser, load_real_language("javascript"));
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
        ts_parser_set_language(parser, load_real_language("javascript"));
        set_text("abc * 123;");

        assert_root_node(
          "(program (expression_statement (binary_expression (identifier) (number))))");

        insert_text(strlen("ab"), "XYZ");

        assert_root_node(
          "(program (expression_statement (binary_expression (identifier) (number))))");

        TSNode node = ts_node_named_descendant_for_byte_range(root, 1, 1);
        AssertThat(ts_node_type(node), Equals("identifier"));
        AssertThat(ts_node_end_byte(node), Equals(strlen("abXYZc")));
      });
    });

    describe("at the end of an existing token", [&]() {
      it("updates the parse tree", [&]() {
        ts_parser_set_language(parser, load_real_language("javascript"));
        set_text("abc * 123;");

        assert_root_node(
          "(program (expression_statement (binary_expression (identifier) (number))))");

        insert_text(strlen("abc"), "XYZ");

        assert_root_node(
          "(program (expression_statement (binary_expression (identifier) (number))))");

        TSNode node = ts_node_named_descendant_for_byte_range(root, 1, 1);
        AssertThat(ts_node_type(node), Equals("identifier"));
        AssertThat(ts_node_end_byte(node), Equals(strlen("abcXYZ")));
      });
    });

    describe("inserting text into a node containing a extra token", [&]() {
      it("updates the parse tree", [&]() {
        ts_parser_set_language(parser, load_real_language("javascript"));
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
        ts_parser_set_language(parser, load_real_language("javascript"));
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
        ts_parser_set_language(parser, load_real_language("python"));
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
      ts_parser_set_language(parser, load_real_language("javascript"));
      set_text("{ x: (b.c) };");

      assert_root_node(
        "(program (expression_statement (object (pair "
          "(property_identifier) (parenthesized_expression (member_expression (identifier) (property_identifier)))))))");

      replace_text(strlen("{ x: "), strlen("(b.c)"), "b.c");

      assert_root_node(
        "(program (expression_statement (object (pair "
          "(property_identifier) (member_expression (identifier) (property_identifier))))))");
    });
  });

  describe("lexing", [&]() {
    describe("handling tokens containing wildcard patterns (e.g. comments)", [&]() {
      it("terminates them at the end of the string", [&]() {
        ts_parser_set_language(parser, load_real_language("javascript"));
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
      ts_parser_set_language(parser, load_real_language("javascript"));
      set_text("'\u03A9\u03A9\u03A9 \u2014 \u0394\u0394';");

      assert_root_node(
        "(program (expression_statement (string)))");

      AssertThat(ts_node_end_byte(root), Equals(strlen("'\u03A9\u03A9\u03A9 \u2014 \u0394\u0394';")));
    });

    it("handles non-UTF8 characters", [&]() {
      const char *string = "cons\xeb\x00e=ls\x83l6hi');\x0a";

      ts_parser_set_language(parser, load_real_language("javascript"));
      tree = ts_parser_parse_string(parser, nullptr, string, strlen(string));
      TSNode root = ts_tree_root_node(tree);
      AssertThat(ts_node_end_byte(root), Equals(strlen(string)));
    });
  });

  describe("handling TSInputs", [&]() {
    SpyInput *spy_input;

    before_each([&]() {
      spy_input = new SpyInput("{\"key\": [null, 2]}", 3);
      ts_parser_set_language(parser, load_real_language("json"));
    });

    after_each([&]() {
      delete spy_input;
    });

    it("handles UTF16 encodings", [&]() {
      const char16_t content[] = u"[true, false]";
      spy_input->content = string((const char *)content, sizeof(content));
      spy_input->encoding = TSInputEncodingUTF16;

      tree = ts_parser_parse(parser, nullptr, spy_input->input());
      root = ts_tree_root_node(tree);
      assert_root_node(
        "(value (array (true) (false)))");
    });

    it("handles truncated UTF16 data", [&]() {
      const char content[1] = { '\0' };
      spy_input->content = string(content, sizeof(content));
      spy_input->encoding = TSInputEncodingUTF16;

      tree = ts_parser_parse(parser, nullptr, spy_input->input());
    });

    it("measures columns in bytes", [&]() {
      const char16_t content[] = u"[true, false]";
      spy_input->content = string((const char *)content, sizeof(content));
      spy_input->encoding = TSInputEncodingUTF16;

      tree = ts_parser_parse(parser, nullptr, spy_input->input());
      root = ts_tree_root_node(tree);
      AssertThat(ts_node_end_point(root), Equals<TSPoint>({0, 28}));
    });
  });

  describe("set_language(language)", [&]() {
    string input_string = "{\"key\": [1, 2]}\n";

    it("uses the given language for future parses", [&]() {
      ts_parser_set_language(parser, load_real_language("json"));
      tree = ts_parser_parse_string(parser, nullptr, input_string.c_str(), input_string.size());

      root = ts_tree_root_node(tree);
      assert_root_node(
        "(value (object (pair (string) (array (number) (number)))))");
    });

    it("does not allow setting a language with a different version number", [&]() {
      TSLanguage language = *load_real_language("json");
      AssertThat(ts_language_version(&language), Equals<uint32_t>(TREE_SITTER_LANGUAGE_VERSION));

      language.version++;
      AssertThat(ts_language_version(&language), !Equals<uint32_t>(TREE_SITTER_LANGUAGE_VERSION));

      AssertThat(ts_parser_set_language(parser, &language), IsFalse());
      AssertThat(ts_parser_language(parser), Equals<const TSLanguage *>(nullptr));
    });

    it("does nothing when parse is called while the language is null", [&]() {
      tree = ts_parser_parse_string(parser, nullptr, "{}", 2);
      AssertThat(tree, Equals<TSTree *>(nullptr));

      ts_parser_set_language(parser, nullptr);
      tree = ts_parser_parse_string(parser, nullptr, "{}", 2);
      AssertThat(tree, Equals<TSTree *>(nullptr));
    });
  });

  describe("set_logger(TSLogger)", [&]() {
    SpyLogger *logger;

    before_each([&]() {
      logger = new SpyLogger();
      ts_parser_set_language(parser, load_real_language("json"));
    });

    after_each([&]() {
      delete logger;
    });

    it("calls the debugger with a message for each parse action", [&]() {
      ts_parser_set_logger(parser, logger->logger());
      tree = ts_parser_parse_string(parser, nullptr, "[ 1, 2, 3 ]", 11);

      AssertThat(logger->messages, Contains("new_parse"));
      AssertThat(logger->messages, Contains("skip character:' '"));
      AssertThat(logger->messages, Contains("consume character:'['"));
      AssertThat(logger->messages, Contains("consume character:'1'"));
      AssertThat(logger->messages, Contains("reduce sym:array, child_count:4"));
      AssertThat(logger->messages, Contains("accept"));
    });

    it("allows the debugger to be retrieved later", [&]() {
      ts_parser_set_logger(parser, logger->logger());
      AssertThat(ts_parser_logger(parser).payload, Equals(logger));
    });

    describe("disabling debugging", [&]() {
      before_each([&]() {
        ts_parser_set_logger(parser, logger->logger());
        ts_parser_set_logger(parser, {NULL, NULL});
      });

      it("does not call the debugger any more", [&]() {
        tree = ts_parser_parse_string(parser, nullptr, "{}", 2);
        AssertThat(logger->messages, IsEmpty());
      });
    });
  });

  describe("set_enabled(enabled)", [&]() {
    it("stops the in-progress parse if false is passed", [&]() {
      ts_parser_set_language(parser, load_real_language("json"));
      AssertThat(ts_parser_enabled(parser), IsTrue());

      auto tree_future = std::async([parser]() {
        size_t read_count = 0;
        TSInput infinite_input = {
          &read_count,
          [](void *payload, uint32_t byte, TSPoint position, uint32_t *bytes_read) {
            size_t *read_count = static_cast<size_t *>(payload);
            assert((*read_count)++ < 100000);
            *bytes_read = 1;
            return "[";
          },
          TSInputEncodingUTF8
        };

        return ts_parser_parse(parser, nullptr, infinite_input);
      });

      auto cancel_future = std::async([parser]() {
        ts_parser_set_enabled(parser, false);
      });

      cancel_future.wait();
      tree_future.wait();
      AssertThat(ts_parser_enabled(parser), IsFalse());
      AssertThat(tree_future.get(), Equals<TSTree *>(nullptr));

      TSTree *tree = ts_parser_parse_string(parser, nullptr, "[]", 2);
      AssertThat(ts_parser_enabled(parser), IsFalse());
      AssertThat(tree, Equals<TSTree *>(nullptr));

      ts_parser_set_enabled(parser, true);
      AssertThat(ts_parser_enabled(parser), IsTrue());
      tree = ts_parser_parse_string(parser, nullptr, "[]", 2);
      AssertThat(tree, !Equals<TSTree *>(nullptr));
      ts_tree_delete(tree);
    });
  });

  describe("set_operation_limit(limit)", [&]() {
    it("limits the amount of work the parser does on any given call to parse()", [&]() {
      ts_parser_set_language(parser, load_real_language("json"));

      struct InputState {
        const char *string;
        size_t read_count;
      };

      InputState state = {"[", 0};

      // An input that repeats the given string forever, counting how many times
      // it has been read.
      TSInput infinite_input = {
        &state,
        [](void *payload, uint32_t byte, TSPoint position, uint32_t *bytes_read) {
          InputState *state = static_cast<InputState *>(payload);
          assert(state->read_count++ <= 11);
          *bytes_read = strlen(state->string);
          return state->string;
        },
        TSInputEncodingUTF8
      };

      ts_parser_set_operation_limit(parser, 10);
      TSTree *tree = ts_parser_parse(parser, nullptr, infinite_input);
      AssertThat(tree, Equals<TSTree *>(nullptr));

      state.read_count = 0;
      state.string = "";

      tree = ts_parser_parse(parser, nullptr, infinite_input);
      AssertThat(tree, !Equals<TSTree *>(nullptr));
      ts_tree_delete(tree);
    });

    it("retains the old tree even if the parser halts before finishing parsing", [&]() {
      ts_parser_set_language(parser, load_real_language("json"));

      SpyInput input("[1234, 5, 6, 4, 5]", 3);
      tree = ts_parser_parse(parser, nullptr, input.input());
      assert_root_node("(value (array (number) (number) (number) (number) (number)))");

      input.clear();
      TSInputEdit edit = input.replace(1, 4, "null");
      ts_tree_edit(tree, &edit);

      ts_parser_set_operation_limit(parser, 1);
      TSTree *new_tree = ts_parser_parse(parser, tree, input.input());
      AssertThat(new_tree, Equals<TSTree *>(nullptr));

      ts_tree_delete(tree);
      ts_parser_set_operation_limit(parser, SIZE_MAX);
      tree = ts_parser_parse(parser, nullptr, input.input());
      assert_root_node("(value (array (null) (number) (number) (number) (number)))");

      AssertThat(input.strings_read(), Equals(vector<string>({
        "[null,",
      })));
    });

    it("does not leak the old tree if parsing halts and never finishes", [&]() {
      ts_parser_set_language(parser, load_real_language("json"));

      SpyInput input("[1234, 5, 6, 4, 5]", 3);
      tree = ts_parser_parse(parser, nullptr, input.input());
      assert_root_node("(value (array (number) (number) (number) (number) (number)))");

      input.clear();
      TSInputEdit edit = input.replace(1, 4, "null");
      ts_tree_edit(tree, &edit);

      ts_parser_set_operation_limit(parser, 1);
      TSTree *new_tree = ts_parser_parse(parser, tree, input.input());
      AssertThat(new_tree, Equals<TSTree *>(nullptr));
    });
  });

  describe("reset()", [&]() {
    it("causes the parser to parse from scratch on the next call to parse, instead of resuming", [&]() {
      ts_parser_set_language(parser, load_real_language("json"));

      ts_parser_set_operation_limit(parser, 3);
      tree = ts_parser_parse_string(parser, nullptr, "[1234, 5, 6, 4, 5]", 18);
      AssertThat(tree, Equals<TSTree *>(nullptr));

      // Without calling reset, the parser continues from where it left off, so
      // it does not see the changes to the beginning of the source code.
      ts_parser_set_operation_limit(parser, SIZE_MAX);
      tree = ts_parser_parse_string(parser, nullptr, "[null, 5, 6, 4, 5]", 18);
      assert_root_node("(value (array (number) (number) (number) (number) (number)))");
      ts_tree_delete(tree);

      ts_parser_set_operation_limit(parser, 3);
      tree = ts_parser_parse_string(parser, nullptr, "[1234, 5, 6, 4, 5]", 18);
      AssertThat(tree, Equals<TSTree *>(nullptr));

      // By calling reset, we force the parser to start over from scratch so
      // that it sees the changes to the beginning of the source code.
      ts_parser_set_operation_limit(parser, SIZE_MAX);
      ts_parser_reset(parser);
      tree = ts_parser_parse_string(parser, nullptr, "[null, 5, 6, 4, 5]", 18);
      assert_root_node("(value (array (null) (number) (number) (number) (number)))");
    });
  });
});

END_TEST
