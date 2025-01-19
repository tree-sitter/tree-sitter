import { describe, it, expect, beforeAll, beforeEach, afterEach } from 'vitest';
import type { Parser as ParserType, Language, Tree, Query, QueryMatch, QueryCapture } from '../src';
import helper from './helper';

let Parser: typeof ParserType;
let JavaScript: Language;

describe('Query', () => {
  let parser: ParserType;
  let tree: Tree | null;
  let query: Query | null;

  beforeAll(async () => {
    ({ Parser, JavaScript } = await helper);
  });

  beforeEach(() => {
    parser = new Parser();
    parser.setLanguage(JavaScript);
  });

  afterEach(() => {
    parser.delete();
    if (tree) tree.delete();
    if (query) query.delete();
  });

  describe('construction', () => {
    it('throws an error on invalid patterns', () => {
      expect(() => {
        JavaScript.query('(function_declaration wat)');
      }).toThrow('Bad syntax at offset 22: \'wat)\'...');

      expect(() => {
        JavaScript.query('(non_existent)');
      }).toThrow('Bad node name \'non_existent\'');

      expect(() => {
        JavaScript.query('(a)');
      }).toThrow('Bad node name \'a\'');

      expect(() => {
        JavaScript.query('(function_declaration non_existent:(identifier))');
      }).toThrow('Bad field name \'non_existent\'');

      expect(() => {
        JavaScript.query('(function_declaration name:(statement_block))');
      }).toThrow('Bad pattern structure at offset 22: \'name:(statement_block))\'');
    });

    it('throws an error on invalid predicates', () => {
      expect(() => {
        JavaScript.query('((identifier) @abc (#eq? @ab hi))');
      }).toThrow('Bad capture name @ab');

      expect(() => {
        JavaScript.query('((identifier) @abc (#eq?))');
      }).toThrow('Wrong number of arguments to `#eq?` predicate. Expected 2, got 0');

      expect(() => {
        JavaScript.query('((identifier) @a (#eq? @a @a @a))');
      }).toThrow('Wrong number of arguments to `#eq?` predicate. Expected 2, got 3');
    });
  });

  describe('.matches', () => {
    it('returns all of the matches for the given query', () => {
      tree = parser.parse('function one() { two(); function three() {} }');
      query = JavaScript.query(`
        (function_declaration name: (identifier) @fn-def)
        (call_expression function: (identifier) @fn-ref)
      `);
      const matches = query.matches(tree.rootNode);
      expect(formatMatches(matches)).toEqual([
        { pattern: 0, captures: [{ name: 'fn-def', text: 'one' }] },
        { pattern: 1, captures: [{ name: 'fn-ref', text: 'two' }] },
        { pattern: 0, captures: [{ name: 'fn-def', text: 'three' }] },
      ]);
    });

    it('can search in specified ranges', () => {
      tree = parser.parse('[a, b,\nc, d,\ne, f,\ng, h]');
      query = JavaScript.query('(identifier) @element');
      const matches = query.matches(
        tree.rootNode,
        {
          startPosition: { row: 1, column: 1 },
          endPosition: { row: 3, column: 1 },
        }
      );
      expect(formatMatches(matches)).toEqual([
        { pattern: 0, captures: [{ name: 'element', text: 'd' }] },
        { pattern: 0, captures: [{ name: 'element', text: 'e' }] },
        { pattern: 0, captures: [{ name: 'element', text: 'f' }] },
        { pattern: 0, captures: [{ name: 'element', text: 'g' }] },
      ]);
    });

    it('handles predicates that compare the text of capture to literal strings', () => {
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
      expect(formatMatches(matches)).toEqual([
        { pattern: 0, captures: [{ name: 'name', text: 'giraffe' }] },
        { pattern: 0, captures: [{ name: 'name', text: 'gross' }] },
      ]);
    });

    it('handles multiple matches where the first one is filtered', () => {
      tree = parser.parse(`
        const a = window.b;
      `);

      query = JavaScript.query(`
        ((identifier) @variable.builtin
          (#match? @variable.builtin "^(arguments|module|console|window|document)$")
          (#is-not? local))
      `);

      const matches = query.matches(tree.rootNode);
      expect(formatMatches(matches)).toEqual([
        { pattern: 0, captures: [{ name: 'variable.builtin', text: 'window' }] },
      ]);
    });
  });

  describe('.captures', () => {
    it('returns all of the captures for the given query, in order', () => {
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
      expect(formatCaptures(captures)).toEqual([
        { name: 'method.def', text: 'bc' },
        { name: 'delimiter', text: ':' },
        { name: 'method.alias', text: 'de' },
        { name: 'function.def', text: 'fg' },
        { name: 'operator', text: '=' },
        { name: 'function.alias', text: 'hi' },
        { name: 'method.def', text: 'jk' },
        { name: 'delimiter', text: ':' },
        { name: 'method.alias', text: 'lm' },
        { name: 'function.def', text: 'no' },
        { name: 'operator', text: '=' },
        { name: 'function.alias', text: 'pq' },
      ]);
    });

    it('handles conditions that compare the text of capture to literal strings', () => {
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
      expect(formatCaptures(captures)).toEqual([
        { name: 'variable', text: 'panda' },
        { name: 'variable', text: 'toad' },
        { name: 'variable', text: 'ab' },
        { name: 'variable', text: 'require' },
        { name: 'function.builtin', text: 'require' },
        { name: 'variable', text: 'Cd' },
        { name: 'constructor', text: 'Cd' },
        { name: 'variable', text: 'EF' },
        { name: 'constructor', text: 'EF' },
        { name: 'constant', text: 'EF' },
      ]);
    });

    it('handles conditions that compare the text of captures to each other', () => {
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
      expect(formatCaptures(captures)).toEqual([
        { name: 'id1', text: 'ghi' },
        { name: 'id2', text: 'ghi' },
      ]);
    });

    it('handles patterns with properties', () => {
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
      expect(formatCaptures(captures)).toEqual([
        {
          name: 'func',
          text: 'a',
          setProperties: { foo: null, bar: 'baz' }
        },
        {
          name: 'prop',
          text: 'c',
          assertedProperties: { foo: null },
          refutedProperties: { bar: 'baz' },
        },
      ]);
      expect(query.didExceedMatchLimit()).toBe(false);
    });

    it('detects queries with too many permutations to track', () => {
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

      query.captures(tree.rootNode, { matchLimit: 32 });
      expect(query.didExceedMatchLimit()).toBe(true);
    });

    it('handles quantified captures properly', () => {
      tree = parser.parse(`
        /// foo
        /// bar
        /// baz
      `);

      const expectCount = (tree: Tree, queryText: string, expectedCount: number) => {
        query = JavaScript.query(queryText);
        const captures = query.captures(tree.rootNode);
        expect(captures).toHaveLength(expectedCount);
      };

      expectCount(
        tree,
        `((comment)+ @foo (#any-eq? @foo "/// foo"))`,
        3
      );

      expectCount(
        tree,
        `((comment)+ @foo (#eq? @foo "/// foo"))`,
        0
      );

      expectCount(
        tree,
        `((comment)+ @foo (#any-not-eq? @foo "/// foo"))`,
        3
      );

      expectCount(
        tree,
        `((comment)+ @foo (#not-eq? @foo "/// foo"))`,
        0
      );

      expectCount(
        tree,
        `((comment)+ @foo (#match? @foo "^/// foo"))`,
        0
      );

      expectCount(
        tree,
        `((comment)+ @foo (#any-match? @foo "^/// foo"))`,
        3
      );

      expectCount(
        tree,
        `((comment)+ @foo (#not-match? @foo "^/// foo"))`,
        0
      );

      expectCount(
        tree,
        `((comment)+ @foo (#not-match? @foo "fsdfsdafdfs"))`,
        3
      );

      expectCount(
        tree,
        `((comment)+ @foo (#any-not-match? @foo "^///"))`,
        0
      );

      expectCount(
        tree,
        `((comment)+ @foo (#any-not-match? @foo "^/// foo"))`,
        3
      );
    });
  });

  describe('.predicatesForPattern(index)', () => {
    it('returns all of the predicates as objects', () => {
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

      expect(query.predicatesForPattern(0)).toStrictEqual([
        {
          operator: 'something?',
          operands: [
            { type: 'capture', name: 'a' },
            { type: 'capture', name: 'b' },
          ],
        },
        {
          operator: 'something-else?',
          operands: [
            { type: 'capture', name: 'a' },
            { type: 'string', value: 'A' },
            { type: 'capture', name: 'b' },
            { type: 'string', value: 'B' },
          ],
        },
      ]);

      expect(query.predicatesForPattern(1)).toStrictEqual([
        {
          operator: 'hello!',
          operands: [{ type: 'capture', name: 'c' }],
        },
      ]);

      expect(query.predicatesForPattern(2)).toEqual([]);
    });
  });

  describe('.disableCapture', () => {
    it('disables a capture', () => {
      query = JavaScript.query(`
        (function_declaration
          (identifier) @name1 @name2 @name3
          (statement_block) @body1 @body2)
      `);

      const source = 'function foo() { return 1; }';
      const tree = parser.parse(source);

      let matches = query.matches(tree.rootNode);
      expect(formatMatches(matches)).toEqual([
        {
          pattern: 0,
          captures: [
            { name: 'name1', text: 'foo' },
            { name: 'name2', text: 'foo' },
            { name: 'name3', text: 'foo' },
            { name: 'body1', text: '{ return 1; }' },
            { name: 'body2', text: '{ return 1; }' },
          ],
        },
      ]);

      // disabling captures still works when there are multiple captures on a
      // single node.
      query.disableCapture('name2');
      matches = query.matches(tree.rootNode);
      expect(formatMatches(matches)).toEqual([
        {
          pattern: 0,
          captures: [
            { name: 'name1', text: 'foo' },
            { name: 'name3', text: 'foo' },
            { name: 'body1', text: '{ return 1; }' },
            { name: 'body2', text: '{ return 1; }' },
          ],
        },
      ]);
    });
  });

  describe('Set a timeout', () => {
    it('returns less than the expected matches', () => {
      tree = parser.parse('function foo() while (true) { } }\n'.repeat(1000));
      query = JavaScript.query(
        '(function_declaration name: (identifier) @function)'
      );
      const matches = query.matches(tree.rootNode, { timeoutMicros: 1000 });
      expect(matches.length).toBeLessThan(1000);
      const matches2 = query.matches(tree.rootNode, { timeoutMicros: 0 });
      expect(matches2).toHaveLength(1000);
    });
  });

  describe('Start and end indices for patterns', () => {
    it('Returns the start and end indices for a pattern', () => {
      const patterns1 = `
"+" @operator
"-" @operator
"*" @operator
"=" @operator
"=>" @operator
      `.trim();

      const patterns2 = `
(identifier) @a
(string) @b
`.trim();

      const patterns3 = `
((identifier) @b (#match? @b i))
(function_declaration name: (identifier) @c)
(method_definition name: (property_identifier) @d)
`.trim();

      const source = patterns1 + patterns2 + patterns3;

      const query = JavaScript.query(source);

      expect(query.startIndexForPattern(0)).toBe(0);
      expect(query.endIndexForPattern(0)).toBe('"+" @operator\n'.length);
      expect(query.startIndexForPattern(5)).toBe(patterns1.length);
      expect(query.endIndexForPattern(5)).toBe(
        patterns1.length + '(identifier) @a\n'.length
      );
      expect(query.startIndexForPattern(7)).toBe(patterns1.length + patterns2.length);
      expect(query.endIndexForPattern(7)).toBe(
        patterns1.length +
        patterns2.length +
        '((identifier) @b (#match? @b i))\n'.length
      );
    });
  });

  describe('Disable pattern', () => {
    it('Disables patterns in the query', () => {
      const query = JavaScript.query(`
        (function_declaration name: (identifier) @name)
        (function_declaration body: (statement_block) @body)
        (class_declaration name: (identifier) @name)
        (class_declaration body: (class_body) @body)
      `);

      // disable the patterns that match names
      query.disablePattern(0);
      query.disablePattern(2);

      const source = 'class A { constructor() {} } function b() { return 1; }';
      tree = parser.parse(source);
      const matches = query.matches(tree.rootNode);
      expect(formatMatches(matches)).toEqual([
        {
          pattern: 3,
          captures: [{ name: 'body', text: '{ constructor() {} }' }],
        },
        { pattern: 1, captures: [{ name: 'body', text: '{ return 1; }' }] },
      ]);
    });
  });

  describe('Executes with a timeout', () => {
    it('Returns less than the expected matches', () => {
      tree = parser.parse('function foo() while (true) { } }\n'.repeat(1000));
      query = JavaScript.query(
        '(function_declaration) @function'
      );

      const startTime = performance.now();

      const matches = query.matches(
        tree.rootNode,
        {
          progressCallback: () => {
            if (performance.now() - startTime > 1) {
              return true;
            }
            return false;
          },
        }
      );
      expect(matches.length).toBeLessThan(1000);

      const matches2 = query.matches(tree.rootNode);
      expect(matches2).toHaveLength(1000);
    });
  });
});

// Helper functions
function formatMatches(matches: QueryMatch[]): QueryMatch[] {
  return matches.map(({ pattern, captures }) => ({
    pattern,
    captures: formatCaptures(captures),
  }));
}

function formatCaptures(captures: QueryCapture[]): (QueryCapture & { text: string })[] {
  return captures.map((c) => {
    const node = c.node;
    // @ts-expect-error We're not interested in the node object for these tests
    delete c.node;
    return { ...c, text: node.text };
  });
}
