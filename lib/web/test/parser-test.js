const {assert} = require('chai');
let Parser, JavaScript, Python;

describe("Parser", () => {
  let parser;

  before(async () =>
    ({Parser, JavaScript, Python} = await require('./helper'))
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

    it("can use languages with external scanners written in C++", () => {
      parser.setLanguage(Python);
      tree = parser.parse("def foo():\n  bar()");
      assert.equal(
        tree.rootNode.toString(),
        '(module (function_definition (identifier) (parameters) (expression_statement (call (identifier) (argument_list)))))'
      );
    });

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
        '(program (expression_statement (call_expression (identifier) (arguments))) (expression_statement (identifier)))'
      );
    })
  });});
