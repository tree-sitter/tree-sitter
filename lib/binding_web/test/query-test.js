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
      JavaScript.query("(a)")
    }, "Bad node name 'a'");
    assert.throws(() => {
      JavaScript.query("(function_declaration non_existent:(identifier))")
    }, "Bad field name 'non_existent'");
  });

  it('matches simple queries',  () => {
    tree = parser.parse("function one() { two(); function three() {} }");
    query = JavaScript.query(`
      (function_declaration name:(identifier) @fn-def)
      (call_expression function:(identifier) @fn-ref)
    `);
    const matches = query.exec(tree.rootNode);
    assert.deepEqual(
      formatMatches(matches),
      [
        {pattern: 0, captures: [{name: 'fn-def', text: 'one'}]},
        {pattern: 1, captures: [{name: 'fn-ref', text: 'two'}]},
        {pattern: 0, captures: [{name: 'fn-def', text: 'three'}]},
      ]
    );
  });

  it('matches queries in specified ranges',  () => {
    tree = parser.parse("[a, b,\nc, d,\ne, f,\ng, h]");
    query = JavaScript.query('(identifier) @element');
    const matches = query.exec(
      tree.rootNode,
      {row: 1, column: 1},
      {row: 3, column: 1}
    );
    assert.deepEqual(
      formatMatches(matches),
      [
        {pattern: 0, captures: [{name: 'element', text: 'd'}]},
        {pattern: 0, captures: [{name: 'element', text: 'e'}]},
        {pattern: 0, captures: [{name: 'element', text: 'f'}]},
        {pattern: 0, captures: [{name: 'element', text: 'g'}]},
      ]
    );
  });
});

function formatMatches(matches) {
  return matches.map(({pattern, captures}) => ({
    pattern,
    captures: captures.map(({name, node}) => ({
      name,
      text: node.text
    }))
  }))
}
