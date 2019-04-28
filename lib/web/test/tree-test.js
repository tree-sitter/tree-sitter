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
      parser.setLanguage(JavaScript)

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
