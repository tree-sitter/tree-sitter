# Porting from grammar.js

The differences are mechanical:

| grammar.js | grammar.tsg |
|---|---|
| `name: "x"` | `language: "x"` |
| `foo: $ => ...` inside `rules` | `rule foo { ... }` at the top level |
| `$.foo` | `foo` |
| `/[0-9]+/` or `new RustRegex("...")` | `regexp("[0-9]+")` |
| `prec.left`, `prec.right`, `prec.dynamic`, `token.immediate` | `prec_left`, `prec_right`, `prec_dynamic`, `token_immediate` |
| `prec.left(rule)` with the number omitted | `prec_left(0, rule)` (the precedence is required) |

Patterns are written in Rust regex syntax directly. Raw strings (`r"..."`) avoid doubling backslashes, so
`regexp(r"\s")` and `regexp("\\s")` describe the same pattern.

The same grammar in both frontends:

```js
export default grammar({
  name: "example",
  extras: $ => [/\s/],
  rules: {
    expression: $ => choice($.sum, $.number),
    sum: $ => prec.left(1, seq($.expression, "+", $.expression)),
    number: $ => /[0-9]+/,
  }
});
```

```tsg
grammar {
  language: "example",
  extras: [regexp(r"\s")],
}

rule expression { choice(sum, number) }
rule sum { prec_left(1, seq(expression, "+", expression)) }
rule number { regexp("[0-9]+") }
```

The two produce identical parsers.

## Migrating an existing grammar

In an existing `grammar.js` project, `tree-sitter init --frontend tsg` scaffolds a `grammar.tsg` to begin porting. Once
it exists, it takes priority during generation, and the build files created by `init` follow whichever grammar file is
present.
