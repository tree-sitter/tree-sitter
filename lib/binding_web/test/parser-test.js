const {assert} = require('chai');
let Parser, JavaScript, languageURL;

describe("Parser", () => {
  let parser;

  before(async () =>
    ({Parser, JavaScript, languageURL} = await require('./helper'))
  );

  beforeEach(() => {
    parser = new Parser();
  });

  afterEach(() => {
    parser.delete()
  });

  describe(".setLanguage", () => {
    it("allows setting the language to null", () => {
      assert.equal(parser.getLanguage(), null);
      parser.setLanguage(JavaScript);
      assert.equal(parser.getLanguage(), JavaScript);
      parser.setLanguage(null);
      assert.equal(parser.getLanguage(), null);
    });

    it("throws an exception when the given object is not a tree-sitter language", () => {
      assert.throws(() => parser.setLanguage({}), /Argument must be a Language/);
      assert.throws(() => parser.setLanguage(1), /Argument must be a Language/);
    });
  });

  describe(".setLogger", () => {
    beforeEach(() => {
      parser.setLanguage(JavaScript)
    });

    it("calls the given callback for each parse event", () => {
      const debugMessages = [];
      parser.setLogger((message) => debugMessages.push(message));
      parser.parse("a + b + c");
      assert.includeMembers(debugMessages, [
        "skip character:' '",
        "consume character:'b'",
        "reduce sym:program, child_count:1",
        "accept"
      ]);
    });

    it("allows the callback to be retrieved later", () => {
      const callback = () => {}
      parser.setLogger(callback);
      assert.equal(parser.getLogger(), callback);
      parser.setLogger(false);
      assert.equal(parser.getLogger(), null);
    });

    it("disables debugging when given a falsy value", () => {
      const debugMessages = [];
      parser.setLogger((message) => debugMessages.push(message));
      parser.setLogger(false);
      parser.parse("a + b * c");
      assert.equal(debugMessages.length, 0);
    });

    it("throws an error when given a truthy value that isn't a function ", () => {
      assert.throws(
        () => parser.setLogger("5"),
        "Logger callback must be a function"
      );
    });

    it("rethrows errors thrown by the logging callback", () => {
      const error = new Error("The error message");
      parser.setLogger((msg, params) => { throw error; });
      assert.throws(
        () => parser.parse("ok;"),
        "The error message"
      );
    });
  });

  describe(".parse", () => {
    let tree;

    beforeEach(() => {
      tree = null;
      parser.setLanguage(JavaScript)
    });

    afterEach(() => {
      if (tree) tree.delete();
    });

    it("reads from the given input", () => {
      const parts = ["first", "_", "second", "_", "third"];
      tree = parser.parse(() => parts.shift());
      assert.equal(tree.rootNode.toString(), "(program (expression_statement (identifier)))");
    });

    it("stops reading when the input callback return something that's not a string", () => {
      const parts = ["abc", "def", "ghi", {}, {}, {}, "second-word", " "];
      tree = parser.parse(() => parts.shift());
      assert.equal(
        tree.rootNode.toString(),
        "(program (expression_statement (identifier)))"
      );
      assert.equal(tree.rootNode.endIndex, 9);
      assert.equal(parts.length, 2);
    });

    it("throws an exception when the given input is not a function", () => {
      assert.throws(() => parser.parse(null), "Argument must be a string or a function");
      assert.throws(() => parser.parse(5), "Argument must be a string or a function");
      assert.throws(() => parser.parse({}), "Argument must be a string or a function");
    });

    it("handles long input strings", () => {
      const repeatCount = 10000;
      const inputString = "[" + "0,".repeat(repeatCount) + "]";

      tree = parser.parse(inputString);
      assert.equal(tree.rootNode.type, "program");
      assert.equal(tree.rootNode.firstChild.firstChild.namedChildCount, repeatCount);
    }).timeout(5000);

    it("can use the bash parser", async () => {
      parser.setLanguage(await Parser.Language.load(languageURL('bash')));
      tree = parser.parse("FOO=bar echo <<EOF 2> err.txt > hello.txt \nhello\nEOF");
      assert.equal(
        tree.rootNode.toString(),
        '(program (redirected_statement ' +
          'body: (command ' +
            '(variable_assignment ' +
              'name: (variable_name) ' +
              'value: (word)) ' +
            'name: (command_name (word))) ' +
          'redirect: (heredoc_redirect (heredoc_start)) ' +
          'redirect: (file_redirect descriptor: (file_descriptor) destination: (word)) ' +
          'redirect: (file_redirect destination: (word))) ' +
          '(heredoc_body))'
      );
    }).timeout(5000);

    it("can use the c++ parser", async () => {
      parser.setLanguage(await Parser.Language.load(languageURL('cpp')));
      tree = parser.parse("const char *s = R\"EOF(HELLO WORLD)EOF\";");
      assert.equal(
        tree.rootNode.toString(),
        '(translation_unit (declaration ' +
          '(type_qualifier) ' +
          'type: (primitive_type) ' +
          'declarator: (init_declarator ' +
            'declarator: (pointer_declarator declarator: (identifier)) ' +
            'value: (raw_string_literal))))'
      );
    }).timeout(5000);

    it("can use the HTML parser", async () => {
      parser.setLanguage(await Parser.Language.load(languageURL('html')));
      tree = parser.parse("<div><span><custom></custom></span></div>");
      assert.equal(
        tree.rootNode.toString(),
        '(fragment (element (start_tag (tag_name)) (element (start_tag (tag_name)) (element (start_tag (tag_name)) (end_tag (tag_name))) (end_tag (tag_name))) (end_tag (tag_name))))'
      );
    }).timeout(5000);

    it("can use the python parser", async () => {
      parser.setLanguage(await Parser.Language.load(languageURL('python')));
      tree = parser.parse("class A:\n  def b():\n    c()");
      assert.equal(
        tree.rootNode.toString(),
        '(module (class_definition ' +
          'name: (identifier) ' +
          'body: (block ' +
            '(function_definition ' +
              'name: (identifier) ' +
              'parameters: (parameters) ' +
              'body: (block (expression_statement (call ' +
                'function: (identifier) ' +
                'arguments: (argument_list))))))))'
      );
    }).timeout(5000);

    it("can use the rust parser", async () => {
      parser.setLanguage(await Parser.Language.load(languageURL('rust')));
      tree = parser.parse("const x: &'static str = r###\"hello\"###;");
      assert.equal(
        tree.rootNode.toString(),
        '(source_file (const_item ' +
          'name: (identifier) ' +
          'type: (reference_type (lifetime (identifier)) type: (primitive_type)) ' +
          'value: (raw_string_literal)))'
      );
    }).timeout(5000);

    it("can use the typescript parser", async () => {
      parser.setLanguage(await Parser.Language.load(languageURL('typescript')));
      tree = parser.parse("a()\nb()\n[c]");
      assert.equal(
        tree.rootNode.toString(),
        '(program ' +
          '(expression_statement (call_expression function: (identifier) arguments: (arguments))) ' +
          '(expression_statement (subscript_expression ' +
            'object: (call_expression ' +
              'function: (identifier) ' +
              'arguments: (arguments)) ' +
            'index: (identifier))))'
      );
    }).timeout(5000);

    it("can use the tsx parser", async () => {
      parser.setLanguage(await Parser.Language.load(languageURL('tsx')));
      tree = parser.parse("a()\nb()\n[c]");
      assert.equal(
        tree.rootNode.toString(),
        '(program ' +
          '(expression_statement (call_expression function: (identifier) arguments: (arguments))) ' +
          '(expression_statement (subscript_expression ' +
            'object: (call_expression ' +
              'function: (identifier) ' +
              'arguments: (arguments)) ' +
            'index: (identifier))))'
      );
    }).timeout(5000);

    it('parses only the text within the `includedRanges` if they are specified', () => {
      const sourceCode = "<% foo() %> <% bar %>";

      const start1 = sourceCode.indexOf('foo');
      const end1 = start1 + 5
      const start2 = sourceCode.indexOf('bar');
      const end2 = start2 + 3

      const tree = parser.parse(sourceCode, null, {
        includedRanges: [
          {
            startIndex: start1,
            endIndex: end1,
            startPosition: {row: 0, column: start1},
            endPosition: {row: 0, column: end1}
          },
          {
            startIndex: start2,
            endIndex: end2,
            startPosition: {row: 0, column: start2},
            endPosition: {row: 0, column: end2}
          },
        ]
      });

      assert.equal(
        tree.rootNode.toString(),
        '(program (expression_statement (call_expression function: (identifier) arguments: (arguments))) (expression_statement (identifier)))'
      );
    })
  });});
