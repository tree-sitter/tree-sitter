# The JavaScript DSL

A `grammar.js` file expresses the concepts from [Grammar Fundamentals](./2-grammar-fundamentals.md) as JavaScript:

- **Symbols (the `$` object)** — Every grammar rule is written as a JavaScript function that takes a parameter conventionally
called `$`. The syntax `$.identifier` is how you refer to another grammar symbol within a rule.

- **String and Regex literals** — Terminal symbols are written as JavaScript strings and regular expressions. Of course
during parsing, Tree-sitter does not actually use JavaScript's regex engine to evaluate these regexes; it generates its
own regex-matching logic based on the Rust regex syntax as part of each parser. Regex literals are just used as a
convenient way of writing regular expressions in your grammar. You can use Rust regular expressions in your grammar
DSL through the `RustRegex` class. Simply pass your regex pattern as a string:

  ```js
  new RustRegex('(?i)[a-z_][a-z0-9_]*') // matches a simple identifier
  ```

  Unlike JavaScript's builtin `RegExp` class, which takes a pattern and flags as separate arguments, `RustRegex` only
  accepts a single pattern string. While it doesn't support separate flags, you can use inline flags within the pattern
  itself. For more details about Rust's regex syntax and capabilities, check out the [Rust regex documentation][rust regex].

- **Grammar fields** — In addition to `name` and `rules`, the optional grammar fields described in
[Grammar Fundamentals](./2-grammar-fundamentals.md) are each written as a function that accepts the grammar object (`$`)
as its only parameter, like the grammar rules themselves.

[rust regex]: https://docs.rs/regex/1.1.8/regex/#grouping-and-flags
