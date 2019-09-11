const {assert} = require('chai');
let Parser, JavaScript;

describe("Query", () => {
  let parser, tree, query;

  before(async () =>
    ({Parser, JavaScript} = await require('./helper'))
  );

  beforeEach(() => {
    parser = new Parser().setLanguage(JavaScript);
  });

  afterEach(() => {
    parser.delete();
    if (tree) tree.delete();
    if (query) query.delete();
  });

  it('throws an error on invalid syntax', () => {
    assert.throws(() => {
      JavaScript.query("(function_declaration wat)")
    }, "Bad syntax at offset 22: \'wat)\'...");
    assert.throws(() => {
      JavaScript.query("(non_existent)")
    }, "Bad node name 'non_existent'");
    assert.throws(() => {
      JavaScript.query("(function_declaration non_existent:(identifier))")
    }, "Bad field name 'non_existent'");
  });

  it('matches simple queries',  () => {
    tree = parser.parse("function one() { two(); function three() {} }");
    const query = JavaScript.query(`
      (function_declaration name:(identifier) @the-name)
    `);
    const matches = query.exec(tree.rootNode);
    assert.deepEqual(
      matches.map(({pattern, captures}) => ({
        pattern,
        captures: captures.map(({name, node}) => ({name, text: node.text}))
      })),
      [
        {pattern: 0, captures: [{name: 'the-name', text: 'one'}]},
        // {pattern: 0, captures: [{name: 'the-function', text: 'two'}]},
        {pattern: 0, captures: [{name: 'the-name', text: 'three'}]},
      ]
    );
  });
});
