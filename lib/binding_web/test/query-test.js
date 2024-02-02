const { assert } = require("chai");
let Parser, JavaScript;

describe("Query", () => {
  let parser, tree, query;

  before(async () => ({ Parser, JavaScript } = await require("./helper")));

  beforeEach(() => {
    parser = new Parser().setLanguage(JavaScript);
  });

  afterEach(() => {
    parser.delete();
    if (tree) tree.delete();
    if (query) query.delete();
  });

  describe("construction", () => {
    it("throws an error on invalid patterns", () => {
      assert.throws(() => {
        JavaScript.query("(function_declaration wat)");
      }, "Bad syntax at offset 22: 'wat)'...");
      assert.throws(() => {
        JavaScript.query("(non_existent)");
      }, "Bad node name 'non_existent'");
      assert.throws(() => {
        JavaScript.query("(a)");
      }, "Bad node name 'a'");
      assert.throws(() => {
        JavaScript.query("(function_declaration non_existent:(identifier))");
      }, "Bad field name 'non_existent'");
      assert.throws(() => {
        JavaScript.query("(function_declaration name:(statement_block))");
      }, "Bad pattern structure at offset 22: 'name:(statement_block))'");
    });

    it("throws an error on invalid predicates", () => {
      assert.throws(() => {
        JavaScript.query("((identifier) @abc (#eq? @ab hi))");
      }, "Bad capture name @ab");
      assert.throws(() => {
        JavaScript.query("((identifier) @abc (#eq? @ab hi))");
      }, "Bad capture name @ab");
      assert.throws(() => {
        JavaScript.query("((identifier) @abc (#eq?))");
      }, "Wrong number of arguments to `#eq?` predicate. Expected 2, got 0");
      assert.throws(() => {
        JavaScript.query("((identifier) @a (eq? @a @a @a))");
      }, "Wrong number of arguments to `#eq?` predicate. Expected 2, got 3");
    });
  });

  describe(".matches", () => {
    it("returns all of the matches for the given query", () => {
      tree = parser.parse("function one() { two(); function three() {} }");
      query = JavaScript.query(`
        (function_declaration name: (identifier) @fn-def)
        (call_expression function: (identifier) @fn-ref)
      `);
      const matches = query.matches(tree.rootNode);
      assert.deepEqual(formatMatches(matches), [
        { pattern: 0, captures: [{ name: "fn-def", text: "one" }] },
        { pattern: 1, captures: [{ name: "fn-ref", text: "two" }] },
        { pattern: 0, captures: [{ name: "fn-def", text: "three" }] },
      ]);
    });

    it("can search in a specified ranges", () => {
      tree = parser.parse("[a, b,\nc, d,\ne, f,\ng, h]");
      query = JavaScript.query("(identifier) @element");
      const matches = query.matches(
        tree.rootNode,
        { row: 1, column: 1 },
        { row: 3, column: 1 }
      );
      assert.deepEqual(formatMatches(matches), [
        { pattern: 0, captures: [{ name: "element", text: "d" }] },
        { pattern: 0, captures: [{ name: "element", text: "e" }] },
        { pattern: 0, captures: [{ name: "element", text: "f" }] },
        { pattern: 0, captures: [{ name: "element", text: "g" }] },
      ]);
    });

    it("handles predicates that compare the text of capture to literal strings", () => {
      tree = parser.parse(`
        giraffe(1, 2, []);
        helment([false]);
        goat(false);
        gross(3, []);
        hiccup([]);
        gaff(5);
      `);

      // Find all calls to functions beginning with 'g', where one argument
      // is an array literal.
      query = JavaScript.query(`
        (call_expression
          function: (identifier) @name
          arguments: (arguments (array))
          (#match? @name "^g"))
      `);

      const matches = query.matches(tree.rootNode);
      assert.deepEqual(formatMatches(matches), [
        { pattern: 0, captures: [{ name: "name", text: "giraffe" }] },
        { pattern: 0, captures: [{ name: "name", text: "gross" }] },
      ]);
    });
  });

  describe(".captures", () => {
    it("returns all of the captures for the given query, in order", () => {
      tree = parser.parse(`
        a({
          bc: function de() {
            const fg = function hi() {}
          },
          jk: function lm() {
            const no = function pq() {}
          },
        });
      `);
      query = JavaScript.query(`
        (pair
          key: _ @method.def
          (function_expression
            name: (identifier) @method.alias))

        (variable_declarator
          name: _ @function.def
          value: (function_expression
            name: (identifier) @function.alias))

        ":" @delimiter
        "=" @operator
      `);

      const captures = query.captures(tree.rootNode);
      assert.deepEqual(formatCaptures(captures), [
        { name: "method.def", text: "bc" },
        { name: "delimiter", text: ":" },
        { name: "method.alias", text: "de" },
        { name: "function.def", text: "fg" },
        { name: "operator", text: "=" },
        { name: "function.alias", text: "hi" },
        { name: "method.def", text: "jk" },
        { name: "delimiter", text: ":" },
        { name: "method.alias", text: "lm" },
        { name: "function.def", text: "no" },
        { name: "operator", text: "=" },
        { name: "function.alias", text: "pq" },
      ]);
    });

    it("handles conditions that compare the text of capture to literal strings", () => {
      tree = parser.parse(`
        lambda
        panda
        load
        toad
        const ab = require('./ab');
        new Cd(EF);
      `);

      query = JavaScript.query(`
        ((identifier) @variable
         (#not-match? @variable "^(lambda|load)$"))

        ((identifier) @function.builtin
         (#eq? @function.builtin "require"))

        ((identifier) @constructor
         (#match? @constructor "^[A-Z]"))

        ((identifier) @constant
         (#match? @constant "^[A-Z]{2,}$"))
      `);

      const captures = query.captures(tree.rootNode);
      assert.deepEqual(formatCaptures(captures), [
        { name: "variable", text: "panda" },
        { name: "variable", text: "toad" },
        { name: "variable", text: "ab" },
        { name: "variable", text: "require" },
        { name: "function.builtin", text: "require" },
        { name: "variable", text: "Cd" },
        { name: "constructor", text: "Cd" },
        { name: "variable", text: "EF" },
        { name: "constructor", text: "EF" },
        { name: "constant", text: "EF" },
      ]);
    });

    it("handles conditions that compare the text of capture to each other", () => {
      tree = parser.parse(`
        ab = abc + 1;
        def = de + 1;
        ghi = ghi + 1;
      `);

      query = JavaScript.query(`
        (
          (assignment_expression
            left: (identifier) @id1
            right: (binary_expression
              left: (identifier) @id2))
          (#eq? @id1 @id2)
        )
      `);

      const captures = query.captures(tree.rootNode);
      assert.deepEqual(formatCaptures(captures), [
        { name: "id1", text: "ghi" },
        { name: "id2", text: "ghi" },
      ]);
    });

    it("handles patterns with properties", () => {
      tree = parser.parse(`a(b.c);`);
      query = JavaScript.query(`
        ((call_expression (identifier) @func)
         (#set! foo)
         (#set! bar baz))

        ((property_identifier) @prop
         (#is? foo)
         (#is-not? bar baz))
      `);

      const captures = query.captures(tree.rootNode);
      assert.deepEqual(formatCaptures(captures), [
        { name: "func", text: "a", setProperties: { foo: null, bar: "baz" } },
        {
          name: "prop",
          text: "c",
          assertedProperties: { foo: null },
          refutedProperties: { bar: "baz" },
        },
      ]);
      assert.ok(!query.didExceedMatchLimit());
    });

    it("detects queries with too many permutations to track", () => {
      tree = parser.parse(`
        [
          hello, hello, hello, hello, hello, hello, hello, hello, hello, hello,
          hello, hello, hello, hello, hello, hello, hello, hello, hello, hello,
          hello, hello, hello, hello, hello, hello, hello, hello, hello, hello,
          hello, hello, hello, hello, hello, hello, hello, hello, hello, hello,
          hello, hello, hello, hello, hello, hello, hello, hello, hello, hello,
        ];
      `);

      query = JavaScript.query(`
        (array (identifier) @pre (identifier) @post)
      `);

      const captures = query.captures(tree.rootNode, null, null, { matchLimit: 32 });
      assert.ok(query.didExceedMatchLimit());
    });

    it("handles quantified captures properly", () => {
      let captures;

      tree = parser.parse(`
        /// foo
        /// bar
        /// baz
      `);

      query = JavaScript.query(`
        (
          (comment)+ @foo
          (#any-eq? @foo "/// foo")
        )
      `);

      let expectCount = (tree, queryText, expectedCount) => {
        query = JavaScript.query(queryText);
        captures = query.captures(tree.rootNode, null, null);
        assert.equal(captures.length, expectedCount);
      };

      expectCount(
        tree,
        ` ( (comment)+ @foo (#any-eq? @foo "/// foo") ) `,
        3
      );

      expectCount(
        tree,
        ` ( (comment)+ @foo (#eq? @foo "/// foo") ) `,
        0
      );

      expectCount(
        tree,
        ` ( (comment)+ @foo (#any-not-eq? @foo "/// foo") ) `,
        3
      );

      expectCount(
        tree,
        ` ( (comment)+ @foo (#not-eq? @foo "/// foo") ) `,
        0
      );

      expectCount(
        tree,
        ` ( (comment)+ @foo (#match? @foo "^/// foo") ) `,
        0
      );

      expectCount(
        tree,
        ` ( (comment)+ @foo (#any-match? @foo "^/// foo") ) `,
        3
      );

      expectCount(
        tree,
        ` ( (comment)+ @foo (#not-match? @foo "^/// foo") ) `,
        0
      );

      expectCount(
        tree,
        ` ( (comment)+ @foo (#not-match? @foo "fsdfsdafdfs") ) `,
        3
      );

      expectCount(
        tree,
        ` ( (comment)+ @foo (#any-not-match? @foo "^///") ) `,
        0
      );

      expectCount(
        tree,
        ` ( (comment)+ @foo (#any-not-match? @foo "^/// foo") ) `,
        3
      );
    })
  });

  describe(".predicatesForPattern(index)", () => {
    it("returns all of the predicates as objects", () => {
      query = JavaScript.query(`
        (
          (binary_expression
            left: (identifier) @a
            right: (identifier) @b)
          (#something? @a @b)
          (#match? @a "c")
          (#something-else? @a "A" @b "B")
        )

        ((identifier) @c
         (#hello! @c))

        "if" @d
      `);

      assert.deepEqual(query.predicatesForPattern(0), [
        {
          operator: "something?",
          operands: [
            { type: "capture", name: "a" },
            { type: "capture", name: "b" },
          ],
        },
        {
          operator: "something-else?",
          operands: [
            { type: "capture", name: "a" },
            { type: "string", value: "A" },
            { type: "capture", name: "b" },
            { type: "string", value: "B" },
          ],
        },
      ]);
      assert.deepEqual(query.predicatesForPattern(1), [
        {
          operator: "hello!",
          operands: [{ type: "capture", name: "c" }],
        },
      ]);
      assert.deepEqual(query.predicatesForPattern(2), []);
    });
  });
});

function formatMatches(matches) {
  return matches.map(({ pattern, captures }) => ({
    pattern,
    captures: formatCaptures(captures),
  }));
}

function formatCaptures(captures) {
  return captures.map((c) => {
    const node = c.node;
    delete c.node;
    c.text = node.text;
    return c;
  });
}
