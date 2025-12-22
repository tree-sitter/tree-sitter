# `tree-sitter generate`

The most important command for grammar development is `tree-sitter generate`, which reads the grammar in structured form and outputs C files that can be compiled into a shared or static library (e.g., using the [`build`](./build.md) command).

```bash
tree-sitter generate [OPTIONS] [GRAMMAR_PATH] # Aliases: gen, g
```

The optional `GRAMMAR_PATH` argument should point to the structured grammar, in one of two forms:
- `grammar.js` a (ESM or CJS) JavaScript file; if the argument is omitted, it defaults to `./grammar.js`.
- `grammar.json` a structured representation of the grammar that is created as a byproduct of `generate`; this can be used to regenerate a missing `parser.c` without requiring a JavaScript runtime (useful when distributing parsers to consumers).

If there is an ambiguity or *local ambiguity* in your grammar, Tree-sitter will detect it during parser generation, and
it will exit with a `Unresolved conflict` error message. To learn more about conflicts and how to handle them, see
the section on [`Structuring Rules Well`](../creating-parsers/3-writing-the-grammar.md#structuring-rules-well)
in the user guide.

## Generated files

- `src/parser.c` implements the parser logic specified in the grammar.
- `src/tree_sitter/parser.h` provides basic C definitions that are used in the generated `parser.c` file.
- `src/tree_sitter/alloc.h` provides memory allocation macros that can be used in an external scanner.
- `src/tree_sitter/array.h` provides array macros that can be used in an external scanner.
- `src/grammar.json` contains a structured representation of the grammar; can be used to regenerate the parser without having to re-evaluate the `grammar.js`.
- `src/node-types.json` provides type information about individual syntax nodes; see the section on [`Static Node Types`](../using-parsers/6-static-node-types.md).


## Options

### `-l/--log`

Print the log of the parser generation process. This includes information such as what tokens are included in the error recovery state,
what keywords were extracted, what states were split and why, and the entry point state.

### `--abi <VERSION>`

The ABI to use for parser generation. The default is ABI 15, with ABI 14 being a supported target.

### `--no-parser`

Only generate `grammar.json` and `node-types.json`

### `-o/--output`

The directory to place the generated parser in. The default is `src/` in the current directory.

### `--report-states-for-rule <RULE>`

Print the overview of states from the given rule. This is useful for debugging and understanding the generated parser's
item sets for all given states in a given rule. To solely view state count numbers for rules, pass in `-` for the rule argument.
To view the overview of states for every rule, pass in `*` for the rule argument.

### `--json-summary`

Report conflicts in a JSON format.

### `--js-runtime <EXECUTABLE>`

The path to the JavaScript runtime executable to use when generating the parser. The default is `node`.
Note that you can also set this with `TREE_SITTER_JS_RUNTIME`. Starting from version 0.26, you can
also pass in `native` to use the experimental native QuickJS runtime that comes bundled with the CLI.
This avoids the dependency on a JavaScript runtime entirely. The native QuickJS runtime is compatible
with ESM as well as with CommonJS in strict mode. If your grammar depends on `npm` to install dependencies such as base grammars, the native runtime can be used *after* running `npm install`.

### `--disable-optimization`

Disable optimizations when generating the parser. Currently, this only affects the merging of compatible parse states.
