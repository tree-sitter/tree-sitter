const {assert} = require('chai');
let JavaScript;

describe('Language', () => {
  before(async () => ({JavaScript} = await require('./helper')));

  describe('.fieldIdForName, .fieldNameForId', () => {
    it('converts between the string and integer representations of fields', () => {
      const nameId = JavaScript.fieldIdForName('name');
      const bodyId = JavaScript.fieldIdForName('body');

      assert.isBelow(nameId, JavaScript.fieldCount);
      assert.isBelow(bodyId, JavaScript.fieldCount);
      assert.equal('name', JavaScript.fieldNameForId(nameId));
      assert.equal('body', JavaScript.fieldNameForId(bodyId));
    });

    it('handles invalid inputs', () => {
      assert.equal(null, JavaScript.fieldIdForName('namezzz'));
      assert.equal(null, JavaScript.fieldNameForId(-1));
      assert.equal(null, JavaScript.fieldNameForId(10000));
    });
  });

  describe('.idForNodeType, .nodeTypeForId, .nodeTypeIsNamed', () => {
    it('converts between the string and integer representations of a node type', () => {
      const exportStatementId = JavaScript.idForNodeType('export_statement', true);
      const starId = JavaScript.idForNodeType('*', false);

      assert.isBelow(exportStatementId, JavaScript.nodeTypeCount);
      assert.isBelow(starId, JavaScript.nodeTypeCount);
      assert.equal(true, JavaScript.nodeTypeIsNamed(exportStatementId));
      assert.equal('export_statement', JavaScript.nodeTypeForId(exportStatementId));
      assert.equal(false, JavaScript.nodeTypeIsNamed(starId));
      assert.equal('*', JavaScript.nodeTypeForId(starId));
    });

    it('handles invalid inputs', () => {
      assert.equal(null, JavaScript.nodeTypeForId(-1));
      assert.equal(null, JavaScript.nodeTypeForId(10000));
      assert.equal(null, JavaScript.idForNodeType('export_statement', false));
    });
  });
});

describe('Lookahead iterator', () => {
  let lookahead;
  let state;
  before(async () => {
    let Parser;
    ({JavaScript, Parser} = await require('./helper'));
    const parser = new Parser().setLanguage(JavaScript);
    const tree = parser.parse('function fn() {}');
    parser.delete();
    const cursor = tree.walk();
    assert(cursor.gotoFirstChild());
    assert(cursor.gotoFirstChild());
    state = cursor.currentNode().nextParseState;
    lookahead = JavaScript.lookaheadIterator(state);
    assert.exists(lookahead);
  });

  after(() => {
    lookahead.delete();
  });

  const expected = ['identifier', 'comment', 'html_comment', '(', '*', 'formal_parameters', 'ERROR'];
  it('should iterate over valid symbols in the state', () => {
    const symbols = Array.from(lookahead);
    assert.includeMembers(symbols, expected);
    assert.lengthOf(symbols, expected.length);
  });

  it('should reset to the initial state', () => {
    assert(lookahead.resetState(state));
    const symbols = Array.from(lookahead);
    assert.includeMembers(symbols, expected);
    assert.lengthOf(symbols, expected.length);
  });

  it('should reset', () => {
    assert(lookahead.reset(JavaScript, state));
    const symbols = Array.from(lookahead);
    assert.includeMembers(symbols, expected);
    assert.lengthOf(symbols, expected.length);
  });
});
