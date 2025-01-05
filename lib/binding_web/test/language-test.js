const {assert} = require('chai');
let JavaScript;

describe('Language', () => {
  before(async () => ({JavaScript, Rust} = await require('./helper')));

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

  describe('Supertypes', () => {
    it('gets the supertypes and subtypes of a parser', () => {
      const supertypes = Rust.supertypes;
      const names = supertypes.map((id) => Rust.nodeTypeForId(id));
      assert.deepStrictEqual(
        names,
        ['_expression', '_literal', '_literal_pattern', '_pattern', '_type'],
      );

      for (const id of supertypes) {
        const name = Rust.nodeTypeForId(id);
        const subtypes = Rust.subtypes(id);
        let subtypeNames = subtypes.map((id) => Rust.nodeTypeForId(id));
        subtypeNames = [...new Set(subtypeNames)].sort(); // Remove duplicates & sort
        switch (name) {
          case '_literal':
            assert.deepStrictEqual(subtypeNames, [
              'boolean_literal',
              'char_literal',
              'float_literal',
              'integer_literal',
              'raw_string_literal',
              'string_literal',
            ]);
            break;
          case '_pattern':
            assert.deepStrictEqual(subtypeNames, [
              '_',
              '_literal_pattern',
              'captured_pattern',
              'const_block',
              'identifier',
              'macro_invocation',
              'mut_pattern',
              'or_pattern',
              'range_pattern',
              'ref_pattern',
              'reference_pattern',
              'remaining_field_pattern',
              'scoped_identifier',
              'slice_pattern',
              'struct_pattern',
              'tuple_pattern',
              'tuple_struct_pattern',
            ]);
            break;
          case '_type':
            assert.deepStrictEqual(subtypeNames, [
              'abstract_type',
              'array_type',
              'bounded_type',
              'dynamic_type',
              'function_type',
              'generic_type',
              'macro_invocation',
              'metavariable',
              'never_type',
              'pointer_type',
              'primitive_type',
              'reference_type',
              'removed_trait_bound',
              'scoped_type_identifier',
              'tuple_type',
              'type_identifier',
              'unit_type',
            ]);
            break;
          default:
            break;
        }
      }
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
    state = cursor.currentNode.nextParseState;
    lookahead = JavaScript.lookaheadIterator(state);
    assert.exists(lookahead);
  });

  after(() => {
    lookahead.delete();
  });

  const expected = ['(', 'identifier', '*', 'formal_parameters', 'html_comment', 'comment'];
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
