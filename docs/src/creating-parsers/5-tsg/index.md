# The TSG Frontend

A `grammar.tsg` file is written in a small language purpose-built for grammar development. The rule combinators and
grammar fields from [Grammar Fundamentals](../2-grammar-fundamentals.md) all keep their meaning. On top of them, TSG adds
static type checking, `let` bindings, macros, and modules.

A complete grammar:

```tsg
grammar {
  language: "example",
  extras: [regexp(r"\s")],
}

rule expression { choice(sum, number) }
rule sum { prec_left(1, seq(expression, "+", expression)) }
rule number { regexp("[0-9]+") }
```

If you are coming from the JavaScript frontend, start with [Porting from grammar.js](./1-porting.md).
