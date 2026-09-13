# The Language

A `grammar.tsg` file is a sequence of declarations and definitions. Values are immutable after declaration,
and evaluation does not require values to be defined lexically before they are referenced.

## Declarations

- **`rule name { expression }`** defines a grammar rule. Rules become the named nodes of the syntax tree, and a leading
underscore hides a rule as usual.
- **`let name = expression`** binds a reusable value. A type annotation is optional and the type is inferred without
one: `let keywords: list_t<str_t> = ["if", "while"]`.
- **`macro name(param: type_t, ...) return_t { expression }`** defines an expression macro, called like a builtin
(covered in Macros).
- **`rules name(param: type_t, ...) { ... }`** defines a rule-set macro containing whole `rule` declarations, stamped
out by invoking `@name(args)` at the top level (covered in Macros).
- **`expect name`** declares a name whose definition lives elsewhere. Any kind of later definition can claim it,
including a rule, a `let` binding, a macro, or an `externals` entry.
- **`grammar { ... }`** configures the grammar. The fields keep their meaning from
[Grammar Fundamentals](../2-grammar-fundamentals.md):

  ```tsg
  grammar {
      language: "example",                        // the grammar name
      start: program,                             // the start rule, defaults to the first rule
      inherits: base,                             // the base grammar to extend (covered in Modules)
      extras: [regexp(r"\s"), comment],           // tokens allowed anywhere
      word: identifier,                           // the token used for keyword extraction
      externals: [indent, dedent],                // tokens produced by src/scanner.c
      inline: [_expression],                      // rules replaced inline by their definition
      conflicts: [[block, object]],               // intended LR(1) conflicts
      precedences: [["member", "call"]],          // named precedence orderings
      supertypes: [_statement],                   // abstract node categories
      reserved: { default: ["if"] },              // reserved word sets
      flags: { enabled: ["X"], disabled: ["Y"] }, // cfg feature flags (covered in Modules)
  }
  ```

## Types

Every expression has a type, checked before evaluation:

| Type | Values |
|---|---|
| `rule_t` | rules, strings, and patterns |
| `str_t` | strings |
| `int_t` | 32-bit signed integers |
| `list_t<T>` | lists, for example `list_t<rule_t>` |
| `obj_t<T>` | objects with values of type `T` |
| `grammar_t` | an `inherit()` result |
| `library_t` | an `import()` result |

Strings and `regexp()` patterns are rules wherever a rule is expected. Integers support `+` and `-` only.

## Expressions

- Strings: `"..."` with the usual escapes (`\n`, `\t`, `\\`, `\"`, `\0`, `\r`, `\xNN`, `\u{...}`), or raw `r"..."` and
`r#"..."#` when the text itself contains quotes.
- Other literals: integers like `42` and `-1`, `[a, b]` lists, `(a, b)` tuples, and `{ name: value }` objects with
`object.name` field access.
- `concat(a, b, ...)` joins strings and `append(a, b)` joins lists.
- `for (x: type_t, ...) in list { expression }` expands a list into the surrounding call, one expression per element,
most often to generate alternatives: `choice(for (op: str_t) in operators { op })`. Tuple elements destructure
positionally: `for (op: str_t, p: int_t) in [("+", 1), ("*", 2)] { ... }`.
- Calls are builtins, expression macros, or rule-set macros with `@`.

## A complete example

```tsg
grammar {
    language: "example",
    extras: [regexp(r"\s"), comment],
    word: identifier,
}

// an inferred list_t<str_t> binding
let keywords = ["if", "while", "return"]

// an expression macro
macro binop(p: int_t, op: str_t) rule_t {
    prec_left(p, seq(expression, op, expression))
}

// a rule-set macro and its invocation
rules make_keyword_rule(words: list_t<str_t>) {
    rule keyword { token(choice(for (w: str_t) in words { w })) }
}
@make_keyword_rule(keywords)

rule program { repeat(statement) }
rule statement { choice(assignment, keyword, expression) }

// strings are rules where a rule is expected
rule assignment { seq(identifier, "=", expression) }

// expression macros expand per call
rule expression { choice(binop(1, "+"), binop(2, "*"), identifier, number) }

rule identifier { regexp("[a-z_]+") }
rule number { regexp("[0-9]+") }
rule comment { token(seq("#", regexp("[^\n]*"))) }
```
