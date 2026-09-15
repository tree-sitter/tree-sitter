// Run with: node --test crates/generate/src/dsl.test.mjs
import assert from "node:assert/strict";
import { spawnSync } from "node:child_process";
import { mkdtempSync, readFileSync, rmSync, writeFileSync } from "node:fs";
import { tmpdir } from "node:os";
import { join } from "node:path";
import { pathToFileURL } from "node:url";
import test from "node:test";

// Match the concatenated script passed to the JS runtime by the Rust loader.
const dsl = ["legacy-dsl.js", "dsl.js"]
  .map(name => readFileSync(new URL(name, import.meta.url), "utf8"))
  .join("\n");

function run(files, entry = "grammar.mjs") {
  const directory = mkdtempSync(join(tmpdir(), "tree-sitter-module-dsl-"));
  try {
    for (const [name, source] of Object.entries(files)) {
      writeFileSync(join(directory, name), source);
    }
    const result = spawnSync(process.execPath, ["--input-type=module"], {
      input: dsl,
      encoding: "utf8",
      env: {
        ...process.env,
        TREE_SITTER_GRAMMAR_PATH: pathToFileURL(join(directory, entry)).href,
      },
      timeout: 10_000,
    });
    assert.ifError(result.error);
    return result;
  } finally {
    rmSync(directory, { recursive: true, force: true });
  }
}

function compile(files, entry) {
  const result = run(files, entry);
  assert.equal(result.status, 0, result.stderr);
  return JSON.parse(result.stdout);
}

function rejects(source, ...messages) {
  const result = run({ "grammar.mjs": source });
  assert.notEqual(result.status, 0, "Invalid grammar unexpectedly compiled");
  for (const message of messages) assert.match(result.stderr, message);
}

function cleanFailure(files, entry) {
  const result = run(files, entry);
  assert.notEqual(result.status, 0, "Invalid grammar unexpectedly compiled");
  assert.equal(result.stdout, "");
  assert.doesNotMatch(result.stderr, /tree-sitter:grammar-dsl/);
  return result.stderr;
}

for (const builder of ["rule(() => 'x')", "rule()", "external()"]) {
  test(`unexported ${builder} points to its declaration`, () => {
    const error = cleanFailure({
      "dsl.mjs": `const original = rule(() => 'x');\nconst hidden = ${builder};\nexport const getHidden = () => hidden;`,
      "grammar.mjs": [
        "import { getHidden } from './dsl.mjs';",
        "export const root = rule(() => alias('x', getHidden()));",
        "export default { name: 'test', start: root };",
      ].join("\n"),
    });
    assert.match(error, /Rule 'root': Unregistered rule handle/);
    assert.match(error, /Unexported rule declared at:\n[\s\S]*dsl\.mjs:2:/);
    assert.doesNotMatch(error, /symbolName|referenceName|Array\.map|node:internal/);
  });
}

test("callback errors retain user helper frames and refresh an already captured heading", () => {
  const error = cleanFailure({
    "package.json": '{"type":"module"}',
    "dsl.js": [
      "export function normalize() {",
      "  const error = new TypeError('helper failure');",
      "  void error.stack;",
      "  throw Object.freeze(error);",
      "}",
    ].join("\n"),
    "grammar.mjs": [
      "import { normalize } from './dsl.js';",
      "export const root = rule(() => normalize());",
      "export default { name: 'test', start: root };",
    ].join("\n"),
  });
  assert.match(error, /TypeError: Rule 'root': helper failure/);
  assert.match(error, /at normalize \([^\n]*dsl\.js:2:/);
  assert.match(error, /grammar\.mjs:2:/);
  assert.equal(error.match(/helper failure/g).length, 1);
});

test("module initialization errors retain user locations", () => {
  const error = cleanFailure({
    "grammar.mjs": "// User module initialization\nthrow new Error('initialization failure');",
  });
  assert.match(error, /Error: initialization failure/);
  assert.match(error, /grammar\.mjs:2:/);
});

test("changed messages do not leave stale stack headings", () => {
  const error = cleanFailure({
    "grammar.mjs": `
      export const root = rule(() => {
        const error = new Error("old message\\nold detail");
        void error.stack;
        error.name = "ChangedError";
        error.message = "new message\\nnew detail";
        throw error;
      });
      export default {name: 'test', start: root};
    `,
  });
  assert.match(error, /ChangedError: Rule 'root': new message\nnew detail/);
  assert.doesNotMatch(error, /old message|old detail/);
});

test("causes and aggregate members retain their messages and filtered stacks", () => {
  const error = cleanFailure({
    "grammar.mjs": `
      export const root = rule(() => {
        let cause;
        try { seq(() => 'invalid'); } catch (error) { cause = error; }
        throw new AggregateError(
          [new Error('first failure'), new Error('second failure')],
          'build failed', {cause},
        );
      });
      export default {name: 'test', start: root};
    `,
  });
  assert.match(error, /AggregateError: Rule 'root': build failed/);
  assert.match(error, /Caused by:\nTypeError: Expected a rule handle/);
  assert.match(error, /Aggregate error 1:\nError: first failure/);
  assert.match(error, /Aggregate error 2:\nError: second failure/);
});

test("circular error causes terminate without losing the outer message", () => {
  const error = cleanFailure({
    "grammar.mjs": `
      export const root = rule(() => {
        const error = new Error('circular failure');
        error.cause = error;
        throw error;
      });
      export default {name: 'test', start: root};
    `,
  });
  assert.match(error, /Rule 'root': circular failure/);
  assert.match(error, /Caused by:\n\[Circular error\]/);
});

test("syntax errors retain the imported source excerpt", () => {
  const error = cleanFailure({
    "grammar.mjs": "export const broken = ;",
  });
  assert.match(error, /SyntaxError/);
  assert.match(error, /grammar\.mjs:1/);
  assert.match(error, /export const broken = ;/);
});

test("legacy callback errors retain CommonJS helper locations", () => {
  const error = cleanFailure({
    "legacy-dsl.cjs": "exports.normalize = () => { throw new Error('legacy helper failure'); };",
    "grammar.cjs": [
      "const { normalize } = require('./legacy-dsl.cjs');",
      "module.exports = grammar({name: 'legacy', rules: {root: () => normalize()}});",
    ].join("\n"),
  }, "grammar.cjs");
  assert.match(error, /legacy helper failure/);
  assert.match(error, /legacy-dsl\.cjs:1:/);
  assert.match(error, /grammar\.cjs:2:/);
});

test("diagnostics do not depend on Error.captureStackTrace", () => {
  const error = cleanFailure({
    "grammar.mjs": [
      "Error.captureStackTrace = () => { throw new Error('V8-only API was called'); };",
      "export const root = rule(() => optional('a', 'b'));",
      "export default {name: 'test', start: root};",
    ].join("\n"),
  });
  assert.match(error, /only takes one rule argument/);
  assert.match(error, /grammar\.mjs:2:/);
  assert.doesNotMatch(error, /V8-only API was called/);
});

test("errors without stacks still report their message and containing rule", () => {
  const error = cleanFailure({
    "grammar.mjs": [
      "export const root = rule(() => {",
      "  const error = new Error('no stack');",
      "  Object.defineProperty(error, 'stack', { value: undefined });",
      "  throw error;",
      "});",
      "export default {name: 'test', start: root};",
    ].join("\n"),
  });
  assert.match(error, /Error: Rule 'root': no stack/);
  assert.match(error, /grammar\.mjs:1:/);
});

const symbol = name => ({ type: "SYMBOL", name });
const string = value => ({ type: "STRING", value });
const pattern = value => ({ type: "PATTERN", value });
const seq = (...members) => ({ type: "SEQ", members });

const moduleSource = `
export const z_start = rule(() => seq(word, optional(z_start))),
  word = rule(() => /[a-z]+/);
export default {
  name: "example", start: z_start, extras: [/\\s/], word,
  conflicts: [[word, z_start]], inline: [word],
  precedences: [[word, "named"]], reserved: { global: ["if"] },
};
`;
const legacySource = `
grammar({
  name: "example",
  rules: {
    z_start: $ => seq($.word, optional($.z_start)),
    word: $ => /[a-z]+/,
  },
  extras: $ => [/\\s/], word: $ => $.word,
  conflicts: $ => [[$.word, $.z_start]], inline: $ => [$.word],
  precedences: $ => [[$.word, "named"]],
  reserved: { global: $ => ["if"] },
})
`;

test("module and legacy grammars produce the same complete JSON across module formats", () => {
  const expected = {
    $schema: "https://tree-sitter.github.io/tree-sitter/assets/schemas/grammar.schema.json",
    name: "example",
    rules: {
      z_start: seq(symbol("word"), {
        type: "CHOICE", members: [symbol("z_start"), { type: "BLANK" }],
      }),
      word: pattern("[a-z]+"),
    },
    extras: [pattern("\\s")],
    externals: [],
    word: "word",
    conflicts: [["word", "z_start"]],
    inline: ["word"],
    supertypes: [],
    precedences: [[symbol("word"), string("named")]],
    reserved: { global: [string("if")] },
  };
  const variants = [
    [{ "grammar.mjs": moduleSource }, "grammar.mjs"],
    [{ "package.json": '{"type":"module"}', "grammar.js": moduleSource }, "grammar.js"],
    [{ "grammar.mjs": `export default ${legacySource}` }, "grammar.mjs"],
    [{ "package.json": '{"type":"module"}', "grammar.js": `export default ${legacySource}` }, "grammar.js"],
    [{ "grammar.js": `module.exports = ${legacySource}` }, "grammar.js"],
    [{ "grammar.cjs": `module.exports = ${legacySource}` }, "grammar.cjs"],
  ];
  for (const [files, entry] of variants) {
    const actual = compile(files, entry);
    assert.deepEqual(actual, expected, entry);
    assert.equal(Object.keys(actual.rules)[0], "z_start", "Explicit start precedes alphabetically earlier exports");
  }
});

test("forward, self and mutual references in comma-separated declarations stay symbols", () => {
  const actual = compile({
    "grammar.mjs": `
      export const z_start = rule(() => seq(a, z_start)),
        a = rule(() => choice("a", b)),
        b = rule(() => seq("b", a));
      export default { name: "recursive", start: z_start };
    `,
  });
  assert.equal(Object.keys(actual.rules)[0], "z_start");
  assert.deepEqual(actual.rules, {
    z_start: seq(symbol("a"), symbol("z_start")),
    a: { type: "CHOICE", members: [string("a"), symbol("b")] },
    b: seq(string("b"), symbol("a")),
  });
});

test("helpers can be ordinary imported functions without becoming rules", () => {
  const actual = compile({
    "helpers.mjs": `export const surrounded = value => seq("(", value, ")");`,
    "grammar.mjs": `
      import { surrounded } from "./helpers.mjs";
      export const root = rule(() => surrounded(item)), item = rule(() => "i");
      export default { name: "helpers", start: root };
    `,
  });
  assert.deepEqual(actual.rules.root, seq(string("("), symbol("item"), string(")")));
  assert.deepEqual(Object.keys(actual.rules), ["root", "item"]);
});

test("alias-only symbols preserve node names without adding rule bodies", () => {
  const actual = compile({
    "grammar.mjs": `
      export const type_identifier = rule(),
        root = rule(() => alias(identifier, type_identifier)),
        identifier = rule(() => /[a-z]+/);
      export default { name: "aliases", start: root };
    `,
  });
  assert.deepEqual(actual.rules.root, {
    type: "ALIAS", content: symbol("identifier"), named: true, value: "type_identifier",
  });
  assert.deepEqual(Object.keys(actual.rules), ["root", "identifier"]);
  assert.deepEqual(actual.externals, []);
});

test("alias-only declarations and their references are inherited", () => {
  const actual = compile({
    "base.mjs": `
      export const label = rule(), root = rule(() => alias("x", label));
      export default { name: "base", start: root };
    `,
    "grammar.mjs": `
      import * as base from "./base.mjs";
      export const root = rule(() => alias("y", base.label));
      export default { name: "derived", extends: base };
    `,
  });
  assert.deepEqual(actual.rules, {
    root: { type: "ALIAS", content: string("y"), named: true, value: "label" },
  });
});

for (const expression of ["label", "seq(label)", "alias(label, root)", 'sym("label")']) {
  test(`alias-only symbols cannot be referenced in expressions: ${expression}`, () => {
    const result = run({
      "grammar.mjs": `
        export const label = rule(), root = rule(() => ${expression});
        export default { name: "invalid", start: root };
      `,
    });
    assert.notEqual(result.status, 0);
    assert.match(result.stderr, /Symbol 'label' has no rule body/);
    assert.match(result.stderr, /only be used as alias targets/);
  });
}

for (const [name, value] of [
  ["start", "label"], ["word", "label"], ["extras", "[label]"],
  ["externals", "[label]"], ["inline", "[label]"], ["supertypes", "[label]"],
  ["conflicts", "[[label]]"], ["precedences", "[[label]]"],
  ["reserved", "{ global: [label] }"],
]) {
  test(`alias-only symbols cannot be used in ${name}`, () => {
    const result = run({
      "grammar.mjs": `
        export const label = rule(), root = rule(() => "x");
        export default { name: "invalid", start: root, ${name}: ${value} };
      `,
    });
    assert.notEqual(result.status, 0);
    assert.match(result.stderr, /Symbol 'label' has no rule body/);
  });
}

test("a named rule called grammar is not mistaken for the legacy schema", () => {
  const actual = compile({
    "grammar.mjs": `
      export const grammar = rule(() => "g");
      export default { name: "named_grammar", start: grammar };
    `,
  });
  assert.equal(actual.name, "named_grammar");
  assert.deepEqual(actual.rules, { grammar: string("g") });
});

test("rule invocation order is retained for structural GLR ties", () => {
  const actual = compile({
    "grammar.mjs": `
      export const z_keyword = rule(() => /int/),
        a_identifier = rule(() => /[a-z]+/),
        root = rule(() => choice(z_keyword, a_identifier));
      export default {name: 'ordered', start: root};
    `,
  });
  assert.deepEqual(Object.keys(actual.rules), ["root", "z_keyword", "a_identifier"]);
});

test("original bodies are lazy, normalized, evaluated once, and copied for each access", () => {
  const actual = compile({
    "base.mjs": `
      let evaluations = 0;
      export const z_item = rule(() => {
        if (++evaluations > 1) throw new Error("base body evaluated twice");
        return choice('base', a_other);
      }), a_other = rule(() => 'old'), root = rule(() => z_item);
      export default {name: 'base', start: root};
    `,
    "grammar.mjs": `
      import * as base from './base.mjs';
      export const z_item = rule(original => {
        const changed = original();
        if (changed.members[1].name !== 'a_other') throw new Error('not normalized');
        changed.members[0].value = 'changed';
        const unchanged = original();
        if (unchanged.members[0].value !== 'base') throw new Error('base was mutated');
        return choice(...changed.members, ...unchanged.members);
      }), a_other = rule(() => 'new');
      export default {name: 'derived', extends: base};
    `,
  });
  assert.deepEqual(Object.keys(actual.rules), ["root", "z_item", "a_other"]);
  assert.deepEqual(actual.rules.z_item, {
    type: "CHOICE",
    members: [string("changed"), symbol("a_other"), string("base"), symbol("a_other")],
  });
  assert.deepEqual(actual.rules.a_other, string("new"));
});

test("original follows the immediate predecessor through multiple overrides", () => {
  const actual = compile({
    "base.mjs": `
      export const root = rule(() => 'base');
      export default {name: 'base', start: root};
    `,
    "middle.mjs": `
      import * as base from './base.mjs';
      export const root = rule(original => seq(original(), 'middle'));
      export default {name: 'middle', extends: base};
    `,
    "grammar.mjs": `
      import * as middle from './middle.mjs';
      export const root = rule(original => seq(original(), 'leaf'));
      export default {name: 'leaf', extends: middle};
    `,
  });
  assert.deepEqual(actual.rules.root, seq(seq(string("base"), string("middle")), string("leaf")));
});

test("failed original bodies are evaluated only once", () => {
  const actual = compile({
    "base.mjs": `
      let calls = 0;
      export const root = rule(() => {
        if (++calls > 1) throw new Error('evaluated twice');
        throw new Error('original failure');
      });
      export default {name: 'base', start: root};
    `,
    "grammar.mjs": `
      import * as base from './base.mjs';
      export const root = rule(original => {
        let first;
        try { original(); } catch (error) { first = error; }
        if (!first || !first.message.includes('original failure')) {
          throw new Error('original failure was not reported');
        }
        let second;
        try { original(); } catch (error) {
          second = error;
        }
        if (second !== first) throw new Error('failure was not cached');
        return 'recovered';
      });
      export default {name: 'derived', extends: base};
    `,
  });
  assert.deepEqual(actual.rules.root, string("recovered"));
});

test("reusing an ancestor handle evaluates its builder against the active predecessor", () => {
  const actual = compile({
    "base.mjs": `
      export const root = rule(() => 'base');
      export default {name: 'base', start: root};
    `,
    "middle.mjs": `
      import * as base from './base.mjs';
      export const root = rule(original => seq(original(), 'middle'));
      export default {name: 'middle', extends: base};
    `,
    "replacement.mjs": `
      import * as middle from './middle.mjs';
      export const root = rule(original => seq(original(), 'replacement'));
      export default {name: 'replacement', extends: middle};
    `,
    "grammar.mjs": `
      import * as middle from './middle.mjs';
      import * as replacement from './replacement.mjs';
      export const root = middle.root;
      export default {name: 'leaf', extends: replacement};
    `,
  });
  assert.deepEqual(actual.rules.root,
    seq(seq(seq(string("base"), string("middle")), string("replacement")), string("middle")));
});

test("original without inheritance reports the containing rule", () => {
  rejects(`
    export const root = rule(original => original());
    export default {name: 'test', start: root};
  `, /Rule 'root' has no inherited body\./);
});

for (const inherited of ["rule()", "external()"]) {
  test(`original rejects an inherited declaration without a body: ${inherited}`, () => {
    const error = cleanFailure({
      "base.mjs": `
        export const item = ${inherited}, root = rule(() => 'base');
        export default {name: 'base', start: root};
      `,
      "grammar.mjs": `
        import * as base from './base.mjs';
        export const item = rule(original => original());
        export default {name: 'derived', extends: base};
      `,
    });
    assert.match(error, /Rule 'item' has no inherited body\./);
  });
}

test("original for a new name has no predecessor even in a derived grammar", () => {
  const error = cleanFailure({
    "base.mjs": `
      export const root = rule(() => 'base');
      export default {name: 'base', start: root};
    `,
    "grammar.mjs": `
      import * as base from './base.mjs';
      export const item = rule(original => original());
      export default {name: 'derived', extends: base};
    `,
  });
  assert.match(error, /Rule 'item' has no inherited body\./);
});

test("namespace inheritance preserves identity through multiple overrides without evaluating replaced bodies", () => {
  const actual = compile({
    "base.mjs": `
      export const root = rule(() => seq(item, item)),
        item = rule(() => { throw new Error("base body must never execute"); });
      export default { name: "base", start: root, word: item };
    `,
    "middle.mjs": `
      import * as base from "./base.mjs";
      export const item = rule(() => { throw new Error("middle body must never execute"); });
      export default { name: "middle", extends: base };
    `,
    "grammar.mjs": `
      import * as base from "./base.mjs";
      import * as middle from "./middle.mjs";
      export const item = rule(() => choice("leaf", base.item, middle.item, item));
      export default { name: "leaf", extends: middle };
    `,
  });
  assert.equal(actual.inherits, "middle");
  assert.equal(actual.word, "item");
  assert.deepEqual(Object.keys(actual.rules), ["root", "item"]);
  assert.deepEqual(actual.rules.root, seq(symbol("item"), symbol("item")));
  assert.deepEqual(actual.rules.item, {
    type: "CHOICE", members: [string("leaf"), symbol("item"), symbol("item"), symbol("item")],
  });
});

test("inherited config replaces arrays, merges reserved sets, and resolves metadata handles and aliases", () => {
  const actual = compile({
    "base.mjs": `
      export const root = rule(() => item), item = rule(() => "base"),
        old_external = external(), new_external = external();
      export default {
        name: "base", start: root, word: item, extras: ["old"],
        externals: [old_external, new_external], conflicts: [[root, item]],
        inline: [root], supertypes: [root], precedences: [[root, "old"]],
        reserved: { kept: [item], replaced: ["old"] },
      };
    `,
    "grammar.mjs": `
      import * as base from "./base.mjs";
      export const item = rule(() => alias("new", base.item));
      export default {
        name: "derived", extends: base, extras: [base.item],
        externals: [base.new_external, base.old_external],
        conflicts: [[item]], inline: [item], supertypes: [item],
        precedences: [[item, "new"]],
        reserved: { replaced: [alias("keyword", item)], added: [base.item] },
      };
    `,
  });
  assert.equal(actual.word, "item");
  assert.deepEqual(actual.extras, [symbol("item")]);
  assert.deepEqual(actual.externals, [symbol("new_external"), symbol("old_external")]);
  assert.deepEqual(actual.conflicts, [["item"]]);
  assert.deepEqual(actual.inline, ["item"]);
  assert.deepEqual(actual.supertypes, ["item"]);
  assert.deepEqual(actual.precedences, [[symbol("item"), string("new")]]);
  assert.deepEqual(actual.reserved, {
    kept: [symbol("item")],
    replaced: [{ type: "ALIAS", content: string("keyword"), named: true, value: "item" }],
    added: [symbol("item")],
  });
  assert.deepEqual(actual.rules.item, {
    type: "ALIAS", content: string("new"), named: true, value: "item",
  });
  assert.deepEqual(Object.keys(actual.rules), ["root", "item"], "External handles have no rule bodies");
});

test("external token declaration order does not replace explicit scanner order", () => {
  const actual = compile({
    "grammar.mjs": `
      export const first = external(), second = external(),
        root = rule(() => seq(first, second));
      export default { name: "external", start: root, externals: [second, first] };
    `,
  });
  assert.deepEqual(actual.externals, [symbol("second"), symbol("first")]);
  assert.deepEqual(actual.rules, { root: seq(symbol("first"), symbol("second")) });
});

const invalidCases = [
  ["handles are not callable", `
    export const root = rule(() => root());
    export default { name: "bad", start: root };
  `, /Rule 'root'/, /not a function/],
  ["rule rejects a non-function builder", `export const root = rule("x");`, /rule\(\).*function/],
  ["plain function exports are not handles", `
    export const root = () => "x";
    export default { name: "bad", start: root };
  `, /Export 'root'.*not a rule handle/],
  ["function expressions are not implicitly invoked", `
    const helper = () => "x";
    export const root = rule(() => seq(helper));
    export default { name: "bad", start: root };
  `, /Rule 'root'/, /not a function/, /Call helpers/],
  ["undefined body gives return guidance", `
    export const root = rule(() => {});
    export default { name: "bad", start: root };
  `, /Rule 'root'/, /undefined/, /return/],
  ["unregistered rule references are rejected", `
    const hidden = rule(() => "x");
    export const root = rule(() => hidden);
    export default { name: "bad", start: root };
  `, /Rule 'root'/, /Unregistered rule handle/, /Export/],
  ["unregistered alias targets are rejected", `
    const hidden = rule(() => "x");
    export const root = rule(() => alias("x", hidden));
    export default { name: "bad", start: root };
  `, /Rule 'root'/, /Unregistered rule handle/],
  ["duplicate export aliases are rejected", `
    const handle = rule(() => "x");
    export { handle as first, handle as second };
    export default { name: "bad", start: handle };
  `, /both 'first' and 'second'/, /one name/],
  ["start must be explicit", `
    export const root = rule(() => "x");
    export default { name: "bad" };
  `, /start/, /Specify a start rule handle/],
  ["external handles require explicit ordering", `
    export const root = rule(() => ext), ext = external();
    export default { name: "bad", start: root };
  `, /External token 'ext'/, /externals/, /order/],
  ["external handles cannot be start rules", `
    export const ext = external();
    export default { name: "bad", start: ext, externals: [ext] };
  `, /start/, /external/],
  ["config must be an object", `export default [];`, /configuration object/],
  ["config requires a valid name", `
    export const root = rule(() => "x");
    export default { name: "not-a-name", start: root };
  `, /name/, /word characters/],
  ["unknown configuration keys are rejected", `
    export const root = rule(() => "x");
    export default { name: "bad", start: root, rules: {} };
  `, /Unknown module grammar option 'rules'/, /named exports/],
  ["array options are validated", `
    export const root = rule(() => "x");
    export default { name: "bad", start: root, extras: () => [] };
  `, /Grammar option 'extras'/, /array/],
  ["metadata handles must be registered", `
    const hidden = rule(() => "x");
    export const root = rule(() => "x");
    export default { name: "bad", start: root, inline: [hidden] };
  `, /Grammar option 'inline'/, /Unregistered rule handle/],
  ["reserved sets require arrays", `
    export const root = rule(() => "x");
    export default { name: "bad", start: root, reserved: { words: "x" } };
  `, /reserved/, /words/, /array/],
];

for (const [name, source, ...messages] of invalidCases) {
  test(name, () => rejects(source, ...messages));
}
