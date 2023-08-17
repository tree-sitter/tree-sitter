const {assert} = require('chai');
let Parser, JavaScript;

describe("Node", () => {
  let parser, tree;

  before(async () =>
    ({Parser, JavaScript} = await require('./helper'))
  );

  beforeEach(() => {
    tree = null;
    parser = new Parser().setLanguage(JavaScript);
  });

  afterEach(() => {
    parser.delete();
    tree.delete();
  });

  describe(".children", () => {
    it("returns an array of child nodes", () => {
      tree = parser.parse("x10 + 1000");
      assert.equal(1, tree.rootNode.children.length);
      const sumNode = tree.rootNode.firstChild.firstChild;
      assert.deepEqual(
        sumNode.children.map(child => child.type),
        ["identifier", "+", "number"]
      );
    });
  });

  describe(".namedChildren", () => {
    it("returns an array of named child nodes", () => {
      tree = parser.parse("x10 + 1000");
      const sumNode = tree.rootNode.firstChild.firstChild;
      assert.equal(1, tree.rootNode.namedChildren.length);
      assert.deepEqual(
        ["identifier", "number"],
        sumNode.namedChildren.map(child => child.type)
      );
    });
  });

  describe(".startIndex and .endIndex", () => {
    it("returns the character index where the node starts/ends in the text", () => {
      tree = parser.parse("a👍👎1 / b👎c👎");
      const quotientNode = tree.rootNode.firstChild.firstChild;

      assert.equal(0, quotientNode.startIndex);
      assert.equal(15, quotientNode.endIndex);
      assert.deepEqual(
        [0, 7, 9],
        quotientNode.children.map(child => child.startIndex)
      );
      assert.deepEqual(
        [6, 8, 15],
        quotientNode.children.map(child => child.endIndex)
      );
    });
  });

  describe(".startPosition and .endPosition", () => {
    it("returns the row and column where the node starts/ends in the text", () => {
      tree = parser.parse("x10 + 1000");
      const sumNode = tree.rootNode.firstChild.firstChild;
      assert.equal("binary_expression", sumNode.type);

      assert.deepEqual({ row: 0, column: 0 }, sumNode.startPosition);
      assert.deepEqual({ row: 0, column: 10 }, sumNode.endPosition);
      assert.deepEqual(
        [{ row: 0, column: 0 }, { row: 0, column: 4 }, { row: 0, column: 6 }],
        sumNode.children.map(child => child.startPosition)
      );
      assert.deepEqual(
        [{ row: 0, column: 3 }, { row: 0, column: 5 }, { row: 0, column: 10 }],
        sumNode.children.map(child => child.endPosition)
      );
    });

    it("handles characters that occupy two UTF16 code units", () => {
      tree = parser.parse("a👍👎1 /\n b👎c👎");
      const sumNode = tree.rootNode.firstChild.firstChild;
      assert.deepEqual(
        [
          [{ row: 0, column: 0 }, { row: 0, column: 6 }],
          [{ row: 0, column: 7 }, { row: 0, column: 8 }],
          [{ row: 1, column: 1 }, { row: 1, column: 7 }]
        ],
        sumNode.children.map(child => [child.startPosition, child.endPosition])
      );
    });
  });

  describe(".parent", () => {
    it("returns the node's parent", () => {
      tree = parser.parse("x10 + 1000");
      const sumNode = tree.rootNode.firstChild;
      const variableNode = sumNode.firstChild;
      assert.notEqual(sumNode.id, variableNode.id);
      assert.equal(sumNode.id, variableNode.parent.id);
      assert.equal(tree.rootNode.id, sumNode.parent.id);
    });
  });

  describe('.child(), .firstChild, .lastChild', () => {
    it('returns null when the node has no children', () => {
      tree = parser.parse("x10 + 1000");
      const sumNode = tree.rootNode.firstChild.firstChild;
      const variableNode = sumNode.firstChild;
      assert.equal(variableNode.firstChild, null);
      assert.equal(variableNode.lastChild, null);
      assert.equal(variableNode.firstNamedChild, null);
      assert.equal(variableNode.lastNamedChild, null);
      assert.equal(variableNode.child(1), null);
    })
  });

  describe(".nextSibling and .previousSibling", () => {
    it("returns the node's next and previous sibling", () => {
      tree = parser.parse("x10 + 1000");
      const sumNode = tree.rootNode.firstChild.firstChild;
      assert.equal(sumNode.children[1].id, sumNode.children[0].nextSibling.id);
      assert.equal(sumNode.children[2].id, sumNode.children[1].nextSibling.id);
      assert.equal(
        sumNode.children[0].id,
        sumNode.children[1].previousSibling.id
      );
      assert.equal(
        sumNode.children[1].id,
        sumNode.children[2].previousSibling.id
      );
    });
  });

  describe(".nextNamedSibling and .previousNamedSibling", () => {
    it("returns the node's next and previous named sibling", () => {
      tree = parser.parse("x10 + 1000");
      const sumNode = tree.rootNode.firstChild.firstChild;
      assert.equal(
        sumNode.namedChildren[1].id,
        sumNode.namedChildren[0].nextNamedSibling.id
      );
      assert.equal(
        sumNode.namedChildren[0].id,
        sumNode.namedChildren[1].previousNamedSibling.id
      );
    });
  });

  describe(".descendantForIndex(min, max)", () => {
    it("returns the smallest node that spans the given range", () => {
      tree = parser.parse("x10 + 1000");
      const sumNode = tree.rootNode.firstChild.firstChild;
      assert.equal("identifier", sumNode.descendantForIndex(1, 2).type);
      assert.equal("+", sumNode.descendantForIndex(4, 4).type);

      assert.throws(() => {
        sumNode.descendantForIndex(1, {});
      }, "Arguments must be numbers");

      assert.throws(() => {
        sumNode.descendantForIndex();
      }, "Arguments must be numbers");
    });
  });

  describe(".namedDescendantForIndex", () => {
    it("returns the smallest node that spans the given range", () => {
      tree = parser.parse("x10 + 1000");
      const sumNode = tree.rootNode.firstChild;
      assert.equal("identifier", sumNode.descendantForIndex(1, 2).type);
      assert.equal("+", sumNode.descendantForIndex(4, 4).type);
    });
  });

  describe(".descendantForPosition(min, max)", () => {
    it("returns the smallest node that spans the given range", () => {
      tree = parser.parse("x10 + 1000");
      const sumNode = tree.rootNode.firstChild;

      assert.equal(
        "identifier",
        sumNode.descendantForPosition(
          { row: 0, column: 1 },
          { row: 0, column: 2 }
        ).type
      );

      assert.equal(
        "+",
        sumNode.descendantForPosition({ row: 0, column: 4 }).type
      );

      assert.throws(() => {
        sumNode.descendantForPosition(1, {});
      }, "Arguments must be {row, column} objects");

      assert.throws(() => {
        sumNode.descendantForPosition();
      }, "Arguments must be {row, column} objects");
    });
  });

  describe(".namedDescendantForPosition(min, max)", () => {
    it("returns the smallest named node that spans the given range", () => {
      tree = parser.parse("x10 + 1000");
      const sumNode = tree.rootNode.firstChild;

      assert.equal(
        sumNode.namedDescendantForPosition(
          { row: 0, column: 1 },
          { row: 0, column: 2 }
        ).type,
        "identifier",
      );

      assert.equal(
        sumNode.namedDescendantForPosition({ row: 0, column: 4 }).type,
        'binary_expression'
      );
    });
  });

  describe(".hasError()", () => {
    it("returns true if the node contains an error", () => {
      tree = parser.parse("1 + 2 * * 3");
      const node = tree.rootNode;
      assert.equal(
        node.toString(),
        '(program (expression_statement (binary_expression (number) (binary_expression (number) (ERROR) (number)))))'
      );

      const sum = node.firstChild.firstChild;
      assert(sum.hasError());
      assert(!sum.children[0].hasError());
      assert(!sum.children[1].hasError());
      assert(sum.children[2].hasError());
    });
  });

  describe(".isMissing()", () => {
    it("returns true if the node is missing from the source and was inserted via error recovery", () => {
      tree = parser.parse("(2 ||)");
      const node = tree.rootNode;
      assert.equal(
        node.toString(),
        "(program (expression_statement (parenthesized_expression (binary_expression (number) (MISSING identifier)))))"
      );

      const sum = node.firstChild.firstChild.firstNamedChild;
      assert.equal(sum.type, 'binary_expression')
      assert(sum.hasError());
      assert(!sum.children[0].isMissing());
      assert(!sum.children[1].isMissing());
      assert(sum.children[2].isMissing());
    });
  });

  describe(".text", () => {
    const text = "α0 / b👎c👎";

    Object.entries({
      '.parse(String)': text,
      '.parse(Function)': offset => text.substr(offset, 4)
    }).forEach(([method, parse]) =>
      it(`returns the text of a node generated by ${method}`, async () => {
        const [numeratorSrc, denominatorSrc] = text.split(/\s*\/\s+/)
        tree = await parser.parse(text)
        const quotientNode = tree.rootNode.firstChild.firstChild;
        const [numerator, slash, denominator] = quotientNode.children;

        assert.equal(text, tree.rootNode.text,          'root node text');
        assert.equal(denominatorSrc, denominator.text, 'denominator text');
        assert.equal(text, quotientNode.text,           'quotient text');
        assert.equal(numeratorSrc, numerator.text,     'numerator text');
        assert.equal('/', slash.text,                  '"/" text');
      })
    );
  });

  describe.skip('.descendantsOfType(type, min, max)', () => {
    it('finds all of the descendants of the given type in the given range', () => {
      tree = parser.parse("a + 1 * b * 2 + c + 3");
      const outerSum = tree.rootNode.firstChild.firstChild;
      let descendants = outerSum.descendantsOfType('number', {row: 0, column: 2}, {row: 0, column: 15})
      assert.deepEqual(
        descendants.map(node => node.startIndex),
        [4, 12]
      );

      descendants = outerSum.descendantsOfType('identifier', {row: 0, column: 2}, {row: 0, column: 15})
      assert.deepEqual(
        descendants.map(node => node.startIndex),
        [8]
      );

      descendants = outerSum.descendantsOfType('identifier', {row: 0, column: 0}, {row: 0, column: 30})
      assert.deepEqual(
        descendants.map(node => node.startIndex),
        [0, 8, 16]
      );

      descendants = outerSum.descendantsOfType('number', {row: 0, column: 0}, {row: 0, column: 30})
      assert.deepEqual(
        descendants.map(node => node.startIndex),
        [4, 12, 20]
      );

      descendants = outerSum.descendantsOfType(
        ['identifier', 'number'],
        {row: 0, column: 0},
        {row: 0, column: 30}
      )
      assert.deepEqual(
        descendants.map(node => node.startIndex),
        [0, 4, 8, 12, 16, 20]
      );

      descendants = outerSum.descendantsOfType('number')
      assert.deepEqual(
        descendants.map(node => node.startIndex),
        [4, 12, 20]
      );

      descendants = outerSum.firstChild.descendantsOfType('number', {row: 0, column: 0}, {row: 0, column: 30})
      assert.deepEqual(
        descendants.map(node => node.startIndex),
        [4, 12]
      );
    })
  });

  describe.skip('.closest(type)', () => {
    it('returns the closest ancestor of the given type', () => {
      tree = parser.parse("a(b + -d.e)");
      const property = tree.rootNode.descendantForIndex("a(b + -d.".length);
      assert.equal(property.type, 'property_identifier');

      const unary = property.closest('unary_expression')
      assert.equal(unary.type, 'unary_expression')
      assert.equal(unary.startIndex, 'a(b + '.length)
      assert.equal(unary.endIndex, 'a(b + -d.e'.length)

      const sum = property.closest(['binary_expression', 'call_expression'])
      assert.equal(sum.type, 'binary_expression')
      assert.equal(sum.startIndex, 2)
      assert.equal(sum.endIndex, 'a(b + -d.e'.length)
    });

    it('throws an exception when an invalid argument is given', () => {
      tree = parser.parse("a + 1 * b * 2 + c + 3");
      const number = tree.rootNode.descendantForIndex(4)

      assert.throws(() => number.closest({a: 1}), /Argument must be a string or array of strings/)
    });
  });
});
