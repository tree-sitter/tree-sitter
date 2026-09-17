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
name, with the trailing-underscore escaping described below. Declare each rule
once, and refer to the binding everywhere it is used.
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

The export supplies the node name, just as for a rule with a body. Unless listed
in `externals`, these symbols produce no rule bodies or external tokens and may
only be used as alias targets. Using such an alias-only symbol in a rule
expression, as the start rule, or in options such as `word` or `supertypes` is an
error. Their ordinary lexical references retain go-to-definition and rename support.

## Escaping exported names

The loader removes exactly one trailing underscore from a module export name.
This lets reserved JavaScript names stay in the same declaration chain:

```javascript
export const
  identifier = rule(() => /[a-z]+/),

  arguments_ = rule(() => seq('(', identifier, ')')),

  for_ = rule(() => 'for');
```

The generated names are `identifier`, `arguments`, and `for`. To retain a literal
trailing underscore, double it: `name__` becomes `name_`. A lone `_` is unchanged.
Exports that normalize to the same grammar name are rejected.

JavaScript bindings and module properties are not renamed: an importing grammar
still uses `base.for_`. Inheritance matches normalized grammar names, and the same
normalization applies to rule bodies, external tokens, alias-only symbols, and
configuration references. Legacy `grammar()` property names are unchanged.

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

Declare named external tokens with `export const indent = rule()`, then
include `indent` in `externals`. The `externals` configuration is the sole
designation of external tokens: there is no separate external-token factory or
handle type. These handles can be referenced in expressions but have no rule
builder; an external scanner supplies the tokens. The explicit
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
transform a specific definition, call that handle's `body()` method:

```javascript
export const identifier = rule(() =>
  choice(base.identifier.body(), /special_identifier/));
```

Every rule handle has `body(): Rule`, including bodyless handles, but calling it
on a bodyless handle is an error. Builders take no arguments. `body()` may only
be called during grammar evaluation, such as inside a rule builder, not at module
top level or after compilation.

`body()` evaluates the specific handle on which it is called, not the active
override of that symbol. For example, an imported ancestor's handle still
provides that ancestor's definition even if an intermediate grammar overrides
the symbol. Ordinary handle references within the returned body still resolve
to the active symbols in the grammar being compiled.

The returned normalized expression can be inspected or transformed, for example
by filtering a choice's `members`. Each handle's builder is evaluated at most
once per compilation, and failed evaluations are cached too. Each successful
`body()` call returns a fresh normalized copy so edits cannot mutate the cached
definition. Replaced bodies are evaluated only if requested.

Use `RuleRef.equals(expression: Rule)` to test whether a normalized expression
directly references a symbol, without comparing its name as a string:

```javascript
export const expression = rule(() => {
  const body = base.expression.body();
  if (body.type !== 'CHOICE') {
    throw new Error('Expected a choice');
  }
  return choice(...body.members.filter(member => !base.jsx_element.equals(member)));
});
```

Like `body()`, `equals()` is only available during grammar evaluation.
It compares symbol identity, not bodies: inherited and overriding references
match the same normalized symbol. It does not expand definitions or look through
aliases, optional expressions, or other wrappers. Its argument must be a normalized
`Rule`, not a `RuleRef`, string, or regex.

Ordinary recursive symbol references remain valid. Cyclic body expansion, such
as a builder calling its own `body()` or two builders requesting each other's
bodies, instead reports a cycle diagnostic.

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
