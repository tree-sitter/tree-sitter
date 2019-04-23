const {assert} = require('chai');
let Parser, JavaScript;

describe("Tree", () => {
  let parser, tree;

  before(async () =>
    ({Parser, JavaScript} = await require('./helper'))
  );

  beforeEach(() => {
    parser = new Parser().setLanguage(JavaScript);
  });

  afterEach(() => {
    parser.delete();
    tree.delete();
  });

  describe('.edit', () => {
    let input, edit

    it('updates the positions of nodes', () => {
      input = 'abc + cde';
      tree = parser.parse(input);
      assert.equal(
        tree.rootNode.toString(),
        "(program (expression_statement (binary_expression (identifier) (identifier))))"
      );

      let sumNode = tree.rootNode.firstChild.firstChild;
      let variableNode1 = sumNode.firstChild;
      let variableNode2 = sumNode.lastChild;
      assert.equal(variableNode1.startIndex, 0);
      assert.equal(variableNode1.endIndex, 3);
      assert.equal(variableNode2.startIndex, 6);
      assert.equal(variableNode2.endIndex, 9);

      ([input, edit] = spliceInput(input, input.indexOf('bc'), 0, ' * '));
      assert.equal(input, 'a * bc + cde');
      tree.edit(edit);

      sumNode = tree.rootNode.firstChild.firstChild;
      variableNode1 = sumNode.firstChild;
      variableNode2 = sumNode.lastChild;
      assert.equal(variableNode1.startIndex, 0);
      assert.equal(variableNode1.endIndex, 6);
      assert.equal(variableNode2.startIndex, 9);
      assert.equal(variableNode2.endIndex, 12);

      tree = parser.parse(input, tree);
      assert.equal(
        tree.rootNode.toString(),
        "(program (expression_statement (binary_expression (binary_expression (identifier) (identifier)) (identifier))))"
      );
    });

    it("handles non-ascii characters", () => {
      input = 'αβδ + cde';

      tree = parser.parse(input);
      assert.equal(
        tree.rootNode.toString(),
        "(program (expression_statement (binary_expression (identifier) (identifier))))"
      );

      let variableNode = tree.rootNode.firstChild.firstChild.lastChild;

      ([input, edit] = spliceInput(input, input.indexOf('δ'), 0, '👍 * '));
      assert.equal(input, 'αβ👍 * δ + cde');
      tree.edit(edit);

      variableNode = tree.rootNode.firstChild.firstChild.lastChild;
      assert.equal(variableNode.startIndex, input.indexOf('cde'));

      tree = parser.parse(input, tree);
      assert.equal(
        tree.rootNode.toString(),
        "(program (expression_statement (binary_expression (binary_expression (identifier) (identifier)) (identifier))))"
      );
    });
  });

  describe(".walk()", () => {
    let cursor

    afterEach(() => {
      cursor.delete();
    })

    it('returns a cursor that can be used to walk the tree', () => {
      tree = parser.parse('a * b + c / d');
      cursor = tree.walk();

      assertCursorState(cursor, {
        nodeType: 'program',
        nodeIsNamed: true,
        startPosition: {row: 0, column: 0},
        endPosition: {row: 0, column: 13},
        startIndex: 0,
        endIndex: 13
      });

      assert(cursor.gotoFirstChild());
      assertCursorState(cursor, {
        nodeType: 'expression_statement',
        nodeIsNamed: true,
        startPosition: {row: 0, column: 0},
        endPosition: {row: 0, column: 13},
        startIndex: 0,
        endIndex: 13
      });

      assert(cursor.gotoFirstChild());
      assertCursorState(cursor, {
        nodeType: 'binary_expression',
        nodeIsNamed: true,
        startPosition: {row: 0, column: 0},
        endPosition: {row: 0, column: 13},
        startIndex: 0,
        endIndex: 13
      });

      assert(cursor.gotoFirstChild());
      assertCursorState(cursor, {
        nodeType: 'binary_expression',
        nodeIsNamed: true,
        startPosition: {row: 0, column: 0},
        endPosition: {row: 0, column: 5},
        startIndex: 0,
        endIndex: 5
      });

      assert(cursor.gotoFirstChild());
      assertCursorState(cursor, {
        nodeType: 'identifier',
        nodeIsNamed: true,
        startPosition: {row: 0, column: 0},
        endPosition: {row: 0, column: 1},
        startIndex: 0,
        endIndex: 1
      });

      assert(!cursor.gotoFirstChild())
      assert(cursor.gotoNextSibling());
      assertCursorState(cursor, {
        nodeType: '*',
        nodeIsNamed: false,
        startPosition: {row: 0, column: 2},
        endPosition: {row: 0, column: 3},
        startIndex: 2,
        endIndex: 3
      });

      assert(cursor.gotoNextSibling());
      assertCursorState(cursor, {
        nodeType: 'identifier',
        nodeIsNamed: true,
        startPosition: {row: 0, column: 4},
        endPosition: {row: 0, column: 5},
        startIndex: 4,
        endIndex: 5
      });

      assert(!cursor.gotoNextSibling());
      assert(cursor.gotoParent());
      assertCursorState(cursor, {
        nodeType: 'binary_expression',
        nodeIsNamed: true,
        startPosition: {row: 0, column: 0},
        endPosition: {row: 0, column: 5},
        startIndex: 0,
        endIndex: 5
      });

      assert(cursor.gotoNextSibling());
      assertCursorState(cursor, {
        nodeType: '+',
        nodeIsNamed: false,
        startPosition: {row: 0, column: 6},
        endPosition: {row: 0, column: 7},
        startIndex: 6,
        endIndex: 7
      });

      assert(cursor.gotoNextSibling());
      assertCursorState(cursor, {
        nodeType: 'binary_expression',
        nodeIsNamed: true,
        startPosition: {row: 0, column: 8},
        endPosition: {row: 0, column: 13},
        startIndex: 8,
        endIndex: 13
      });

      // const childIndex = cursor.gotoFirstChildForIndex(12);
      // assertCursorState(cursor, {
      //   nodeType: 'identifier',
      //   nodeIsNamed: true,
      //   startPosition: {row: 0, column: 12},
      //   endPosition: {row: 0, column: 13},
      //   startIndex: 12,
      //   endIndex: 13
      // });
      // assert.equal(childIndex, 2);
      // assert(!cursor.gotoNextSibling());
      // assert(cursor.gotoParent());

      assert(cursor.gotoParent());
      assert.equal(cursor.nodeType, 'binary_expression')
      assert(cursor.gotoParent());
      assert.equal(cursor.nodeType, 'expression_statement')
      assert(cursor.gotoParent());
      assert.equal(cursor.nodeType, 'program')
      assert(!cursor.gotoParent());
    });

    it('returns a cursor that can be reset anywhere in the tree', () => {
      tree = parser.parse('a * b + c / d');
      cursor = tree.walk();
      const root = tree.rootNode.firstChild;

      cursor.reset(root.firstChild.firstChild);
      assertCursorState(cursor, {
        nodeType: 'binary_expression',
        nodeIsNamed: true,
        startPosition: {row: 0, column: 0},
        endPosition: {row: 0, column: 5},
        startIndex: 0,
        endIndex: 5
      });

      cursor.gotoFirstChild()
      assertCursorState(cursor, {
        nodeType: 'identifier',
        nodeIsNamed: true,
        startPosition: {row: 0, column: 0},
        endPosition: {row: 0, column: 1},
        startIndex: 0,
        endIndex: 1
      });

      assert(cursor.gotoParent());
      assert(!cursor.gotoParent());
    })
  });
});

function spliceInput(input, startIndex, lengthRemoved, newText) {
  const oldEndIndex = startIndex + lengthRemoved;
  const newEndIndex = startIndex + newText.length;
  const startPosition = getExtent(input.slice(0, startIndex));
  const oldEndPosition = getExtent(input.slice(0, oldEndIndex));
  input = input.slice(0, startIndex) + newText + input.slice(oldEndIndex);
  const newEndPosition = getExtent(input.slice(0, newEndIndex));
  return [
    input,
    {
      startIndex, startPosition,
      oldEndIndex, oldEndPosition,
      newEndIndex, newEndPosition
    }
  ];
}

function getExtent(text) {
  let row = 0
  let index;
  for (index = 0; index != -1; index = text.indexOf('\n', index)) {
    index++
    row++;
  }
  return {row, column: text.length - index};
}

function assertCursorState(cursor, params) {
  assert.equal(cursor.nodeType, params.nodeType);
  assert.equal(cursor.nodeIsNamed, params.nodeIsNamed);
  assert.deepEqual(cursor.startPosition, params.startPosition);
  assert.deepEqual(cursor.endPosition, params.endPosition);
  assert.deepEqual(cursor.startIndex, params.startIndex);
  assert.deepEqual(cursor.endIndex, params.endIndex);

  const node = cursor.currentNode()
  assert.equal(node.type, params.nodeType);
  assert.equal(node.isNamed(), params.nodeIsNamed);
  assert.deepEqual(node.startPosition, params.startPosition);
  assert.deepEqual(node.endPosition, params.endPosition);
  assert.deepEqual(node.startIndex, params.startIndex);
  assert.deepEqual(node.endIndex, params.endIndex);
}
