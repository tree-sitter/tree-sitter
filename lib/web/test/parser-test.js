const assert = require('assert');
const Parser = require('../../../target/release/tree-sitter.js');
let JavaScript, Python;

before(async () => {
  await Parser.init();
  JavaScript = await Parser.Language.load('../../target/scratch/tree-sitter-javascript.wasm');
  Python = await Parser.Language.load('../../target/scratch/tree-sitter-python.wasm');
});

describe("Parser", () => {
  let parser;

  beforeEach(() => {
    parser = new Parser();
  });

  afterEach(() => {
    parser.delete();
  });

  it("parses strings", () => {
    const tree = parser
      .setLanguage(JavaScript)
      .parse("a('hi')\n");
    assert.equal(
      tree.rootNode.toString(),
      "(program (expression_statement (call_expression (identifier) (arguments (string)))))"
    );
  });
});
