# Modules

A grammar can load two kinds of modules, both bound with a `let`. Paths are relative to the loading file, and a module
loads completely before its parent continues.

- **`import("path.tsg")`** loads a **library**: a file of rules, bindings, and macros. A library has no `grammar` block
and cannot use `inherit()` or `override`.
- **`inherit("path.tsg")`** loads a whole **grammar** to extend. The result must be named in the grammar block's
`inherits` field, and a grammar can inherit only once.

## Names across modules

- Everything a module defines is reachable qualified: `lib::identifier`, `lib::separator`, `lib::delimited(...)`, and
`@lib::make_rules(...)`.
- Rules from imported and inherited modules also join the grammar's scope by bare name, and the two forms are evaluated
differently. A bare `identifier` references the rule and produces its node in the tree, while a qualified
`lib::identifier` inlines the rule's definition at the use site.
- Positions that take a rule name, such as `inline` entries or `alias` symbol targets, always use the bare name.

## Extending a grammar

- `override rule name { ... }` replaces a rule defined by the base grammar.
- Grammar block fields replace the base's values rather than merging. `grammar_config(base, field)` reads the base's
effective value, so any merge is written out explicitly. The one exception is `reserved`, whose word sets merge with
the base's automatically.

## Feature flags

- The grammar block's `flags` field declares cfg flags: `flags: { enabled: ["X"], disabled: ["Y"] }`.
- `#[cfg(X)]` on a declaration or a config list element keeps it only when `X` is enabled. A removed declaration behaves
as if it was never written, and referencing one produces an error with a note pointing at the disabled declaration.
- A parent module's flag settings take precedence over its children's.
- A module load can itself be gated: `#[cfg(EXTRA)] let lib = import("extra.tsg")` skips loading the file entirely when
the flag is disabled.

## A worked example

`lib.tsg`:

```tsg
let separator = ","

macro delimited(item: rule_t) rule_t {
    seq(item, repeat(seq(separator, item)))
}

rule identifier { regexp("[a-z]+") }
```

`grammar.tsg`:

```tsg
let lib = import("lib.tsg")

grammar { language: "example" }

// a qualified macro call, and identifier is in scope by bare name
rule program { lib::delimited(identifier) }

// a qualified value
rule pair { seq(identifier, lib::separator, identifier) }
```

Extending a base grammar:

```tsg
let base = inherit("base/grammar.tsg")

grammar {
    language: "derived",
    inherits: base,
    extras: append(grammar_config(base, extras), [comment]),
}

override rule expression { choice(identifier, number) }
rule comment { token(seq("#", regexp("[^\n]*"))) }
```
