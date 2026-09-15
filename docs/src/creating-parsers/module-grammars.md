# Module Grammars

Module grammars are an experimental alternative to the `grammar({rules: …})`
format. Rules are ordinary JavaScript bindings, so editors can navigate and
rename their references without a synthetic `$` object.

Use an ES module entry file such as `grammar.mjs`, or `grammar.js` in a package
with `"type": "module"`. The loader automatically distinguishes a legacy
`grammar(...)` result from a module configuration; existing grammars need not
change. The DSL functions are built-in globals, just as in legacy grammars.

```javascript
// grammar.mjs
/// <reference types="tree-sitter-cli/dsl.d.ts" />

export const
  source_file = rule(() => repeat(statement)),
  statement = rule(() => seq(identifier, ';')),
  identifier = rule(() => /[a-z]+/);

/** @satisfies {ModuleGrammar} */
export default {
  name: 'example',
  start: source_file,
  word: identifier,
  extras: [/\s/],
};
```

Pass the module path explicitly when using an extension other than the default
`grammar.js`. Both Node and the embedded QuickJS runtime support this format:

```sh
tree-sitter generate grammar.mjs
tree-sitter generate grammar.mjs --js-runtime native
```

Each named export of a rule handle defines a grammar symbol using that export's
name. Declare each rule once, and refer to the binding everywhere it is used.
`rule(() => expression)` returns an opaque **non-callable handle**, not a helper
function or a parser. Its callback runs after module evaluation, so it can refer
to rules declared later. Put the default configuration after the declarations:
unlike rule callbacks, its property values are evaluated immediately and cannot
reference uninitialized bindings.

Rule declaration/construction order is preserved because it breaks lexical ties.
The selected start rule is emitted first. In derived grammars, overrides retain
their inherited positions and new rules are appended in declaration order.

All existing expression combinators accept handles, including `seq`, `choice`,
`repeat`, `field`, `prec`, `token`, and `reserved`. `alias(value, handle)` produces
a named alias; `alias(value, 'name')` produces an anonymous alias.

For named node types that exist only as aliases, omit the builder:

```javascript
export const
  type_identifier = rule(),
  _type_identifier = rule(() => alias(identifier, type_identifier));
```

The export supplies the node name, just as for a rule with a body. These symbols
produce no rule bodies or external tokens and may only be used as alias targets.
Using one in a rule expression, as the start rule, or in options such as `word`,
`externals`, or `supertypes` is an error. Their ordinary lexical references retain
go-to-definition and rename support.

## Helpers and configuration

Keep helpers unexported, or import them from another module. Call helpers to build
expressions; pass rule handles without calling them:

```javascript
function commaSep(value) {
  return optional(seq(value, repeat(seq(',', value))));
}

export const arguments_list = rule(() =>
  seq('(', commaSep(identifier), ')'));
// identifier is a handle: identifier(), unlike commaSep(identifier), is invalid.
```

The default export has these fields. Unlike legacy grammar options, values are
direct arrays or handles, not callbacks receiving `$`.

| Field | Value |
| --- | --- |
| `name` | Language name |
| `start` | Start-rule handle; required unless inherited |
| `extends` | Namespace imported from another module grammar |
| `word` | Keyword-extraction token handle |
| `extras` | Array of expressions, handles, strings, or regular expressions |
| `conflicts` | Array of arrays of rule handles |
| `inline`, `supertypes` | Arrays of rule handles |
| `precedences` | Arrays of precedence strings or rule handles, highest first |
| `externals` | Array of token expressions or handles, in scanner token order |
| `reserved` | Object mapping context names to arrays of expressions |

Declare named external tokens with `export const indent = external()`, then
include `indent` in `externals`. These handles can be referenced in expressions
but have no rule builder; an external scanner supplies the tokens. The explicit
`start` and `externals` options select the entry rule and scanner token order
independently of where the handles are declared or how exports are enumerated.

Include `tree-sitter-cli/dsl.d.ts` in your editor's types (or use the triple-slash
reference above). The explicit extension works with NodeNext's ESM resolution.
The global `ModuleGrammar` type supports JSDoc `@satisfies` and
TypeScript `satisfies ModuleGrammar`. Keep actual imports and declarations intact
instead of casting them to a broad dictionary: ordinary bindings preserve
go-to-definition and rename. TypeScript authoring still requires producing a
JavaScript module for the loader.

## Inheritance and overrides

Import the base grammar as a module namespace:

```javascript
import * as base from './grammar.mjs';

export const identifier = rule(() => /[a-z_]+/);

/** @satisfies {ModuleGrammar} */
export default {
  name: 'extended_example',
  extends: base,
};
```

Exporting a `rule()` handle under an inherited name replaces that symbol's body.
Both inherited and new handles reference the same symbol and use its replacement
in the derived grammar. The base grammar and its handles are not mutated;
independent derived grammars can replace the same symbol differently.

Referencing `base.identifier` inside a builder still references that symbol; it
does not expand the previous body. Rule handles are not callable. To extend or
transform the inherited body, use the lazy accessor passed to every `rule` callback:

```javascript
export const identifier = rule(original =>
  choice(original(), /special_identifier/));
```

`original()` returns a normalized copy of the immediate predecessor's expression.
It can also be inspected or transformed, for example by filtering a choice's
`members`. Each definition is evaluated at most once per compilation. A previous
body is evaluated only if requested; each call receives a fresh copy so edits
cannot mutate the base.
Overrides that ignore the accessor do not evaluate the replaced body.
The predecessor is the active definition of the same exported name in the
grammar being extended, including replacements made by intermediate grammars.
Failed evaluations are cached too. Calling `original()` without an inherited
body (including when the predecessor is alias-only or external) reports
`Rule 'name' has no inherited body.`

The start rule and all omitted options are inherited. An explicitly provided
option replaces the inherited value, including an empty array. `reserved` is
the exception: it merges by context name, with each provided array replacing
that context's inherited array. The derived grammar supplies its own `name`.

For this prototype, `extends` accepts only the namespace of another module
grammar. Mixing legacy `grammar(...)` inheritance with module grammar inheritance
is not supported.

## Error locations

Rule handles record their declaration stacks when they are created. If a rule is
referenced without being exported, the error names the containing rule and points
back to the missing handle's declaration:

```text
Error: Rule 'call_expression': Unregistered rule handle. Export the rule from this grammar, or inherit its module with 'extends'.
Unexported rule declared at:
    at file:///path/to/grammar.mjs:12:18
```

Reported stacks hide Tree-sitter's DSL/bootstrap frames while preserving frames
from grammar files and user helpers. The same filtering applies to legacy
grammars and errors during module initialization. Nested error causes and
aggregate members are retained, with their internal frames filtered as well.

This uses `new Error().stack`, supported by Node and QuickJS, not V8's
`Error.captureStackTrace`. Stack properties and their formatting are not part of
the ECMAScript standard, so exact frame formatting varies by runtime. If a runtime
does not provide a stack, the diagnostic still reports the error and rule context
but cannot recover a declaration location.
